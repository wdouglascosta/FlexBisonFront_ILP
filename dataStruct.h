#ifndef TREE_H  // guardas de cabeçalho, impedem inclusões cíclicas
#define TREE_H

struct NODE;
extern struct AST *root ;    // declaração de uma variável global
                   // como é global, valor inicial é zero.
// struct NODE *teste();
void printTree();
// int foo(long arg); // declaração de uma função
// int bar(void);     // outra

#endif