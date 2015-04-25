/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

// #include "parser.h"
#include "parserDef.h"
#include "commonHeader.h"

void insert(Node **head, Symbol sym);
void printList(Node *head);
void reverseList(Node **head);
bool searchList(Node* head, Symbol sym);

#endif