#include <stdio.h> // a libc vai definir essas funções
#include "dataStruct.c"

int main() {
  struct NODE test1;
  printf("teste\n");


    NODE *no;
    NODE *no2;
    NODE *no3;

    NODE_val values ;
    values.OP_BIN_F.OPERATION = "ADD";
    values.OP_BIN_F.VAL1.integer = 3;
    values.OP_BIN_F.VAL2.integer = 5;

    no3 = createNode(1, values, 10, 4);
    no = createNode(1, values, 78, 8);
    no2 = createNode(1, values, 505, 78);
    // tree ->next = no;
    startTree();


    no3 ->next = no;
    no ->next = no2;
    tree -> next = no3;
    
    printTree();
    
    printf("fim\n");

}