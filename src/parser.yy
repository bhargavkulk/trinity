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
    
        TOKEN_NEW TOKEN_DEL TOKEN_REC
                
        TOKEN_ERR
    
%%
    
program : 
        globdefs 
        {
                $[start_call].as.int_val = vm.bytecode_len();
                vm.write_op(OP::CALL);
                vm.write_dword(0);
                vm.write_op(OP::POP);
                vm.write_op(OP::HLT);
        } [start_call]
        defs
        {
                vm.patch_start_call($[start_call].as.int_val);
        } ;
    

globdefs : 
        variable globdefs | ;


defs : 
        fundef defs | 

        /*recdef defs |*/ ;
    
/*
recdef :
        TOKEN_REC TOKEN_IDENTIFIER
        {
                string ident = $2.as.str_val;
                RecordEntry entry;
                entry.name = ident;
                if(!add_record(ident, entry)) DECLARE_ERROR("Cannot create two records with the same name");
                set_current_record_name(ident);
        }
        TOKEN_BRACE_L fielddefs TOKEN_BRACE_R ;


fielddefs :
        fielddef fielddefs | ;


fielddef :
        TOKEN_VAR TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SEMICOLON
        {
                string &rec = get_current_record_name();
                string ident = $2.as.str_val;

                RecordEntry::FieldEntry entry;
                entry.type = $4.type;
                entry.id = get_current_record_field_id();

                if(!add_record_field(rec, ident, entry)) DECLARE_ERROR("Cannot declare two fields with the same name");
        } |

        TOKEN_VAR TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SQ_BRACK_L args TOKEN_SQ_BRACK_R TOKEN_SEMICOLON
        {

        } ;
*/

fundef : 
        function 
        {
                string ident = $1.as.str_val;
                FuncEntry entry;
                entry.retType = $1.type;
                entry.ret_dim_count = $1.as.int_val;
                entry.pc = static_cast<u32>(vm.bytecode_len());

                currFuncRetType = entry.retType;
                curr_func_ret_dim_count = entry.ret_dim_count;

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
                        entry.param_dim_counts.push_back(sse.dim_count);
                }
                FuncEntry nat;
                if(check_native(ident, nat) || !add_func(ident, entry)) DECLARE_ERROR("Function redefinition not allowed");
        } blckstmt 
        { 
                vm.write_op(OP::CONST_0); vm.write_op(OP::RET); 
        } ;


variable : 
        TOKEN_VAR TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_EQUAL expr TOKEN_SEMICOLON
        {
                if($4.type != $6.type) DECLARE_ERROR("Type mismatch");

                usize id = vm.write_decl_var(is_currently_global());
                string ident = $2.as.str_val;
                SymbolEntry entry = { $4.type, id, 0 };

                if(!add_symbol(ident, entry)) DECLARE_ERROR("Variable redeclaration not allowed");
        } |

        TOKEN_VAR TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SQ_BRACK_L dim_commas TOKEN_SQ_BRACK_R TOKEN_EQUAL expr TOKEN_SEMICOLON
        {
                if(convert_to_arr_type($4.type) != $9.type) DECLARE_ERROR("Type mismatch: Not an array expression");
                if($6.as.int_val + 1 != $9.as.int_val) DECLARE_ERROR("Number of dimensions does not match");

                usize id = vm.write_decl_var(is_currently_global());
                string ident = $2.as.str_val;
                SymbolEntry entry = { convert_to_arr_type($4.type), id, $9.as.int_val };

                if(!add_symbol(ident, entry)) DECLARE_ERROR("Variable redeclaration not allowed");
        } |

        TOKEN_VAR TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SQ_BRACK_L args TOKEN_SQ_BRACK_R TOKEN_EQUAL TOKEN_NEW TOKEN_SEMICOLON
        {
                if(argv.size() >= UINT8_MAX) DECLARE_ERROR("Arrays can have a maximum of 255 dimensions");
                for(auto arg : argv)
                {
                        if(arg.type != DataType::INT) DECLARE_ERROR("Array dimensions can only be of type \"int\"");
                }

                vm.write_op(OP::ARR);
                vm.write_byte(static_cast<u8>(argv.size()));

                usize id = vm.write_decl_var(is_currently_global());
                string ident = $2.as.str_val;
                SymbolEntry entry = { convert_to_arr_type($4.type), id, static_cast<i64>(argv.size()) };

                if(!add_symbol(ident, entry)) DECLARE_ERROR("Variable redeclaration not allowed");
                argv.clear();
        } |

        TOKEN_VAR TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SQ_BRACK_L args TOKEN_SQ_BRACK_R TOKEN_SEMICOLON
        {
                DECLARE_ERROR("Arrays must be declared using the \"new\" keyword as the initialised value");
        } ;


