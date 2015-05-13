/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef BUFFERINPUT_H_INCLUDED
#define BUFFERINPUT_H_INCLUDED

#include "commonHeader.h"

#define BUFFSIZE 5000

typedef struct{
	char source1 [BUFFSIZE + 1];
	char source2 [BUFFSIZE + 1];
	char *forward;
	FILE *file;
	int currBuffer;
} Buffer;

void reloadBuffer(Buffer *buffer, int buff_number);
void updateForward(Buffer *buffer);
void loadFile(Buffer *buffer, char *filename);
char getChar(Buffer *b);

#endif