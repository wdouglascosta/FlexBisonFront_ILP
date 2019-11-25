#include <stdio.h>
#include <stdlib.h>
#include "dataStruct.h"



union NUMBER{
    int integer;
    float real;
};

typedef enum TP {
    TP_opbin_F,
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
    struct NODE *sub;
}NODE;


NODE *tree ;
int teste1;

void startTree(){
    tree = (NODE *) malloc(sizeof(NODE));
}

struct NODE *createNode(TP Type, NODE_val Values, int LINE, int COL){
    struct NODE *node = malloc(sizeof(NODE));
    node -> Type = Type;
    node -> VALUES = Values;
    node -> LINE = LINE;
    node -> COL = COL;
    return node;
};

void teste(){
    printf("chamada interna de funçãon\n");
}

void printTree(){
    NODE *tmp;
    tmp = tree;
    while( tmp != NULL){
        printf("linha:");
        printf("%d", tmp->LINE);
        printf("\n");
        tmp = tmp->next;
    }
}

// int main(int argc, char const *argv[]){


//     NODE *no;
//     NODE *no2;
//     NODE *no3;


//     NODE_val values ;
//     values.OP_BIN_F.OPERATION = "ADD";
//     values.OP_BIN_F.VAL1.integer = 3;
//     values.OP_BIN_F.VAL2.integer = 5;

//     no3 = createNode(1, values, 1, 4);
//     no = createNode(1, values, 7, 8);
//     no2 = createNode(1, values, 50, 78);
//     // tree ->next = no;
//     startTree();


//     no3 ->next = no;
//     no ->next = no2;
//     tree -> next = no3;
    
//     printTree();
    
//     printf("fim\n");

//     return 0;

// }
