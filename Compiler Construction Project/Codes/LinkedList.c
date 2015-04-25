/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#include "LinkedList.h"

void LL_insert(LL_Node **head, void *data) {
	LL_Node *p = *head;

	LL_Node *temp = malloc(sizeof(LL_Node));
	temp->value = data;
	temp->next = NULL;

	if (p == NULL)
		*head = temp;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = temp;
	}
}

int LL_size(LL_Node *head){
	int count=0;
	while(head != NULL){
		head = head->next;
		count++;
	}
	return count;
}

// int main() {
// 	LL_Node *List = NULL;
// 	TokenInfo *tk1 = malloc(sizeof(TokenInfo));
// 	TokenInfo *tk2 = malloc(sizeof(TokenInfo));
// 	strcpy(tk1->lexeme, "Hello");
// 	strcpy(tk2->lexeme, "World");

// 	LL_insert(&List, tk1);
// 	LL_insert(&List, tk2);


// 	printf("%s\n", ((TokenInfo*)(List->value))->lexeme);
// 	printf("%s\n", ((TokenInfo*)(List->next->value))->lexeme);

// 	return 0;
// }