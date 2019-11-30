%{

#include "calc.tab.h"
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
{TAG} {col++; yylval.str=strdup(yytext); return TAG;}
{integer} {col++; yylval.integer=atoi(yytext); return INTEGER;}
{real} { yylval.num=atof(yytext); return REAL; }


"+" return PLUS;
"-" return MINUS;
"*" return TIMES;
"/" return DIVIDE;
"^" return POWER;
"(" return LEFT;
")" return RIGHT;
"=" return EQUAL;
";" return END;

%%

// yylloc.firstline = 34