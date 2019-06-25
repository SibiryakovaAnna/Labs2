#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "tree.h"

Tree* new_tree(unsigned char s, int f) {                 
	Tree* tmp = (Tree*)malloc(sizeof(Tree));
	tmp->f = f;
	tmp->s = s;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}

Tree* CodeTree(Stack** stack) {                
	if (!(*stack)) {
		return NULL;
	}
	while ((*stack)->next) {
		push(stack, merge(pop(stack), pop(stack)));
	}
	return pop(stack);
}

Tree* merge(Tree* first, Tree* second) {           
	Tree* tmp = new_tree(0, first->f + second->f);
	tmp->left = second;
	tmp->right = first;
	return tmp;
}

void writeTree(Tree* codeTree, BitStream* bitStream, FILE* out) {
	if (!codeTree) {
		return;
	}
	if (!codeTree->left) {
		writeBits(0, 1, bitStream, out);
		writeBits(codeTree->s, CHAR_BIT, bitStream, out);
		return;
	}
	writeBits(1, 1, bitStream, out);
	writeTree(codeTree->left, bitStream, out);
	writeTree(codeTree->right, bitStream, out);
}

void freeTree(Tree* tree) {
	if (!tree) {
		return;
	}
	if (tree->left) {
		freeTree(tree->left);
	}
	if (tree->right) {
		freeTree(tree->right);
	}
	free(tree);
}

Tree* getCodeTree(FILE* in, BitStream* bitStream) {    
	Tree* codeTree = NULL;
	if (getBit(bitStream, in)) {
		codeTree = new_tree(0, 0);
		codeTree->left = getCodeTree(in, bitStream);
		codeTree->right = getCodeTree(in, bitStream);
	}
	else {
		unsigned char s = 0;
		for (int i = 0; i < CHAR_BIT; i++) {
			s= (s << 1) + getBit(bitStream, in);
		}
		codeTree = new_tree(s, 0);
	}
	return codeTree;
}
