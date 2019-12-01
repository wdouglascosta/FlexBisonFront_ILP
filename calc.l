%{

#include "calc.tab.h"
# include <stdio.h>
# include <stdlib.h>
#include <string.h>
extern int col = 0;

%}

white [ \t]+
digit [0-9]
integer {digit}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})?{exponent}?
TAG ^[a-zA-Z_$][a-zA-Z_$0-9]*

%%
"fim" return END_PROGRAM;
"print" return PRINT;
{white} { }
{TAG} {yylval.str=strdup(yytext); return TAG;}
{integer} {yylval.integer=atoi(yytext);printf("comprimeiro: %d\n", strlen(yytext));yylloc.first_column =+ strlen(yytext) ;return INTEGER;}
{real} { yylval.num=atof(yytext); return REAL; }


"=" {yylloc.first_column++; return EQUAL;}
"+" {yylloc.first_column++; return PLUS;}
"-" return MINUS;
"*" return TIMES;
"/" return DIVIDE;
"^" return POWER;
"(" return LEFT;
")" return RIGHT;
";" return END;

%%

// yylloc.firstline = 34