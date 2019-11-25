%{
#include <math.h>
#include <stdio.h>
#include "dataStruct.c"

int yyerror (char const *s);
extern int yylex (void);

%}

%union{
  char *str;
  double num;
  int integer;
}

%token<num> NUMBER
%token LEFT RIGHT
%token PLUS MINUS TIMES DIVIDE POWER
%token END
%token PRINT
%token<str> TAG
%token EQUAL
%token<num> REAL
%token<integer> INTEGER

%type<num> Expression

%left PLUS MINUS
%left TIMES DIVIDE
%left NEG
%right POWER

%define parse.error verbose

%start Input
%%

Input: /* empty */;
Input: Input Line;

Line: END
Line: REAL {printf("isso é um real: %f\n", $1);}
Line: INTEGER {printf("isso é um inteiro: %d\n", $1);}
Line: Expression END { printf("Result: %f\n", $1); }
Line: PRINT Expression { printf("esse é o meu print: %f\n", $2);}
Line: TAG EQUAL Expression {printf("o valor de %s: %f\n", $1, $3);}

Expression: INTEGER { $$=$1; startTree(); printTree("charizanr");};
Expression: REAL { $$=$1; printf("novo print\n");};

Expression: REAL PLUS REAL { $$ =$1 + $3; };
Expression: INTEGER PLUS INTEGER { $$ =$1 + $3; };
Expression: Expression PLUS Expression { $$ =$1 + $3; };
Expression: Expression MINUS Expression { $$ = $1 - $3; };
Expression: Expression TIMES Expression { $$ = $1 * $3; };
Expression: Expression DIVIDE Expression { $$ = $1 / $3; };
Expression: MINUS Expression %prec NEG { $$ = -$2; };
Expression: Expression POWER Expression { $$ = pow($1, $3); };
Expression: LEFT Expression RIGHT { $$ = $2; };

%%

int yyerror(char const *s) {
  printf("%s\n", s);
}

int main() {
    int ret = yyparse();
    startTree();
    if (ret){
	    fprintf(stderr, "%d error found.\n",ret);
    }


    return 0;
}

