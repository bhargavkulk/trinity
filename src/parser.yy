%code top
{
#include <cstdio>
#include "vm.hh"
#include "symbols.hh"

extern int yylineno;
extern int yylex(void);
void yyerror(const char *);

#define DECLARE_ERROR(msg) do { yyerror(msg); YYERROR; } while(0)

}

%code requires
{
#include <cstdint>
#include "types.hh"
}

%define api.value.type { ExprType }

%token 	TOKEN_INT TOKEN_STR TOKEN_BLK TOKEN_FUN
        TOKEN_IF TOKEN_ELSE TOKEN_FOR TOKEN_FROM TOKEN_TO TOKEN_WHILE
        TOKEN_VAR TOKEN_BRK TOKEN_CNT TOKEN_RET TOKEN_NIL
        TOKEN_DIR_GRID TOKEN_DIR_TITLE TOKEN_DIR_ICON

        TOKEN_SQ_BRACK_L TOKEN_SQ_BRACK_R TOKEN_PAREN_L TOKEN_PAREN_R TOKEN_BRACE_L TOKEN_BRACE_R
        TOKEN_PLUS TOKEN_MINUS TOKEN_SLASH TOKEN_STAR TOKEN_MODULO
        TOKEN_DOUBLE_EQ TOKEN_NOT_EQ TOKEN_GREATER_EQ TOKEN_LESS_EQ TOKEN_EQUAL TOKEN_LESS TOKEN_GREATER
        TOKEN_LOGICAL_AND TOKEN_LOGICAL_OR TOKEN_LOGICAL_NOT
        TOKEN_SEMICOLON TOKEN_COLON TOKEN_COMMA

        TOKEN_INT_VAL TOKEN_STR_VAL TOKEN_IDENTIFIER

        TOKEN_LOG
                
        TOKEN_ERR

%%

program : definitions
        ;


definitions : definition definitions
        |
        ;

definition : variable 
        | function
        ;

variable : TOKEN_VAR TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_EQUAL expr TOKEN_SEMICOLON
{
        if($4.type != $6.type) DECLARE_ERROR("Type mismatch");

        usize id = vm.write_decl_var();
        string ident = $2.as.str_val;
        Entry entry = { $4.type, id };

        if(!add_symbol(ident, entry)) DECLARE_ERROR("Variable redeclaration not allowed");

}

        | TOKEN_VAR TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SQ_BRACK_L args TOKEN_SQ_BRACK_R TOKEN_EQUAL TOKEN_SQ_BRACK_L args TOKEN_SQ_BRACK_R TOKEN_SEMICOLON
        ;

function :  TOKEN_FUN TOKEN_IDENTIFIER TOKEN_PAREN_L params TOKEN_PAREN_R blckstmt
                | TOKEN_FUN TOKEN_IDENTIFIER TOKEN_PAREN_L params TOKEN_PAREN_R TOKEN_COLON type blckstmt
                | TOKEN_FUN TOKEN_IDENTIFIER TOKEN_PAREN_L params TOKEN_PAREN_R TOKEN_COLON type TOKEN_SQ_BRACK_L TOKEN_SQ_BRACK_R blckstmt
        ;

params : params_
        |
        ;

params_	: param
        | param TOKEN_COMMA params_
        ;

param :	TOKEN_IDENTIFIER TOKEN_COLON type
        | TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SQ_BRACK_L TOKEN_SQ_BRACK_R
        ;

type : TOKEN_INT { $$.type = DataType::INT; }
        | TOKEN_STR { $$.type = DataType::STR; }
        | TOKEN_BLK { $$.type = DataType::BLK; }
        ;

stmts :	stmts stmt
        |
        ;

stmt : variable
        | expr TOKEN_SEMICOLON
        | forstmt
        | ifstmt
        | whilestmt
        | retstmt
        | asgnstmt
        | blckstmt
        | TOKEN_BRK TOKEN_SEMICOLON
        | TOKEN_CNT TOKEN_SEMICOLON
        | TOKEN_SEMICOLON

        | TOKEN_LOG expr TOKEN_SEMICOLON
        {
                switch($2.type)
                {
                        case DataType::STR:
                        vm.write_op(OP::LOGSTR);
                        break;

                        case DataType::INT:
                        vm.write_op(OP::LOGINT);
                        break;

                        default:
                        DECLARE_ERROR("Invalid operand for log\n");
                        break;
                }
        }
        ;

retstmt : TOKEN_RET TOKEN_SEMICOLON
        | TOKEN_RET expr TOKEN_SEMICOLON
        ;