dim_commas : 
        dim_commas TOKEN_COMMA
        {
                $$.as.int_val = $1.as.int_val + 1;
        } |
        {
                $$.as.int_val = 0;
        };
    

function : 
        TOKEN_FUN TOKEN_IDENTIFIER TOKEN_PAREN_L params TOKEN_PAREN_R 
        {
                $$.as.str_val = $2.as.str_val;
                $$.type = DataType::NIL;
        } |

        TOKEN_FUN TOKEN_IDENTIFIER TOKEN_PAREN_L params TOKEN_PAREN_R TOKEN_COLON type
        {
                $$.as.str_val = $2.as.str_val;
                $$.type = $7.type;
        } |

        TOKEN_FUN TOKEN_IDENTIFIER TOKEN_PAREN_L params TOKEN_PAREN_R TOKEN_COLON type TOKEN_SQ_BRACK_L dim_commas TOKEN_SQ_BRACK_R
        {
                $$.as.str_val = $2.as.str_val;
                $$.type = convert_to_arr_type($7.type);
                $$.as.int_val = $9.as.int_val + 1;
        }
        ;


params : 
        params_ | ;
    

params_	: 
        param |
        
        param TOKEN_COMMA params_ ;
    

param :	
        TOKEN_IDENTIFIER TOKEN_COLON type
        {
                scope_starts.push_back({ $1.as.str_val, $3.type, 0 });
        } |

        TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SQ_BRACK_L dim_commas TOKEN_SQ_BRACK_R
        {
                scope_starts.push_back({$1.as.str_val, convert_to_arr_type($3.type), $5.as.int_val + 1});
        } ;
    

type : 
        TOKEN_INT 
        { 
                $$.type = DataType::INT; 
        } |
        TOKEN_STR 
        { 
                $$.type = DataType::STR; 
        } |
        TOKEN_BLK 
        { 
                $$.type = DataType::BLK;
        } ;
    

stmts :	
        stmts stmt | ;
    

stmt : 
        variable |
        expr TOKEN_SEMICOLON 
        { 
                vm.write_op(OP::POP); 
        } |

        ifstmt |
        whilestmt |
        retstmt |
        asgnstmt |
        blckstmt |
        delstmt |
        TOKEN_BRK TOKEN_SEMICOLON
        {
                if(loop_entries.empty())
                {
                        DECLARE_ERROR("brk statement outside a loop");       
                }
                u64 brk_point = vm.bytecode_len();
                vm.write_op(OP::JMP);
                vm.write_word(0);
                loop_entries.back().breaks.push_back(brk_point);
        } |
        TOKEN_CNT TOKEN_SEMICOLON
        {
                if(loop_entries.empty())
                {
                        DECLARE_ERROR("cnt statement outside a loop");       
                }
                vm.write_op(OP::LOOP);
                vm.write_word(static_cast<u16>(vm.bytecode_len() - 1 - loop_entries.back().loop_start));

        } |
        TOKEN_SEMICOLON ;
    

retstmt : 
        TOKEN_RET TOKEN_SEMICOLON 
        {
                if(currFuncRetType != DataType::NIL) DECLARE_ERROR("Must return a value");
                vm.write_op(OP::CONST_0); 
                vm.write_op(OP::RET);
        } |
        TOKEN_RET expr TOKEN_SEMICOLON
        {
                if(currFuncRetType != $2.type) DECLARE_ERROR("Return value type mismatch");
                if(is_arr_type(currFuncRetType) && curr_func_ret_dim_count != $2.as.int_val) DECLARE_ERROR("Return value array type dimension count mismatch");
                vm.write_op(OP::RET);
        } ;


whilestmt : 
        TOKEN_WHILE 
        {
                $[offset_loop].as.int_val = vm.bytecode_len();
                LoopEntry entry = {vm.bytecode_len(), vector<u64>()};
                loop_entries.push_back(entry);
        } [offset_loop] 
        expr 
        {
                $[offset_exit].as.int_val = vm.bytecode_len();
                vm.write_op(OP::JMP_IF_FALSE);
                vm.write_word(0);
        } [offset_exit] 
        blckstmt 
        {
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
        } ;


ifstmt : 
        TOKEN_IF expr 
        {
                $[offset_then].as.int_val = vm.bytecode_len();
                vm.write_op(OP::JMP_IF_FALSE);
                vm.write_word(0);
        } [offset_then] 
        blckstmt 
        {
                $[offset_else].as.int_val = vm.bytecode_len();
                vm.write_op(OP::JMP);
                vm.write_word(0);
                vm.patch_jump($[offset_then].as.int_val);
        } [offset_else] 
        TOKEN_ELSE blckstmt 
        {
                vm.patch_jump($[offset_else].as.int_val);
        } /* |
        
        TOKEN_IF expr 
        {
                $[offset].as.int_val = vm.bytecode_len();
                vm.write_op(OP::JMP_IF_FALSE);
                vm.write_word(0);
        } [offset] blckstmt 
        {
                vm.patch_jump($[offset].as.int_val);        
        }*/ ;


