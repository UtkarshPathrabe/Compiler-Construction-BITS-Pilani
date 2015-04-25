/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef STACKS_H_INCLUDED
#define STACKS_H_INCLUDED

#include "parserDef.h"
#include "commonHeader.h"

void push(Node** head,Symbol n);
void pop(Node** head);
Symbol top(Node* head);
void printStack(Node* head);
bool isEmpty(Node* head);

#endif