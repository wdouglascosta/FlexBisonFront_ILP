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
            enum {OP_ADD, OP_MINUS, OP_TIMES, OP_DIVIDE, OP_EXPO} OP;
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

void printTree(){
    printf("oooi gentiii\n");
}


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

insertRoot(NODE *no){
    root = no;
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
















// char *getTypeNode(TP type){
//     switch (type)
//     {
    
//         case TP_opbin_F:
//         return "TP_opbin_F";
//         break;
        
//         case TP_opbin_E:
//         return "TP_opbin_E";
//         break;
        
//         case TP_atrib:
//         return "TP_atrib";
//         break;

//         case TP_unit_value:
//         return "TP_unit_value";
//         break;

//         case TP_print:
//         return "TP_print";
//         break;
    
//         default:
//         return "ERROR";
//             break;
//     }
// }



