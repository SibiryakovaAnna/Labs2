#ifndef HUFFMAN_STRUCTS_H
#define HUFFMAN_STRUCTS_H

typedef struct tree {
	unsigned char s;
	unsigned int f;
	struct tree* left;
	struct tree* right;
} Tree;

typedef struct stack{
	Tree* root;
	struct stack* next;
} Stack;

typedef struct code {
	unsigned char* s;
	int size;
} Code;

typedef struct bit {
	unsigned char byte;
	int size;
} BitStream;

Stack* newStack(Tree* node);
BitStream* new_bit();
void push(Stack** sort, Tree* node);
Tree* pop(Stack** stack);

#endif
