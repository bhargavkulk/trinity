%{
#include <cstdlib>
#include <cstring>
#include "parser.hh"
%}

%option noyywrap
%option yylineno

%%

int                             return TOKEN_INT;
str                             return TOKEN_STR;
blk                             return TOKEN_BLK;
fun                             return TOKEN_FUN;
if                              return TOKEN_IF;
else                            return TOKEN_ELSE;
for                             return TOKEN_FOR;
from                            return TOKEN_FROM;
to                              return TOKEN_TO;
while                           return TOKEN_WHILE;
var                             return TOKEN_VAR;
brk                             return TOKEN_BRK;
cnt                             return TOKEN_CNT;
ret                             return TOKEN_RET;
nil                             return TOKEN_NIL;
!grid                           return TOKEN_DIR_GRID;
!title                          return TOKEN_DIR_TITLE;
!icon                           return TOKEN_DIR_ICON;

\[                              return TOKEN_SQ_BRACK_L;
\]                              return TOKEN_SQ_BRACK_R;
\(                              return TOKEN_PAREN_L;
\)                              return TOKEN_PAREN_R;
\{                              return TOKEN_BRACE_L;
\}                              return TOKEN_BRACE_R;
\+                              return TOKEN_PLUS;
\-                              return TOKEN_MINUS;
\/                              return TOKEN_SLASH;
\*                              return TOKEN_STAR;
\%                              return TOKEN_MODULO;
==                              return TOKEN_DOUBLE_EQ;
!=                              return TOKEN_NOT_EQ;
\>=                             return TOKEN_GREATER_EQ;
\<=                             return TOKEN_LESS_EQ;
=                               return TOKEN_EQUAL;
\<                              return TOKEN_LESS;
\>                              return TOKEN_GREATER;
&&                              return TOKEN_LOGICAL_AND;
\|\|                            return TOKEN_LOGICAL_OR;
!                               return TOKEN_LOGICAL_NOT;
\;                              return TOKEN_SEMICOLON;
:                               return TOKEN_COLON;
,                               return TOKEN_COMMA;

[_a-zA-Z][a-zA-Z0-9_\?]*		{ yylval.as.str_val = strndup(yytext, yyleng); return TOKEN_IDENTIFIER; }
0x[0-9A-Fa-f]+	 				{ yylval.as.int_val = strtol(yytext, NULL, 16); return TOKEN_INT_VAL; }
[0-9]+ 							{ yylval.as.int_val = strtol(yytext, NULL, 10); return TOKEN_INT_VAL; }
\"([^\\\"]|\\.)*\"				{ yylval.as.str_val = strndup(yytext + 1, yyleng - 2); return TOKEN_STR_VAL; }


[ \t\n\r]+						;
.								return TOKEN_ERR;

%%
