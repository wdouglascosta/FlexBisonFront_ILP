#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStruct.h"

typedef enum TP {
    TP_opbin_F = 1,
    TP_opbin_E,
    TP_atrib,
    TP_unit_value,
    TP_print
} TP;

typedef union 
{
    struct OP_BIN_F{
        char *OPERATION;
        union NUMBER VAL1;
        union NUMBER VAL2;
    } OP_BIN_F;

    struct OP_BIN_E{
        char *OPERATION;
        struct NODE *SUB1;
        struct NODE *SUB2;
    } OP_BIN_E;

    struct OP_ATR{
        char *TAG;
        union NUMBER VAL1
    } OP_ATR;
    union NUMBER UNITVALUE;
    char *OP_PRINT;       
} NODE_val;

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
            enum {ADD, MINUS, TIMES, DIVIDE, EXPO} OP;
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

NODE *create_TPBIN(NODE * Left, NODE *Right, char *op, int LINE, int COL){
    struct NODE *new = malloc(sizeof(NODE));
    new -> TP = TP_OPBIN;
    new -> VALUE.VAL_OPBIN.EX_L = Left;
    new -> VALUE.VAL_OPBIN.EX_D = Right;
    new -> VALUE.VAL_OPBIN.OP = op;
    new -> LINE = LINE;
    new -> COL = COL;
    
    return new;
}


















char *NumberToString(union NUMBER n){
    if (n.integer != NULL){
        return n.integer;
    }else{
        char toReturn[100];
        gcvt(n.real, 16, toReturn);
        return toReturn;
    }
}

char *getTypeNode(TP type){
    switch (type)
    {
    
        case TP_opbin_F:
        return "TP_opbin_F";
        break;
        
        case TP_opbin_E:
        return "TP_opbin_E";
        break;
        
        case TP_atrib:
        return "TP_atrib";
        break;

        case TP_unit_value:
        return "TP_unit_value";
        break;

        case TP_print:
        return "TP_print";
        break;
    
        default:
        return "ERROR";
            break;
    }
}

void printNodeValue(NODE_val value){

}

struct NODE *createNode(TP Type, NODE_val Values, int LINE, int COL){
    nos++;
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
        printf(" coluna:");
        printf("%d", tmp->COL);
        printf("\n");
        printf("Tipo: ");
        printf(getTypeNode(tmp->Type));
        printf("\n");
        printf("\n");
        
        // switch (tmp -> Type){
        
        // break;
        
        // case TP_opbin_E:
        // return "TP_opbin_E";
        // break;
        
        // case TP_atrib:
        // return "TP_atrib";
        // break;

        // case TP_unit_value:
        // return "TP_unit_value";
        // break;

        // case TP_print:
        // return "TP_print";
        // break;
        // }
        
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

void insertNextNode(struct NODE *new){
    if (tree == NULL){
        tree = new;
    } else {

        insertLastNode(tree, new);
    }
    
    
}

insertRoot(NODE *no){
    tree = no;
}

NODE *create_OP_BIN_F(int a, int b, char *OP){
    NODE *new;
    cont++;
    NODE_val values ;
    values.OP_BIN_F.OPERATION = OP;
    values.OP_BIN_F.VAL1.integer = a;
    values.OP_BIN_F.VAL2.integer = b;

    new = createNode(1, values, cont, cont+1);

    return new;
}
NODE *create_EX_BIN_E(NODE *no1, NODE *no2, char *op){
    NODE *new;
    NODE_val value;
    value.OP_BIN_E.SUB1 = no1;
    value.OP_BIN_E.SUB2 = no2;
    value.OP_BIN_E.OPERATION = op;

    new = createNode(2,value,1,1);
    return new;
}

NODE *create_TP_unit_Real(float UNITVALUE){
    NODE *new;
    NODE_val value;

    value.UNITVALUE.real = UNITVALUE;
    
    new = createNode(4, value, 100, 101);
    return new;
}



NODE *create_TP_Print(struct NODE *ex){
    NODE_val value;
    NODE *new;

     new = createNode(4, value, 100, 101);
    return new;
}
