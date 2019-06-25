#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

Stack* newStack(Tree* node) {
	Stack* tmp = (Stack*)malloc(sizeof(Stack));
	tmp->next = NULL;
	tmp->root = node;
	return tmp;
}

BitStream* new_bit() {
	BitStream* tmp = (BitStream*)malloc(sizeof(BitStream));
	tmp->byte = 0;
	tmp->size = 0;
	return tmp;
}

void push(Stack**sort, Tree* node) {
	int val = node->f;
	Stack* tmp = newStack(node);
	if (!(*sort) || (*sort)->root->f >= val) {
		tmp->next = *sort;
		*sort = tmp;
		return;
	}
	Stack* cur = *sort;
	while (cur->next && val > cur->next->root->f) {
		cur = cur->next;
	}
	tmp->next = cur->next;
	cur->next = tmp;
}

Tree* pop(Stack**stack) {
	Stack* tmp = *stack;
	Tree* s = tmp->root;
	*stack = (*stack)->next;
	free(tmp);
	return s;
}
