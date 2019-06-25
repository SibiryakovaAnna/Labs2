#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H
#include "structs.h"
#include "tree.h"

Code* new_code(unsigned char* s, int size);
void countFreq(int* freqTable, FILE* in);
void base(Stack**stack, int* freqTable);
void Resize(Code* buffer);
unsigned char* copyCode(Code* buffer);
void addBit(Code* buffer, int bit);
void CodeTable(Code** codeTable, Tree* codeTree, Code* buffer);
void writeBits(unsigned char bits, int count, BitStream* bitStream, FILE* out);
void t_code(FILE* in, FILE* out, Code** codeTable, BitStream* bitStream);
void writeSize(unsigned int size, FILE* out);
void freeCodeTable(Code** codeTable);
void code(FILE* in, FILE* out);
unsigned char getBit(BitStream* bitStream, FILE* in);
int readSize(FILE* in, unsigned int* size);
void decodeText(Tree* codeTree, FILE* in, FILE* out, unsigned int size, BitStream* bitStream);
void decode(FILE* in, FILE* out);

#endif
