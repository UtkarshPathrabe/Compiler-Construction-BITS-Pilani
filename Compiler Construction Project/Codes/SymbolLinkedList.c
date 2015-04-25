/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#include "SymbolLinkedList.h"

void insert(Node **head, Symbol sym) {
	Node *temp, *p = *head;;
	Symbol a = sym;
	temp = (Node *)malloc(sizeof(Node));
	temp->value = a;
	temp->next = NULL;

	if (p == NULL)
		*head = temp;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = temp;
	}
}

void printList(Node *head) {
	Node *p = head;
	if (p == NULL) return;
	while (p != NULL) {
		printf("%d ", p->value);
		p = p->next;
	}
	printf("\n");
}

void reverseList(Node **head) {
	Node *prev, *current, *next;
	prev = NULL;
	current = *head;
	while (current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}

bool searchList(Node *head, Symbol n) {
	Node *p = head;
	while (p != NULL) {
		if (p->value == n) {
			return true;
		}
		p = p->next;
	}
	return false;
}
// int main() {
// 	Node *List = NULL, *list2 = NULL;
// 	insert(&List, AND);
// 	insert(&List, ARROW);
// 	// insert(&List, ASSIGN);
// 	// insert(&List, str_assign_stmt);
// 	// insert(&List, str_stmt);

// 	insert(&list2, AND);
// 	insert(&list2, AND);
// 	// // insert(&list2, AND);
// 	// insert(&list2, AND);

// 	printList(list2);
// 	printList(List);
// 	// reverseList(&List);
// 	// printList(List);
// 	return 0;
// }