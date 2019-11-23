%{

#include "calc.tab.h"

%}

white [ \t]+
digit [0-9]
integer {digit}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})?{exponent}?
TAG ^[a-zA-Z_$][a-zA-Z_$0-9]*

%%

{white} { }
{TAG} { yylval.str=strdup(yytext); return TAG;}
{integer} {yylval.integer=atoi(yytext); return INTEGER;}
{real} { yylval.num=atof(yytext); return REAL; }


"print" return PRINT;
"+" return PLUS;
"-" return MINUS;
"*" return TIMES;
"/" return DIVIDE;
"^" return POWER;
"(" return LEFT;
")" return RIGHT;
"=" return EQUAL;
"\n" return END;
