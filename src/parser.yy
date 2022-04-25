%code top
{
#include <cstdio>
#include <cstring>
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
        TOKEN_IF TOKEN_ELSE TOKEN_WHILE
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
    
program : vardefs 
        {
                $[start_jump].as.int_val = vm.bytecode_len();
                vm.write_op(OP::JMP);
                vm.write_word(0);
        } [start_jump]
        fundefs
        {
                vm.patch_start_jump($[start_jump].as.int_val);
        }
        ;
    
vardefs : variable vardefs | ;
fundefs : fundef fundefs | ;
    
fundef : function 
            {
                    string ident = $1.as.str_val;
                    FuncEntry entry;
                    entry.retType = $1.type;
                    entry.pc = (u32) vm.bytecode_len();

                    currFuncRetType = entry.retType;

                    if(ident == "start")
                    {
                            if(entry.retType != DataType::NIL || scope_starts.size() > 0)
                            {
                                    DECLARE_ERROR("Function \"start\" must have the following prototype: fun start() { ... }");
                            }
                            vm.set_start(entry.pc);
                    }

                    for(usize i = 0, size = scope_starts.size(); i < size; i++)
                    {
                            ScopeStartEntry sse = scope_starts.at(i);
                            entry.paramTypes.push_back(sse.type);
                    }
                    if(!add_func(ident, entry)) DECLARE_ERROR("Function redefinition not allowed");
            } 
            blckstmt { vm.write_op(OP::CONST_0); vm.write_op(OP::RET); }
            ;
    
variable : TOKEN_VAR TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_EQUAL expr TOKEN_SEMICOLON
    {
            if($4.type != $6.type) DECLARE_ERROR("Type mismatch");

            usize id = vm.write_decl_var(is_currently_global());
            string ident = $2.as.str_val;
            SymbolEntry entry = { $4.type, id };

            if(!add_symbol(ident, entry)) DECLARE_ERROR("Variable redeclaration not allowed");
    }

            | TOKEN_VAR TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SQ_BRACK_L args TOKEN_SQ_BRACK_R TOKEN_EQUAL TOKEN_SQ_BRACK_L args TOKEN_SQ_BRACK_R TOKEN_SEMICOLON
            ;
    
function :  TOKEN_FUN TOKEN_IDENTIFIER TOKEN_PAREN_L params TOKEN_PAREN_R 
            {
                    $$.as.str_val = $2.as.str_val;
                    $$.type = DataType::NIL;
            }

                | TOKEN_FUN TOKEN_IDENTIFIER TOKEN_PAREN_L params TOKEN_PAREN_R TOKEN_COLON type
                {
                    $$.as.str_val = $2.as.str_val;
                    $$.type = $7.type;
                }

            | TOKEN_FUN TOKEN_IDENTIFIER TOKEN_PAREN_L params TOKEN_PAREN_R TOKEN_COLON type TOKEN_SQ_BRACK_L TOKEN_SQ_BRACK_R
            ;

params : params_
        |
        ;
    
params_	: param
        | param TOKEN_COMMA params_
        ;
    
param :	TOKEN_IDENTIFIER TOKEN_COLON type
            {
                    scope_starts.push_back({$1.as.str_val, $3.type});
            }

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
        | ifstmt
        | whilestmt
        | retstmt
        | asgnstmt
        | blckstmt
        | TOKEN_BRK TOKEN_SEMICOLON
        {
                if(loop_entries.empty())
                {
                        DECLARE_ERROR("brk statement outside a loop");       
                }
                u64 brk_point = vm.bytecode_len();
                vm.write_op(OP::JMP);
                vm.write_word(0);
                loop_entries.back().breaks.push_back(brk_point);
        }
        | TOKEN_CNT TOKEN_SEMICOLON
        {
                if(loop_entries.empty())
                {
                        DECLARE_ERROR("cnt statement outside a loop");       
                }
                vm.write_op(OP::LOOP);
                vm.write_word(static_cast<u16>(vm.bytecode_len() - 1 - loop_entries.back().loop_start));

        }
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
                        printf("type %d", $2.type);
                        DECLARE_ERROR("Invalid operand for log\n");
                        break;
                }
        }
        ;
    