asgnstmt : 
        TOKEN_IDENTIFIER TOKEN_EQUAL expr TOKEN_SEMICOLON
        {
                string ident = $1.as.str_val;
                SymbolEntry entry;
                bool is_global;
                if(!check_symbol(ident, entry, is_global)) DECLARE_ERROR("Undeclared identifier");
                if(entry.type != $3.type) DECLARE_ERROR("Type mismatch");
                if(is_arr_type(entry.type) && entry.dim_count != $3.as.int_val) DECLARE_ERROR("Number of dimensions does not match");

                vm.write_op(is_global ? OP::GLOB_VARSET : OP::VARSET);
                vm.write_byte(entry.id);
        } |

        TOKEN_IDENTIFIER TOKEN_SQ_BRACK_L args TOKEN_SQ_BRACK_R TOKEN_EQUAL expr TOKEN_SEMICOLON
        {
                string ident = $1.as.str_val;
                SymbolEntry entry;
                bool is_global;
                if(!check_symbol(ident, entry, is_global)) DECLARE_ERROR("Undeclared identifier");
                if(!is_arr_type(entry.type)) DECLARE_ERROR("Cannot use subscript operator on a non-array type");
                for(auto arg : argv)
                {
                        if(arg.type != DataType::INT) DECLARE_ERROR("Array dimensions can only be of type \"int\"");
                }
                if(convert_from_arr_type(entry.type) != $6.type) DECLARE_ERROR("Type mismatch");

                vm.write_op(is_global ? OP::GLOB_VARGET : OP::VARGET);
                vm.write_byte(entry.id);
                vm.write_op(OP::ARRSET);

                argv.clear();
        } ;
    

blckstmt : 
        TOKEN_BRACE_L 
        {
                open_scope();
                for(auto it = scope_starts.rbegin(); it != scope_starts.rend(); it++)
                {
                        ScopeStartEntry sse = *it;
                        
                        usize id = vm.write_decl_var(false); // Never global in a block stmt
                        SymbolEntry entry = { sse.type, id, sse.dim_count };

                        if(!add_symbol(sse.symbol, entry)) DECLARE_ERROR("Variable redeclaration not allowed");
                }
                scope_starts.clear();
        } stmts TOKEN_BRACE_R 
        {
                usize var_count = get_scope_var_count();
                close_scope();
                vm.undecl_vars(var_count);
        } ;


delstmt :
        TOKEN_DEL expr
        {
                if(!is_arr_type($2.type)) DECLARE_ERROR("Cannot delete primitive type values");
                vm.write_op(OP::DEL);
        }


expr : 
        expr TOKEN_LOGICAL_OR andexpr 
        {
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::OR);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
        } |

        andexpr { $$.type = $1.type; } ;
    

andexpr : 
        andexpr TOKEN_LOGICAL_AND notexpr
        {
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::AND);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
        } |

        notexpr { $$.type = $1.type; } ;
    

notexpr : 
        TOKEN_LOGICAL_NOT relexpr
        {
                if($2.type == DataType::INT) {
                        vm.write_op(OP::NOT);
                } else {
                        DECLARE_ERROR("Types not same.");
                }
                $$.type = $2.type;
        } |

        relexpr { $$.type = $1.type; } ;
    

relexpr : 
        relexpr TOKEN_LESS_EQ sumexpr
        {
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::LESS_EQUAL);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
        } |

        relexpr TOKEN_GREATER_EQ sumexpr
        {
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::LESS);
                        vm.write_op(OP::NOT);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
        } |

        relexpr TOKEN_LESS sumexpr
        {
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::LESS);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
        } |

        relexpr TOKEN_GREATER sumexpr
        {
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::LESS_EQUAL);
                        vm.write_op(OP::NOT);
                } else {
                        DECLARE_ERROR("Types not same.");
                }     
        } |

        relexpr TOKEN_DOUBLE_EQ sumexpr
        {
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::EQUAL);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
        } |

        relexpr TOKEN_NOT_EQ sumexpr
        {
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::EQUAL);
                        vm.write_op(OP::NOT);
                } else {
                        DECLARE_ERROR("Types not same.");
                } 
        } |

        sumexpr { $$.type = $1.type; } ;


sumexpr : 
        sumexpr TOKEN_PLUS mulexpr
        {
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::ADD);
                } else {
                        DECLARE_ERROR("Types not same.");
                }    
        } |

        sumexpr TOKEN_MINUS mulexpr 
        { 
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::SUB);
                } else {
                        DECLARE_ERROR("Types not same.");
                }
        } |

        mulexpr { $$.type = $1.type; } ;


