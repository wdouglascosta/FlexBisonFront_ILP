%{
#include <math.h>
#include <stdio.h>
#include "dataStruct.c"


int yyerror (char const *s);
extern int yylex (void);

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

%left PLUS MINUS
%left TIMES DIVIDE
%left POWER
%left EQUAL
%right NEG

%define parse.error verbose

%start Program

%%

Program: List_Exp END_PROGRAM {printf("---INICIAL -> ListaEx---\n");insertRoot($1);return;}

List_Exp: END
List_Exp: List_Exp Exp END {$$ = insertNodeList($1, $2);}
List_Exp: Exp END {printf("---Expressão---\n");line =+ 1;$$ = insertNodeList(NULL, $1);}

Exp: TAG                  {$$ = create_TP_TAG($1, line, colum);}
Exp: PRINT LEFT Exp RIGHT {$$ = create_TP_Print($3, line, colum);}
Exp: INTEGER              {$$ = create_TP_unit_Integer($1, line, @1.first_column); };
Exp: REAL                 {$$ = create_TP_unit_Real($1, line, colum); };
Exp: Exp PLUS Exp         {$$ = create_TPBIN($1, $3, 1 ,line, colum);}
Exp: Exp MINUS Exp        {$$ = create_TPBIN($1, $3, 2, line, colum);}
Exp: Exp TIMES Exp        {$$ = create_TPBIN($1, $3, 3, line, colum);}
Exp: Exp DIVIDE Exp       {$$ = create_TPBIN($1, $3, 4, line, colum);}
Exp: TAG EQUAL Exp        {$$ = create_TP_ATR($1, $3, line, colum);}

%%

int yyerror(char const *s) {
  printf("%s\n", s);
  
}

int main() {

    int ret = yyparse();
    printTree(root);
    printf("aqui o programa ACABOU \n");
    if (ret){
	    fprintf(stderr, "%d error found.\n",ret);
    }
    return 0;
}