retstmt : TOKEN_RET TOKEN_SEMICOLON 
            {
                    if(currFuncRetType != DataType::NIL) DECLARE_ERROR("Must return a value");
                    vm.write_op(OP::CONST_0); 
                    vm.write_op(OP::RET);
            }
        | TOKEN_RET expr TOKEN_SEMICOLON
            {
                    if(currFuncRetType != $2.type) DECLARE_ERROR("Return value type mismatch");
                    vm.write_op(OP::RET);
            }
        ;

whilestmt : TOKEN_WHILE {
        $[offset_loop].as.int_val = vm.bytecode_len();
        LoopEntry entry = {vm.bytecode_len(), vector<u64>()};
        loop_entries.push_back(entry);
}[offset_loop] expr {
        $[offset_exit].as.int_val = vm.bytecode_len();
        vm.write_op(OP::JMP_IF_FALSE);
        vm.write_word(0);
}[offset_exit] blckstmt {
        vm.write_op(OP::LOOP);
        i64 offset = vm.bytecode_len() - 1 - $[offset_loop].as.int_val;
        if(offset > UINT16_MAX) DECLARE_ERROR("Code jump too big");
        vm.write_word(static_cast<u16>(offset));
        vm.patch_jump($[offset_exit].as.int_val);
        for(auto it = loop_entries.back().breaks.begin(); it != loop_entries.back().breaks.end(); it ++)
        {
                vm.patch_jump(*it);
        }  
        loop_entries.pop_back();

}
        ;

ifstmt  : /*TOKEN_IF expr {
        $[offset_then].as.int_val = vm.bytecode_len();
        vm.write_op(OP::JMP_IF_FALSE);
        vm.write_word(0);
        
}[offset_then] blckstmt {
        $[offset_else].as.int_val = vm.bytecode_len();
        vm.write_op(OP::JMP);
        vm.write_word(0);
        vm.patch_jump($[offset_then].as.int_val);
} [offset_else] TOKEN_ELSE blckstmt {
        vm.patch_jump($[offset_else].as.int_val);
}
        | */TOKEN_IF expr {
        $[offset].as.int_val = vm.bytecode_len();
        vm.write_op(OP::JMP_IF_FALSE);
        vm.write_word(0);
}[offset] blckstmt {
        vm.patch_jump($[offset].as.int_val);        
}
        ;

asgnstmt : TOKEN_IDENTIFIER TOKEN_EQUAL expr TOKEN_SEMICOLON
            {
                    string ident = $1.as.str_val;
                    SymbolEntry entry;
                    bool is_global;
                    if(!check_symbol(ident, entry, is_global)) DECLARE_ERROR("Undeclared identifier");
                    if(entry.type != $3.type) DECLARE_ERROR("Type mismatch");

                    vm.write_op(is_global ? OP::GLOB_VARSET : OP::VARSET);
                    vm.write_byte(entry.id);
            }

            | TOKEN_IDENTIFIER TOKEN_SQ_BRACK_L expr TOKEN_SQ_BRACK_R TOKEN_EQUAL expr TOKEN_SEMICOLON
            ;
    
blckstmt : TOKEN_BRACE_L 
            { 
                    open_scope();
                    for(auto it = scope_starts.rbegin(); it != scope_starts.rend(); it++)
                    {
                            ScopeStartEntry sse = *it;
                            
                            usize id = vm.write_decl_var(false); // Never global in a block stmt
                            SymbolEntry entry = { sse.type, id };

                            if(!add_symbol(sse.symbol, entry)) DECLARE_ERROR("Variable redeclaration not allowed");
                    }
                    scope_starts.clear();
            } 
            stmts TOKEN_BRACE_R 
            { 
                    usize var_count = get_scope_var_count();
                    close_scope();
                    vm.undecl_vars(var_count);
            }
        ;
    
