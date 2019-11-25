#include <stdio.h>
#include <stdlib.h>
#include "dataStruct.h"

union NUMBER{
    int integer;
    float real;
};

typedef enum TP {
    TP_opbin_F = 1,
    TP_opbin_E,
    TP_atrib,
    TP_unit_value,
    TP_print
} TP;

typedef union 
{
    struct OP_BIN_F
    {
        char *OPERATION;
        union NUMBER VAL1;
        union NUMBER VAL2;
    } OP_BIN_F;

    struct OP_BIN_E
    {
        char *OPERATION;
        struct NODE *SUB1;
        struct NODE *SUB2;
    } OP_BIN_E;

    struct OP_ATR
    {
        char *TAG;
        union NUMBER VAL1
    } OP_ATR;



    union NUMBER UNITVALUE;
    char *OP_PRINT;       
} NODE_val;

typedef struct NODE {
    TP Type;

    NODE_val VALUES;

    int LINE;
    int COL;


    struct NODE *next;
}NODE;


NODE *tree ;
int cont;

void startTree(){
    if (tree == NULL){
        tree = (NODE *) malloc(sizeof(NODE));
    }
    
    
}

struct NODE *createNode(TP Type, NODE_val Values, int LINE, int COL){
    struct NODE *node = malloc(sizeof(NODE));
    node -> Type = Type;
    node -> VALUES = Values;
    node -> LINE = LINE;
    node -> COL = COL;
    return node;
};


void teste(int c){
    printf("chamada interna de função, valor: %d",c,"\n");
}

void printTree(){
    NODE *tmp;
    tmp = tree;
    while( tmp != NULL){
        printf("linha:");
        printf("%d", tmp->LINE);
                printf(" - coluna:");
        printf("%d", tmp->COL);
        printf("\n");
        tmp = tmp->next;
    }
}

void insertLastNode(struct NODE *tree, struct NODE *new){
        if (tree ->next == NULL){
            tree ->next = new;
        } else {
            insertLastNode(tree ->next, new);
        };
}

void create_OP_BIN_F(int a, int b, char *OP){
    NODE *new;
    cont++;
    NODE_val values ;
    values.OP_BIN_F.OPERATION = OP;
    values.OP_BIN_F.VAL1.integer = a;
    values.OP_BIN_F.VAL2.integer = b;

    new = createNode(1, values, cont, cont+1);

    insertLastNode(tree, new);
    
}

