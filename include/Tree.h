#ifndef TREE_H
#define TREE_H

#define BLACK 0
#define RED 1

#define uint unsigned int
#define color_type uint
#define treeNull    tree->nil

typedef struct TreeNode{
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
    color_type    color;
    void*   data;
    uint    data_size;
} treeNode;
typedef struct {
    treeNode* root;
    treeNode* nil;
    uint tree_size;
    uint (*sorting_criteria)(treeNode, treeNode);
} Tree;

// Initialise tree specifying sorting criteria
Tree* treeInit(uint(*sorting_criteria)(treeNode, treeNode));

#define treeAbsMinimum(tree)    treeMinimum(tree, tree.root)
treeNode* treeMinimum(Tree* tree, treeNode* x);
#define treeAbsMaximum(tree)    treeMaximum(tree, tree.root)
treeNode* treeMaximum(Tree* tree, treeNode* x);
treeNode* treePred(Tree* tree, treeNode* x);
treeNode* treeSucc(Tree* tree, treeNode* x);
void treeAppend(Tree* tree, void* data, uint data_size);
void treeDelete(Tree* tree, treeNode* z);

void treeLeftRotate(Tree* tree, treeNode* x);
void treeRightRotate(Tree* tree, treeNode* x);
void treeTransplant(Tree* tree, treeNode* u, treeNode* v);
void treeInsert(Tree* tree, treeNode* z);
void treeInsertFixup(Tree* tree, treeNode* z);
void treeDeleteFixup(Tree* tree, treeNode* x);

#define treeStructPrint(tree)   treeRecursiveStructPrint(tree, tree->root, 0);
void treeRecursiveStructPrint(Tree* tree, treeNode* node,  uint depth);

#define treeDestroy(tree)       treeRecursiveDestroy(tree, tree->root)
void treeRecursiveDestroy(Tree* tree, treeNode* node);

#endif