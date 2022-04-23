    %code top
    {
    #include <cstdio>
    #include "vm.hh"
     
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
             | TOKEN_VAR TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SQ_BRACK_L args TOKEN_SQ_BRACK_R TOKEN_EQUAL TOKEN_SQ_BRACK_L args TOKEN_SQ_BRACK_R TOKEN_SEMICOLON
             ;
     
    function : TOKEN_FUN TOKEN_IDENTIFIER TOKEN_PAREN_L params TOKEN_PAREN_R TOKEN_COLON type blckstmt
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
     
    type : TOKEN_INT
    	 | TOKEN_STR
    	 | TOKEN_BLK;
     
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
         ;
     
    retstmt : TOKEN_RET TOKEN_SEMICOLON
            | TOKEN_RET expr TOKEN_SEMICOLON
            ;
     
    whilestmt : TOKEN_WHILE expr blckstmt
              ;
     
    forstmt : TOKEN_FOR TOKEN_IDENTIFIER TOKEN_FROM expr TOKEN_TO expr blckstmt
            ;
     
    ifstmt  : TOKEN_IF expr blckstmt
            | TOKEN_IF expr blckstmt TOKEN_ELSE blckstmt
            ;
     
    asgnstmt : TOKEN_IDENTIFIER TOKEN_EQUAL expr TOKEN_SEMICOLON
             | TOKEN_IDENTIFIER TOKEN_SQ_BRACK_L expr TOKEN_SQ_BRACK_R TOKEN_EQUAL expr TOKEN_SEMICOLON
             ;
     
    blckstmt : openbrace stmts TOKEN_BRACE_R
    		 ;
     
    openbrace :	TOKEN_BRACE_L
    		  ;
     
    expr : expr TOKEN_LOGICAL_OR andexpr 
         | andexpr
         ;
     
    andexpr : andexpr TOKEN_LOGICAL_AND notexpr
            | notexpr
            ;
     
    notexpr : TOKEN_LOGICAL_NOT relexpr 
            | relexpr
            ;
     
    relexpr : relexpr TOKEN_LESS_EQ sumexpr
            | relexpr TOKEN_GREATER_EQ sumexpr
            | relexpr TOKEN_LESS sumexpr
            | relexpr TOKEN_GREATER sumexpr
            | relexpr TOKEN_DOUBLE_EQ sumexpr
            | relexpr TOKEN_NOT_EQ sumexpr
            | sumexpr
            ;
     
    sumexpr : sumexpr TOKEN_PLUS mulexpr
            | sumexpr TOKEN_MINUS mulexpr
            | mulexpr
            ;
     
    mulexpr : mulexpr TOKEN_STAR unexpr
            | mulexpr TOKEN_SLASH unexpr
            | mulexpr TOKEN_MODULO unexpr
            | unexpr
            ;
     
    unexpr : TOKEN_MINUS smolexpr
           | smolexpr
           ;
     
    smolexpr : TOKEN_INT_VAL
        {
                vm.write_constant_op(OP::CONST, $1.as.int_val);
        }

             | TOKEN_STR_VAL
             | TOKEN_PAREN_L expr TOKEN_PAREN_R
             | TOKEN_IDENTIFIER TOKEN_SQ_BRACK_L expr TOKEN_SQ_BRACK_R
             | callexpr
             | TOKEN_IDENTIFIER
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
    	fprintf(stderr, "Syntax error: %s\n", msg);
    }