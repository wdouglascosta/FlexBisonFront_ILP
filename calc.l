%{

#include "calc.tab.h"
# include <stdio.h>
# include <stdlib.h>
#include <string.h>
#define YY_USER_ACTION yylloc.first_line = yylineno;
int col;
%}
%option yylineno
white [ \t]+
digit [0-9]
integer {digit}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})?{exponent}?
TAG ^[a-zA-Z_$][a-zA-Z_$0-9]*

%%
"fim" return END_PROGRAM;
"print" return PRINT;

{white} {yylloc.first_column++; }
{TAG} {yylloc.first_column=+strlen(yytext); yylval.str=strdup(yytext); return TAG;}
{integer} {yylloc.first_column =+ strlen(yytext);yylval.integer=atoi(yytext);return INTEGER;}
{real} { yylloc.first_column =+ strlen(yytext);yylval.num=atof(yytext); return REAL; }

"\n" { }
"=" {yylloc.first_column++; return EQUAL;}
"+" {yylloc.first_column++; return PLUS;}
"-" {yylloc.first_column++; return MINUS;}
"*" {yylloc.first_column++; return TIMES;}
"/" {yylloc.first_column++; return DIVIDE;}
"^" {yylloc.first_column++; return EXPO;}
"(" {yylloc.first_column++; return LEFT;}
")" {yylloc.first_column++; return RIGHT;}
";" {yylloc.first_column++; return END;}

%%
int columnCalc(int step){
    col = yylloc.first_column + col;
    return col;
}
// yylloc.firstline = 34