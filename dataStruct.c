#include <stdio.h>
#include <stdlib.h>



union NUMBER{
    int integer;
    float real;
};

typedef enum TP {
    TP_opbin,
    TP_atrib,
    TP_print
} TP;

typedef union 
{
    struct OP_BIN
    {
        char *TAG;
        union NUMBER VAL1;
        union NUMBER VAL2;
    } OP_BIN;

    struct OP_ATR
    {
        char *TAG;
        union NUMBER VAL1
    } OP_ATR;

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

struct NODE *createNode(TP Type, NODE_val Values, int LINE, int COL){
    struct NODE *node = malloc(sizeof(NODE));
    node -> Type = Type;
    node -> VALUES = Values;
    node -> LINE = LINE;
    node -> COL = COL;
    return node;
};


NODE *teste(){
    NODE *noTeste = malloc(sizeof(NODE));
    noTeste -> next = NULL;
    noTeste -> sub = NULL;
    noTeste -> LINE = 66;
    return noTeste;
};

int main(int argc, char const *argv[]){
    // tree -> COL = 0;
    // tree -> LINE = 0;
    // tree -> Type = TP_opbin;
    // tree -> VALUES.OP_ATR.TAG = "oooi";
    // tree -> VALUES.OP_ATR.VAL1.integer = 12;

    NODE *list = (NODE *) malloc(sizeof(NODE));
    NODE *no = (NODE *) malloc(sizeof(NODE));
    NODE *no2 = (NODE *) malloc(sizeof(NODE));


    NODE_val values ;
    values.OP_BIN.TAG = "varTeste1";
    values.OP_BIN.VAL1.integer = 3;
    values.OP_BIN.VAL2.integer = 5;

    list = createNode(1, values, 1, 4);
    no = createNode(1, values, 7, 8);
    no2 = createNode(1, values, 50, 78);
    // tree ->next = no;

    list ->next = no;
    no ->next = no2;
    
    NODE *tmp;
    tmp = list;
    while( tmp != NULL){
        printf("linha:");
        printf("%d", tmp->LINE);
        printf("\n");
        tmp = tmp->next;
    }
    
    printf("imprime carai\n");

    return 0;

}
