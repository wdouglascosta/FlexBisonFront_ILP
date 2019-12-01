#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStruct.h"

typedef struct NODE {
    enum {
        TP_OPBIN,
        TP_TAG,
        TP_UNIT_REAL,
        TP_UNIT_INT,
        TP_ATR,
        TP_PRINT
    } TP;
    int LINE;
    int COL;
    union {
        struct VAL_OPBIN{
            enum {OP_ADD = 1, OP_MINUS, OP_TIMES, OP_DIVIDE, OP_EXPO} OP;
            struct NODE * EX_L;
            struct NODE * EX_D;
        }VAL_OPBIN;
        char *VAL_TAG;
        float VAL_REAL;
        int VAL_INT;
        struct VAL_ATR{
            char *tag;
            struct NODE * VALOR;
        } VAL_ATR;
        struct NODE * VAL_PRINT;
        
        
    }VALUE;
}NODE;

struct AST{
    struct NODE * head;
    struct AST * tail;
};


struct AST *root;

struct AST *insertNodeList(struct AST *lista, NODE *node){
    if (lista == NULL ){
        struct AST *monoList = malloc(sizeof(struct AST));
        monoList ->head = node;
        monoList ->tail = NULL;
        root = monoList;
        return monoList;
    } else {
        insertLastNode(lista, node);
        return root;
    }
}

void insertLastNode(struct AST *listasub, struct NODE *nodesub){
        if (listasub ->tail == NULL){
            struct AST *new = malloc(sizeof(struct AST));
            new -> head = nodesub;
            new -> tail = NULL;
            listasub ->tail = new;
        } else {
            insertLastNode(listasub ->tail, nodesub);
        };
}


NODE *create_TP_unit_Integer(int UNITVALUE, int LINE, int COL){

    struct NODE *new = malloc(sizeof(NODE));
    new -> TP = TP_UNIT_INT;
    new -> VALUE.VAL_INT = UNITVALUE;
    new -> LINE = LINE;
    new -> COL = COL;
    
    return new;
}

NODE *create_TP_unit_Real(float UNITVALUE, int LINE, int COL){

    struct NODE *new = malloc(sizeof(NODE));
    new -> TP = TP_UNIT_REAL;
    new -> VALUE.VAL_REAL = UNITVALUE;
    new -> LINE = LINE;
    new -> COL = COL;
    
    return new;
}

NODE *create_TPBIN(NODE * Left, NODE *Right, int op, int LINE, int COL){
    struct NODE *new = malloc(sizeof(NODE));
    new -> TP = TP_OPBIN;
    new -> VALUE.VAL_OPBIN.EX_L = Left;
    new -> VALUE.VAL_OPBIN.EX_D = Right;
    new -> VALUE.VAL_OPBIN.OP = op;
    new -> LINE = LINE;
    new -> COL = COL;
    
    return new;
}

NODE *create_TP_Print(NODE *no, int line, int colum){
    NODE *new = malloc(sizeof(NODE));
    new -> TP = TP_PRINT;
    new -> VALUE.VAL_PRINT = no;
    new -> LINE = line;
    new -> COL = colum;
    return new;
}
NODE *create_TP_ATR(char *var, NODE *no, int line, int colum){
    NODE *new = malloc(sizeof(NODE));
    new -> TP = TP_ATR;
    new -> VALUE.VAL_ATR.tag = var;
    new -> VALUE.VAL_ATR.VALOR = no;
    new -> LINE = line;
    new -> COL = colum;
    return new;
}

NODE *create_TP_TAG(char *var, int line, int colum){
    NODE *new = malloc(sizeof(NODE));
    new -> TP = TP_TAG;
    new -> VALUE.VAL_TAG = var;
    new -> LINE = line;
    new -> COL = colum;
    return new;
}

void printTree(struct AST *branch){
    if (branch == NULL || branch -> head == NULL)    {
        printf("----\nÁrvore ou ramo vazio.\n----\n");
        return;
    }
    printNode(branch ->head, 0);

    if (branch ->tail == NULL){
        printf("FIM\n");
        return;
    }else{
        printTree(branch ->tail);
    }
}
void printTab(int tab){
    for (int i = 0; i < tab; i++)    {
        printf("--");
    }
    
}
void printNode(NODE *no, int tab){
    tab++;
    printTab(tab);
    printf("Linha: %d\n", no->LINE);
    printTab(tab);
    printf("Colun: %d\n", no->COL);
    switch (no -> TP)
    {
    case TP_OPBIN:
        printf("|OP BIN|\n");
        printTab(tab);
        printf("Operação: %d\n", no ->VALUE.VAL_OPBIN.OP);
        printTab(tab);
        printf("Exp Esq ->\n");
        printTab(tab);
        printNode(no->VALUE.VAL_OPBIN.EX_L, tab);
        printTab(tab);
        printf("Exp Dir ->\n");
        printTab(tab);
        printNode(no->VALUE.VAL_OPBIN.EX_D,tab);
        break;
    case TP_UNIT_INT:
        printf("|TP_UNIT_INT|\n");
        printTab(tab);
        printf("Inteiro: ");
        printf("%d\n", no->VALUE.VAL_INT);
        break;
    case TP_UNIT_REAL:
        printf("| TP_UNIT_REAL |\n");
        printTab(tab);
        printf("Real: ");
        printf("%f\n", no->VALUE.VAL_REAL);
        break;

    case TP_PRINT:
        printf("| TP PRINT |\n");
        printTab(tab);
        printf("Exp ->\n");
        printTab(tab);
        printNode(no ->VALUE.VAL_PRINT,tab);
        break;
    case TP_ATR:
        printf("| TP ATR |\n");
        printTab(tab);
        printf("Nome Var: %s\n", no ->VALUE.VAL_ATR.tag);
        printTab(tab);
        printf("Valor -> \n");
        printTab(tab);
        printNode(no->VALUE.VAL_ATR.VALOR, tab);
        break;
    case TP_TAG:
        printf("| TP TAG |\n");
        printTab(tab);
        printf("Nome Var: %s\n", no ->VALUE.VAL_TAG);
        printTab(tab);
        break;

    default:
        break;
    }
}
    
void insertRoot(struct AST *lista){
    root = lista;
    printf("caiu na insert Root!\n");
}
// enum yytokentype
//   {
//     NUMBER = 258,
//     LEFT = 259,
//     RIGHT = 260,
//     PLUS = 261,
//     MINUS = 262,
//     TIMES = 263,
//     DIVIDE = 264,
//     POWER = 265,
//     END = 266,
//     PRINT = 267,
//     TAG = 268,
//     EQUAL = 269,
//     REAL = 270,
//     INTEGER = 271,
//     NEG = 272
//   };
