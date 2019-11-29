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
    new -> VALUE.VAL_OPBIN.OP = 1;
    new -> LINE = LINE;
    new -> COL = COL;
    
    return new;
}


















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


// void insertLastNode(struct NODE *tree, struct NODE *new){
//         if (tree ->next == NULL){
//             tree ->next = new;
//         } else {
//             insertLastNode(tree ->next, new);
//         };
// }

// void insertNextNode(struct NODE *new){
//     if (tree == NULL){
//         tree = new;
//     } else {

//         insertLastNode(tree, new);
//     }   
// }

insertRoot(NODE *no){
    tree = no;
}
