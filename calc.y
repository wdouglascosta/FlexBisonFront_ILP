%{
#include <math.h>
#include <stdio.h>
#include "dataStruct.c"


int yyerror (char const *s);
extern int yylex (void);
extern FILE *yyin;

  int line;
  int colum;
  line = 0;
  colum = 0;
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
%token END_PROGRAM
%token <node> PRINT
%token<str> TAG
%token EQUAL
%token<num> REAL
%token<integer> INTEGER

%type<node> Exp
%type<list> List_Exp
%type<list> Program

%left EQUAL
%left PLUS MINUS
%left TIMES DIVIDE
%left POWER
%right NEG

%define parse.error verbose

%start Program

%%

Program: List_Exp END_PROGRAM {insertRoot($1);return;}

List_Exp: END
List_Exp: List_Exp Exp END {$$ = insertNodeList($1, $2);}
List_Exp: Exp END {$$ = insertNodeList(NULL, $1);}

Exp: TAG                  {$$ = create_TP_TAG($1, @1.first_line, @1.first_column);}
Exp: PRINT LEFT Exp RIGHT {$$ = create_TP_Print($3, @1.first_line, @1.first_column);}
Exp: INTEGER              {$$ = create_TP_unit_Integer($1, @1.first_line, @1.first_column); };
Exp: REAL                 {$$ = create_TP_unit_Real($1, @1.first_line, @1.first_column); };
Exp: Exp PLUS Exp         {$$ = create_TPBIN($1, $3, 1 ,@1.first_line, @1.first_column);}
Exp: Exp MINUS Exp        {$$ = create_TPBIN($1, $3, 2, @1.first_line, @1.first_column);}
Exp: Exp TIMES Exp        {$$ = create_TPBIN($1, $3, 3, @1.first_line, @1.first_column);}
Exp: Exp DIVIDE Exp       {$$ = create_TPBIN($1, $3, 4, @1.first_line, @1.first_column);}
Exp: TAG EQUAL Exp        {$$ = create_TP_ATR($1, $3, @1.first_line, @1.first_column);}

%%

int yyerror(char const *s) {
  printf("Erro Sintático, Linha %d - Coluna %d\n", yylloc.first_line, yylloc.first_column);
  printf("%s\n", s);
  
}

int main() {
    yyin = fopen("code.txt", "r");
    int ret = yyparse();
    printTree(root);
    if (ret){
	    fprintf(stderr, "%d error found.\n",ret);
    }

    return 0;
// printf("%d is defined at line %d and Col %d\n", $1, @1.first_line, @1.first_column);
}
