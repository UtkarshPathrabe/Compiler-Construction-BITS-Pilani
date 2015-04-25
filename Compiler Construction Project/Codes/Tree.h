/********************************
       |TEAM-1 | GROUP-20|
UTKARSH PATHRABE  - 2012A7PS034P
SHIKHAR VASHISHTH - 2012C6PS436P
********************************/
#ifndef PARSE_TREE_H_INCLUDED
#define PARSE_TREE_H_INCLUDED

#include "parserDef.h"
#include "lexerDef.h"
#include "SymbolLinkedList.h"
#include "SymbolTableDef.h"

typedef struct _TreeNode TreeNode;

struct _TreeNode{
	void *value;
	Symbol sym;
	bool visited;
	ST* scope;
	int offset;
	TreeNode* parent;
	TreeNode* prev;
	TreeNode* next;
	TreeNode* child;
};

typedef TreeNode* Tree;

TreeNode* createTree(Symbol sym);
void insertTreeList(TreeNode **root, Node* list);
void printTree(TreeNode *root, int level);
void printTreeScope(TreeNode *root, int level);
// TreeNode* searchTree(TreeNode *root, Symbol s);
TreeNode* searchTree(TreeNode *root, Symbol s, Symbol endSearch);
void resetTree(TreeNode *tree);
int numChild(TreeNode *root);
void insertChild(TreeNode *root, Symbol sym, void *value);

#endif