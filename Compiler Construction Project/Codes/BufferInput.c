/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#include "BufferInput.h"

void reloadBuffer(Buffer *b, int buff_number){
	if(buff_number == 1){
		size_t newLen = fread(b->source1, sizeof(char), BUFFSIZE, b->file);
		if(newLen == 0) b->source1[0] ='$';
		else if(newLen == BUFFSIZE) b->source1[++newLen] ='\0';
		else b->source1[newLen] = '$';
	}

	else{
		size_t newLen = fread(b->source2, sizeof(char), BUFFSIZE, b->file);
		if(newLen == 0) b->source2[0] ='$';
		else if (newLen == BUFFSIZE) b->source2[++newLen] = '\0';
		else b->source2[newLen] = '$';
	}
}

void updateForward(Buffer *b){
	if(b->forward == (b->source1)+BUFFSIZE){
		reloadBuffer(b, 2);
		b->forward = b->source2;
	}
	else if(b->forward == (b->source2)+BUFFSIZE){
		reloadBuffer(b, 1);
		b->forward = b->source1;
	}
}

void loadFile(Buffer *b, char *filename){
	b->file = fopen(filename, "r");
	reloadBuffer(b, 1);
	b->forward = b->source1;
	b->currBuffer = 1;
}

char getChar(Buffer *b){
	if(b->forward == '\0') updateForward(b);
	char c = *(b->forward);
	b->forward += 1;
	return c;
}