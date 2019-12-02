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
        printf("___");
    }
    
}
void printNode(NODE *no, int tab){
    tab++;
    // printTab(tab);
    printf("Linha: %d\n", no->LINE);
    switch (no -> TP)
    {
    case TP_OPBIN:
        printTab(tab);
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
        printTab(tab);
        printf("|TP_UNIT_INT|\n");
        printTab(tab);
        printf("Inteiro: ");
        printf("%d\n", no->VALUE.VAL_INT);
        break;
    case TP_UNIT_REAL:
        printTab(tab);
        printf("| TP_UNIT_REAL |\n");
        printTab(tab);
        printf("Real: ");
        printf("%f\n", no->VALUE.VAL_REAL);
        break;

    case TP_PRINT:
        printTab(tab);
        printf("| TP PRINT |\n");
        printTab(tab);
        printf("Exp ->\n");
        printTab(tab);
        printNode(no ->VALUE.VAL_PRINT,tab);
        break;
    case TP_ATR:
        printTab(tab);
        printf("| TP ATR |\n");
        printTab(tab);
        printf("Nome Var: %s\n", no ->VALUE.VAL_ATR.tag);
        printTab(tab);
        printf("Valor -> \n");
        printTab(tab);
        printNode(no->VALUE.VAL_ATR.VALOR, tab);
        break;
    case TP_TAG:
        printTab(tab);
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
}
//MOTOR DE EXECUÇÃO====================================================================
struct cmdLine{
    char *cmd;
    struct cmdLine *next;
};
int i, j;


int run_OP_BIN_INT(NODE *opBin){
    
    if (opBin ->TP == TP_UNIT_INT){
        return opBin ->VALUE.VAL_INT;
        
    } else {
        switch (opBin->VALUE.VAL_OPBIN.OP)
        {
        case 1:
            /* ADD */
            i = run_OP_BIN_INT(opBin->VALUE.VAL_OPBIN.EX_L);
            j = run_OP_BIN_INT(opBin->VALUE.VAL_OPBIN.EX_D);
            
            return i + j; 
            break;
        case 2:
            /* MINUS */
            return run_OP_BIN_INT(opBin->VALUE.VAL_OPBIN.EX_L) - run_OP_BIN_INT(opBin->VALUE.VAL_OPBIN.EX_D) ;
            break;
        case 3:
            /* TIMES */
            return run_OP_BIN_INT(opBin->VALUE.VAL_OPBIN.EX_L) * run_OP_BIN_INT(opBin->VALUE.VAL_OPBIN.EX_D) ;
            break;
        case 4:
            /* DIVIDE */
            return run_OP_BIN_INT(opBin->VALUE.VAL_OPBIN.EX_L) / run_OP_BIN_INT(opBin->VALUE.VAL_OPBIN.EX_D) ;
            break;
        case 5:
            /* EXPO */
            return pow(run_OP_BIN_INT(opBin->VALUE.VAL_OPBIN.EX_L), run_OP_BIN_INT(opBin->VALUE.VAL_OPBIN.EX_D) );
            break;
        default:
            break;
        }
    }
    //OP_ADD = 1, OP_MINUS, OP_TIMES, OP_DIVIDE, OP_EXPO
}

float run_OP_BIN_REAL(NODE *opBin){
    if (opBin ->TP == TP_UNIT_REAL){
        return opBin ->VALUE.VAL_REAL;
        
    } else {
        switch (opBin->VALUE.VAL_OPBIN.OP)
        {
        case 1:
            /* ADD */
            return run_OP_BIN_REAL(opBin->VALUE.VAL_OPBIN.EX_L) + run_OP_BIN_REAL(opBin->VALUE.VAL_OPBIN.EX_D) ;
            break;
        case 2:
            /* MINUS */
            return run_OP_BIN_REAL(opBin->VALUE.VAL_OPBIN.EX_L) - run_OP_BIN_REAL(opBin->VALUE.VAL_OPBIN.EX_D) ;
            break;
        case 3:
            /* TIMES */
            return run_OP_BIN_REAL(opBin->VALUE.VAL_OPBIN.EX_L) * run_OP_BIN_REAL(opBin->VALUE.VAL_OPBIN.EX_D) ;
            break;
        case 4:
            /* DIVIDE */
            return run_OP_BIN_REAL(opBin->VALUE.VAL_OPBIN.EX_L) / run_OP_BIN_REAL(opBin->VALUE.VAL_OPBIN.EX_D) ;
            break;
        case 5:
            /* EXPO */
            return pow(run_OP_BIN_REAL(opBin->VALUE.VAL_OPBIN.EX_L), run_OP_BIN_REAL(opBin->VALUE.VAL_OPBIN.EX_D) );
            break;
        default:
            break;
        }
    }
    //OP_ADD = 1, OP_MINUS, OP_TIMES, OP_DIVIDE, OP_EXPO
}
void runEngine(struct AST *root){
    if (root == NULL){
        printf("Arvore de instruções vazia\n");
        return;
    } 
    if (root ->head->TP == TP_OPBIN ){
        
        printf("%d\n", run_OP_BIN_INT(root->head));
    }

    if (root -> head -> TP == TP_ATR){
        printf("%s: %d\n", root ->head->VALUE.VAL_ATR.tag, run_OP_BIN_INT(root ->head->VALUE.VAL_ATR.VALOR));
    }

    if (root ->tail == NULL){
        printf("***Fim da Execução***\n");
    
    } else {
        runEngine(root ->tail);
    }
    
    
    

    // FILE *fp = fopen("output.c", "wb");
    // char *compiled = "printf(\"maoeeee\");";
    // char *template = "#include <stdio.h> \n int main(){";
    // fputs(template, fp);
    // fputs(compiled, fp);
    // fputs("}", fp);
    // fclose(fp);


    /* Close file to save file data */
}


