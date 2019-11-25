#ifndef TREE_H  // guardas de cabeçalho, impedem inclusões cíclicas
#define TREE_H

struct NODE;
extern int teste1;
extern struct NODE *tree ;    // declaração de uma variável global
                   // como é global, valor inicial é zero.
void startTree();
// struct NODE *teste();
void printTree();
void teste(char *c);
// int foo(long arg); // declaração de uma função
// int bar(void);     // outra

#endif