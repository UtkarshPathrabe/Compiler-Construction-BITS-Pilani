/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/

#include "Tree.h"
#include "mapping.h"

TreeNode* createTree(Symbol sym) {
	TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->sym = sym;
    	temp->visited = false;
	temp->value = NULL;
	temp->child = temp->prev = temp->next = temp->parent = NULL;

	return temp;
}

void insertChild(TreeNode *root, Symbol sym, void *value){
	TreeNode *p = root->child;
	if( p == NULL){
		root->child = malloc(sizeof(TreeNode));
		root->child->prev = p;
		root->child->next = NULL;
		root->child->parent = root;
		root->child->value = value;
		root->child->sym = sym;
		root->child->visited = false;
		root->child->child = NULL;
		return;
	}

	while(p->next != NULL) p = p->next;

	p->next = malloc(sizeof(TreeNode));
	p->next->prev = p;
	p->next->parent = root;
	p->next->value = value;
	p->next->sym = sym;
	p->next->visited = false;
	p->next->child = NULL;
	p->next->next = NULL;
}

void resetTree(TreeNode *tree){
	TreeNode *root = tree;
	root->visited = false;
	root = root->child;
	while(root != NULL){
		resetTree(root);
		root = root->next;
	}
}

void insertTreeList(TreeNode **root, Node* list) {
	Node *p = list;
	TreeNode *prev = NULL;
	TreeNode *head = *root;
	TreeNode *temp;
	bool isFirst = true;

	while (p != NULL) {
		temp = (TreeNode*)malloc(sizeof(TreeNode));
		temp->sym = p->value;
		temp->visited = false;
		temp->value = NULL;

		if (isFirst) {
			head->child = temp;
			isFirst = false;
		}

		temp->parent = head;
		temp->prev = prev;
		if (temp->prev != NULL) temp->prev->next = temp;
		temp->next = NULL;

		prev = temp;
		p = p->next;
	}
}

void printTree(TreeNode *root, int level) {
	int i;
	if (root == NULL) return;
	for(i=0; i<level; i++) printf("____");
	printf("%s\n", symbolToStr(root->sym));
	TreeNode *p = root->child;
	while (p != NULL) {
		printTree(p, level+1);
		p = p->next;
	}	
}

void printTreeScope(TreeNode *root, int level) {
	int i;
	if (root == NULL) return;
	for(i=0; i<level; i++) printf("____");
	printf("%s(%d)\n", symbolToStr(root->sym), root->scope->id);
	TreeNode *p = root->child;
	while (p != NULL) {
		printTreeScope(p, level+1);
		p = p->next;
	}	
}

void markVisited(TreeNode *root){
	while(root!=NULL){
		root->visited = true;
		root = root->prev;
	}
}

int numChild(TreeNode *root){
	int count = 0;
	root = root->child;
	while(root != NULL){
		root = root->next;
		count++;
	}
	return count;
}

Tree searchTree(Tree root, Symbol sym, Symbol endSearch){
	Tree prevP, prevC, p = root;
	bool flag = false;
	while(true){
		while(p != NULL){
			while(p != NULL){
				if(p->sym == endSearch){
					flag = true;
					break;
				}
				if(p->sym == sym) return p;
				prevC = p;
				p = p->child;
			}
			if(flag || (prevC == NULL)) break;
			prevP = prevC;
			p = prevC->next;
		}
		if(flag) break;
		if(prevP->sym == endSearch) break;
		if(prevP->parent != NULL){
			prevP = prevP->parent;
		}else{
			break;
		}
		p = prevP->next;
	}
	return NULL;
}

// int main(){
// 	TreeNode* root = createTree(program);
// 	Node *list = NULL; 
// 	Node *list2 = NULL;
// 	Node *list3 = NULL;

// 	insert(&list, 0);
// 	insert(&list, 1);
// 	insert(&list, 2);
// 	insert(&list, 3);


// 	insert(&list2, 4);
// 	insert(&list2, 5);
// 	insert(&list2, 6);
// 	insert(&list2, 7);

// 	insert(&list3, 9);
// 	insert(&list3, 10);
// 	insert(&list3, 11);
// 	insert(&list3, 12);

// 	insertTreeList(&root, list);
// 	insertTreeList(&(root->child->next), list2);
// 	insertTreeList(&(root->child->next->next), list3);
// 	// printTree(root);

// 	TreeNode * res = searchTree(root->child->next->next, program);
// 	printf("%d \n",res->sym);
// 	return 0;
// }