mulexpr : 
        mulexpr TOKEN_STAR unexpr
        {
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::MUL);
                } else {
                        DECLARE_ERROR("Types not same.");
                }    
        } |

        mulexpr TOKEN_SLASH unexpr
        {
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::DIV);
                } else {
                        DECLARE_ERROR("Types not same.");
                }
        } |

        mulexpr TOKEN_MODULO unexpr
        {
                if($1.type == DataType::INT && $3.type == DataType::INT) {
                        vm.write_op(OP::MOD);
                } else {
                        DECLARE_ERROR("Types not same.");
                }
        } |

        unexpr { $$.type = $1.type; } ;
    

unexpr : 
        TOKEN_MINUS smolexpr
        {
                if($2.type == DataType::INT) {
                        vm.write_op(OP::NEG);
                } else {
                        DECLARE_ERROR("Types not same.");
                }
                $$.type = $2.type;
        } |
        
        smolexpr { $$.type = $1.type; } ;
    

smolexpr : 
        TOKEN_INT_VAL
        {
                vm.write_constant_op(OP::CONST, $1.as.int_val);
                $$.type = DataType::INT;
        } |

        TOKEN_NIL
        {
                vm.write_op(OP::CONST_0);
                $$.type = DataType::NIL; 
        } |

        TOKEN_STR_VAL
        {
                vm.write_constant_op(OP::CONST, (u64) $1.as.str_val);
                $$.type = DataType::STR;
        } |

        TOKEN_PAREN_L expr TOKEN_PAREN_R { $$.type = $2.type; } |

        TOKEN_IDENTIFIER TOKEN_SQ_BRACK_L args TOKEN_SQ_BRACK_R
        {
                string ident = $1.as.str_val;
                SymbolEntry entry;
                bool is_global;
                if(!check_symbol(ident, entry, is_global)) DECLARE_ERROR("Undeclared identifier");
                if(!is_arr_type(entry.type)) DECLARE_ERROR("Cannot use subscript operator on a non-array type");
                for(auto arg : argv)
                {
                        if(arg.type != DataType::INT) DECLARE_ERROR("Array dimensions can only be of type \"int\"");
                }

                vm.write_op(is_global ? OP::GLOB_VARGET : OP::VARGET);
                vm.write_byte(entry.id);
                vm.write_op(OP::ARRGET);

                argv.clear();
                $$.type = convert_from_arr_type(entry.type);
        } |

        callexpr |

        TOKEN_IDENTIFIER
        {
                string ident = $1.as.str_val;
                SymbolEntry entry;
                bool is_global;
                if(!check_symbol(ident, entry, is_global)) DECLARE_ERROR("Undeclared identifier");

                vm.write_op(is_global ? OP::GLOB_VARGET : OP::VARGET);
                vm.write_byte(entry.id);
                $$.type = entry.type;
                $$.as.int_val = entry.dim_count;
        } ;
    

callexpr : 
        TOKEN_IDENTIFIER TOKEN_PAREN_L args TOKEN_PAREN_R
        {
                string ident = $1.as.str_val;
                FuncEntry nat, func;
                bool is_nat = check_native(ident, nat);
                if(!is_nat && !check_func(ident, func)) DECLARE_ERROR("Undefined function");
                if(is_nat) func = nat;

                if(func.paramTypes.size() != argv.size()) DECLARE_ERROR("Number of function parameters and arguments do not match");

                for(usize i = 0, size = argv.size(); i < size; i++)
                {
                        if(func.paramTypes.at(i) != argv.at(i).type) DECLARE_ERROR("Function parameter and argument type mismatch");
                        if(is_arr_type(argv.at(i).type) && func.param_dim_counts.at(i) != argv.at(i).dim_count)
                                DECLARE_ERROR("Function array parameter and argument dimension count mismatch");
                }
                argv.clear();

                vm.write_op(is_nat ? OP::CALL_NAT : OP::CALL);
                vm.write_dword(func.pc);
                if(is_nat) vm.write_byte(static_cast<u8>(func.paramTypes.size()));

                $$.type = func.retType;
                $$.as.int_val = func.ret_dim_count;
        } ;


args : 
        args_ | ;


args_ : 
        args_ TOKEN_COMMA expr
        {
                argv.push_back({ $3.type, $3.as.int_val });
        } |

        expr
        {
                argv.push_back({ $1.type, $1.as.int_val });
        } ;
    
    
%%
    
void yyerror(const char *msg)
{
    fprintf(stderr, "SYNTAX ERROR <Line %d>: %s\n", yylineno, msg);
}
