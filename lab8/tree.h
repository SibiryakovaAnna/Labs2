#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#include "structs.h"

Tree* new_tree(unsigned char s, int f);
Tree* CodeTree(Stack** stack);
Tree* merge(Tree* first, Tree* second);
void writeTree(Tree* codeTree, BitStream* bitStream, FILE* out);
void freeTree(Tree* tree);
Tree* getCodeTree(FILE* in, BitStream* bitStream);

#endif
