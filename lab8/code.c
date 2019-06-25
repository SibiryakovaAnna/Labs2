#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Code.h"

Code* new_code(unsigned char* s, int size) {    
	Code* tmp = (Code*)malloc(sizeof(Code));
	tmp->s = s;
	tmp->size = size;
	return tmp;
}

void countFreq(int* freqTable, FILE* in) {        
	int c;
	while ((c = fgetc(in)) != EOF) {
		freqTable[c]++;
	}
}

void base(Stack**stack, int* freqTable) {       
	for (int i = 0; i < 256; i++) {
		if (freqTable[i]) {
			push(stack, new_tree(i, freqTable[i]));
		}
	}
}

void Resize(Code* buffer) {               
	buffer->size++;
	int isOverflow = buffer->size % CHAR_BIT;
	if (isOverflow == 1) {
		int bytes = buffer->size / CHAR_BIT + 1;
		buffer->s = (unsigned char*)realloc(buffer->s, bytes);
		buffer->s[bytes - 1] = 0;
	}

}

unsigned char* copyCode(Code* buffer) {            
	int bytes = (buffer->size - 1) / CHAR_BIT + 1;
	unsigned char* new_s = (unsigned char*)malloc(bytes);
	for (int i = 0; i < bytes; i++) {
		new_s[i] = buffer->s[i];
	}
	return new_s;
}

void t_code(FILE* in, FILE* out, Code** codeTable, BitStream* bitStream) {   
	int c, i;
	while ((c = fgetc(in)) != EOF) {
		for (i = 0; i < codeTable[c]->size / CHAR_BIT; i++) {
			writeBits(codeTable[c]->s[i], CHAR_BIT, bitStream, out);
		}
		writeBits(codeTable[c]->s[i], codeTable[c]->size % CHAR_BIT, bitStream, out);
	}
	if (bitStream->size) {
		fputc(bitStream->byte << (CHAR_BIT - bitStream->size), out);
	}
}

void writeSize(unsigned int size, FILE* out) {    
	fwrite(&size, sizeof(unsigned int), 1, out);
}

void freeCodeTable(Code** codeTable) { 
	for (int i = 0; i < 256; i++) {
		if (codeTable[i]) {
			free(codeTable[i]->s);
			free(codeTable[i]);
		}
	}
}

void code(FILE* in, FILE* out) {      
    int k;
	int freqTable[256];
	Stack* stack = NULL;
	Code* codeTable[256];
	Tree* codeTree = NULL;
	BitStream* bitStream = new_bit();
	memset(freqTable, 0, sizeof(int) * 256);
	memset(codeTable, NULL, sizeof(Code*) * 256);

	while ((k = fgetc(in)) != EOF) {
		freqTable[k]++;
	}
	base(&stack, freqTable);
	codeTree = CodeTree(&stack);
	if (codeTree) {
		writeSize(codeTree->f, out);
	}
	writeTree(codeTree, bitStream, out);
	CodeTable(codeTable, codeTree, new_code(NULL, 0));
	fseek(in, 3, SEEK_SET);
	t_code(in, out, codeTable, bitStream);
	free(bitStream);
	freeCodeTable(codeTable);
	freeTree(codeTree);
}

int readSize(FILE* in, unsigned int* size) {    
	return fread(size, sizeof(unsigned int), 1, in);
}

void decodeText(Tree* codeTree, FILE* in, FILE* out, unsigned int size, BitStream* bitStream) {     
	Tree* tmpCodeTree;
	for (unsigned int i = 0; i < size; i++) {
		tmpCodeTree = codeTree;
		while (tmpCodeTree->left) {
			if (getBit(bitStream, in)) {
				tmpCodeTree = tmpCodeTree->right;
			}
			else {
				tmpCodeTree = tmpCodeTree->left;
			}
		}
		fputc(tmpCodeTree->s, out);
	}
}

void decode(FILE* in, FILE* out) {   
	unsigned int size;
	if (!readSize(in, &size)) {
		return;
	}
	BitStream* bitStream = new_bit();
	Tree* codeTree = getCodeTree(in, bitStream);
	decodeText(codeTree, in, out, size, bitStream);
	free(bitStream);
	freeTree(codeTree);
}
