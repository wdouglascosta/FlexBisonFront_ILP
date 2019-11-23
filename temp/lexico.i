%{


#include<stdio.h>
#include<string.h>

//#define PRINT(STR) {};
#define PRINT(STR) printf("%s    # %s \n", STR, token);
int nl = 1;  

%}
tk_tag ^[a-zA-Z_$][a-zA-Z_$0-9]*$

tk_integer [0-9]+

tk_float [-+]?[0-9]*\.?[0-9]+

tk_print print


comentario "(*".*"*)"

%%

= { simbolo = tk_atribuicao;  
          strncpy (token, yytext, TAM_TOKEN);
          PRINT("atribuiçao ")
          //return ATRIBUICAO;  
 }



\, { simbolo = tk_virgula;  
          strncpy (token, yytext, TAM_TOKEN);
          PRINT("virgula ")
          //return VIRGULA;
 }


\. { simbolo = tk_ponto;  
          strncpy (token, yytext, TAM_TOKEN);
          PRINT("ponto ")
          //return PONTO; 
    }

\(  { simbolo = tk_abre_parenteses;  
          strncpy (token, yytext, TAM_TOKEN);
          PRINT("abre_parenteses ")
          //return ABRE_PARENTESES;
    }

\)  { simbolo = tk_fecha_parenteses;  
          strncpy (token, yytext, TAM_TOKEN);
          PRINT("fecha_parenteses ")
          //return FECHA_PARENTESES;
 }

\+  { simbolo = tk_soma;  
          strncpy (token, yytext, TAM_TOKEN);
          PRINT("soma ")
          \\return SOMA;
 }

\-  { simbolo = tk_sub;  
          strncpy (token, yytext, TAM_TOKEN);
          PRINT("subtracao ")
        //   return SUBTRACAO;
 }

\*  { simbolo = tk_multiplicacao;  
          strncpy (token, yytext, TAM_TOKEN);
          PRINT("multiplicacao ")
        //   return MULTIPLICACAO;
 }

%%

main(){
	return yylex();
}