expr : expr TOKEN_LOGICAL_OR andexpr 
{
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::OR);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
        | andexpr { $$.type = $1.type; }
        ;
    
andexpr : andexpr TOKEN_LOGICAL_AND notexpr
{
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::AND);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
        | notexpr { $$.type = $1.type; }
        ;
    
notexpr : TOKEN_LOGICAL_NOT relexpr
        | relexpr { $$.type = $1.type; }
        ;
    
relexpr : relexpr TOKEN_LESS_EQ sumexpr
{
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::LESS_EQUAL);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
        | relexpr TOKEN_GREATER_EQ sumexpr
{
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::LESS);
                        vm.write_op(OP::NOT);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
        | relexpr TOKEN_LESS sumexpr
{
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::LESS);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
        | relexpr TOKEN_GREATER sumexpr
{
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::LESS_EQUAL);
                        vm.write_op(OP::NOT);
                } else {
                        DECLARE_ERROR("Types not same.");
                }     
}
        | relexpr TOKEN_DOUBLE_EQ sumexpr
{
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::EQUAL);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
        | relexpr TOKEN_NOT_EQ sumexpr
{
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::EQUAL);
                        vm.write_op(OP::NOT);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
}
        | sumexpr { $$.type = $1.type; }
        ;


sumexpr : sumexpr TOKEN_PLUS mulexpr{
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::ADD);
                } else {
                        DECLARE_ERROR("Types not same.");
                }    
}
        | sumexpr TOKEN_MINUS mulexpr { 
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::SUB);
                } else {
                        DECLARE_ERROR("Types not same.");
                }
}
        | mulexpr { $$.type = $1.type; }
        ;

mulexpr : mulexpr TOKEN_STAR unexpr{
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::MUL);
                } else {
                        DECLARE_ERROR("Types not same.");
                }    
}
        | mulexpr TOKEN_SLASH unexpr
{
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::DIV);
                } else {
                        DECLARE_ERROR("Types not same.");
                }
}
        | mulexpr TOKEN_MODULO unexpr
{
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::MOD);
                } else {
                        DECLARE_ERROR("Types not same.");
                }
}
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

            | TOKEN_NIL
            {
                    vm.write_op(OP::CONST_0);
                    $$.type = DataType::NIL; 
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
                    SymbolEntry entry;
                    bool is_global;
                    if(!check_symbol(ident, entry, is_global)) DECLARE_ERROR("Undeclared identifier");

                    vm.write_op(is_global ? OP::GLOB_VARGET : OP::VARGET);
                    vm.write_byte(entry.id);
                    $$.type = entry.type;
            }
            ;
    
callexpr : TOKEN_IDENTIFIER TOKEN_PAREN_L args TOKEN_PAREN_R
            {
                    string ident = $1.as.str_val;
                    FuncEntry func;
                    if(!check_func(ident, func)) DECLARE_ERROR("Undefined function");
                    if(func.paramTypes.size() != argv.size()) DECLARE_ERROR("Number of function parameters and arguments do not match");

                    for(usize i = 0, size = argv.size(); i < size; i++)
                    {
                            if(func.paramTypes.at(i) != argv.at(i)) DECLARE_ERROR("Function parameter and argument type mismatch");
                    }
                    argv.clear();

                    vm.write_op(OP::CALL);
                    vm.write_dword(func.pc);

                    $$.type = func.retType;
            }
            ;
    
args : args_
        |
        ;
    
args_ : args_ TOKEN_COMMA expr
            {
                    argv.push_back($3.type);
            }
        | expr
        {
                argv.push_back($1.type);
        }
        ;
    
    
%%
    
void yyerror(const char *msg)
{
    fprintf(stderr, "<Line %d> Syntax error: %s\n", yylineno, msg);
}
