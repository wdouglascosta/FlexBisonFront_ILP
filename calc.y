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
  struct NODE *node;
  struct AST *list;
}

%token<num> NUMBER
%token LEFT RIGHT
%token PLUS MINUS TIMES DIVIDE POWER
%token END
%token <node> PRINT
%token<str> TAG
%token EQUAL
%token<num> REAL
%token<integer> INTEGER

%type<node> Exp
%type<list> List_Exp
%type<list> Program

%left PLUS MINUS
%left TIMES DIVIDE
%left NEG
%right POWER

%define parse.error verbose

%start Program
%%

Program: 
Program: END
Program: List_Exp {insertRoot($1);}
Program: PRINT END{printf("testeeee");}


List_Exp: Exp END {$$ = insertNodeList(NULL, $1);}
List_Exp: List_Exp Exp {$$ = insertNodeList($1, $2);}

Exp: INTEGER { $$ = create_TP_unit_Integer($1, 0, 0); };
Exp: REAL { $$ = create_TP_unit_Real($1, 0, 0); };
Exp: Exp PLUS Exp {$$ = create_TPBIN($1, $3, 261 ,0, 0);}

%%

int yyerror(char const *s) {
  printf("%s\n", s);
}

int main() {
    int ret = yyparse();
    
    if (ret){
	    fprintf(stderr, "%d error found.\n",ret);
    }


    return 0;
}