whilestmt : TOKEN_WHILE expr blckstmt
        ;

forstmt : TOKEN_FOR TOKEN_IDENTIFIER TOKEN_FROM expr TOKEN_TO expr blckstmt
        ;

ifstmt  : TOKEN_IF expr {
        vm.write_op(OP::JMP_IF_FALSE);
        vm.write_word(0);
        $[offset_then].as.int_val = vm.bytecode_len() - 3;
}[offset_then] blckstmt {
        vm.write_op(OP::JMP);
        vm.write_word(0);
        $[offset_else].as.int_val = vm.bytecode_len() - 3;
        vm.patch_jump($[offset_then].as.int_val);
} [offset_else] TOKEN_ELSE blckstmt {
        vm.patch_jump($[offset_else].as.int_val);
}
        | TOKEN_IF expr {
        vm.write_op(OP::JMP_IF_FALSE);
        vm.write_word(0);
        $[offset].as.int_val = vm.bytecode_len() - 3;
}[offset] blckstmt {
        vm.patch_jump($[offset].as.int_val);        
}
        ;

asgnstmt : TOKEN_IDENTIFIER TOKEN_EQUAL expr TOKEN_SEMICOLON
{
string ident = $1.as.str_val;
Entry entry;
if(!check_symbol(ident, entry)) DECLARE_ERROR("Undeclared identifier");
if(entry.type != $3.type) DECLARE_ERROR("Type mismatch");

vm.write_op(OP::VARSET);
vm.write_byte(entry.id);
}
        | TOKEN_IDENTIFIER TOKEN_SQ_BRACK_L expr TOKEN_SQ_BRACK_R TOKEN_EQUAL expr TOKEN_SEMICOLON
        ;

blckstmt : TOKEN_BRACE_L { open_scope(); } stmts TOKEN_BRACE_R 
        { 
                usize var_count = get_scope_var_count();
                close_scope();
                vm.undecl_vars(var_count);
        }
        ;

expr : expr TOKEN_LOGICAL_OR andexpr 
        | andexpr { $$.type = $1.type; }
        ;

andexpr : andexpr TOKEN_LOGICAL_AND notexpr
        | notexpr { $$.type = $1.type; }
        ;

notexpr : TOKEN_LOGICAL_NOT relexpr 
        | relexpr { $$.type = $1.type; }
        ;

relexpr : relexpr TOKEN_LESS_EQ sumexpr
        | relexpr TOKEN_GREATER_EQ sumexpr
        | relexpr TOKEN_LESS sumexpr
        | relexpr TOKEN_GREATER sumexpr
        | relexpr TOKEN_DOUBLE_EQ sumexpr
        | relexpr TOKEN_NOT_EQ sumexpr
        | sumexpr { $$.type = $1.type; }
        ;

sumexpr : sumexpr TOKEN_PLUS mulexpr
        | sumexpr TOKEN_MINUS mulexpr
        | mulexpr { $$.type = $1.type; }
        ;

mulexpr : mulexpr TOKEN_STAR unexpr
        | mulexpr TOKEN_SLASH unexpr
        | mulexpr TOKEN_MODULO unexpr
        | unexpr { $$.type = $1.type; }
        ;

unexpr : TOKEN_MINUS smolexpr
        | smolexpr { $$.type = $1.type; }
        ;

smolexpr : TOKEN_INT_VAL
{
        vm.write_constant_op(OP::CONST, $1.as.int_val);
        $$.type = DataType::INT;
}

        | TOKEN_STR_VAL
        {
                vm.write_constant_op(OP::CONST, (u64) $1.as.str_val);
                $$.type = DataType::STR;
        }
        | TOKEN_PAREN_L expr TOKEN_PAREN_R
        | TOKEN_IDENTIFIER TOKEN_SQ_BRACK_L expr TOKEN_SQ_BRACK_R
        | callexpr
        | TOKEN_IDENTIFIER
        {
                string ident = $1.as.str_val;
                Entry entry;
                if(!check_symbol(ident, entry)) DECLARE_ERROR("Undeclared identifier");

                vm.write_op(OP::VARGET);
                vm.write_byte(entry.id);
                $$.type = entry.type;
        }
        ;

callexpr : TOKEN_IDENTIFIER TOKEN_PAREN_L args TOKEN_PAREN_R
        ;

args : args_
        |
        ;

args_ : args_ TOKEN_COMMA expr
        | expr
        ;


%%

void yyerror(const char *msg)
{
fprintf(stderr, "<Line %d> Syntax error: %s\n", yylineno, msg);
}