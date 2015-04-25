/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#include "SymbolStack.h"
#include "mapping.h"

void push(Node** head, Symbol sym) {
	Node *temp;
	temp = (Node *)malloc(sizeof(Node));
	temp->value = sym;
	temp->next = NULL;

	if (*head == NULL)
		*head = temp;
	else {
		temp->next = *head;
		*head = temp;
	}
}

Symbol top(Node* head) {
	if(head == NULL) return -1;
	return head->value;
}

void pop(Node** head) {
	Node* p = *head;
	if(p != NULL) {
		*head = p->next;
		free(p);
	}
}

bool isEmpty(Node* head){
	if (head == NULL) return true;
	else return false;
}

void printStack(Node* head) {
	Node *p = head;
	while (p != NULL) {
		printf("%s ", symbolToStr(p->value));
		p = p->next;
	}
	printf("\n");
}

/*int main(){
	Node* st;
	push(&st, AND);
	push(&st, ARROW);
	push(&st, ASSIGN);
	push(&st, str_assign_stmt);
	push(&st, str_stmt);
	printAll(st);
	while(!isEmpty(st)){
		printf("TOP: %d\n", top(st));
		pop(&st);
	}
	return 0;
}*/