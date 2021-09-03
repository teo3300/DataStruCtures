#ifndef TREE_H
#define TREE_H

#undef  LIBALLOC
#undef  USRALLOC
#define LIBALLOC 1
#define USRALLOC 0

#define INLINE static inline

#define BLACK 0
#define RED 1

#define uint  unsigned int
#define ulint unsigned long int
#define color_type uint

typedef struct TREENODE{
    struct TREENODE *left;
    struct TREENODE *parent;
    struct TREENODE *right;
    void*            data;
    color_type       color;
} TreeNode;
typedef TreeNode *treeNode;

typedef struct {
    treeNode    nil;
    treeNode    root;
    int       (*sorting_criteria)(void*, void*);
    uint        data_size;
    uint        libAlloc;
    uint        tree_size;
    void      (*print)(void*);
} TREE;
typedef TREE *Tree;

INLINE uint treeSize(Tree tree){return tree->tree_size;}

// Initialise tree specifying sorting criteria
Tree treeInit(int(*sorting_criteria)(void*, void*), uint memAlloc, uint data_size /*only used with libAlloc*/);
void treeSetPrint(Tree tree, void(*print)(void*));

void treePrintProp(Tree tree);

#define treeAbsMinimum(tree)    treeMinimum(tree, tree->root)
treeNode treeMinimum(Tree tree, treeNode x);
#define treeAbsMaximum(tree)    treeMaximum(tree, tree->root)
treeNode treeMaximum(Tree tree, treeNode x);
treeNode treePred(Tree tree, treeNode x);
treeNode treeSucc(Tree tree, treeNode x);
treeNode treeAppend(Tree tree, void* data);
treeNode treeRemove(Tree tree, treeNode z);
void* treeDelete(Tree tree, treeNode z);
Tree treeRebuild(Tree tree, int(*sorting_criteria)(void*, void*));/*keep alloc type*/

#define treeFirstFind(tree, data_ptr)    treeRecursiveFirstFind(tree, data_ptr, tree->root)
treeNode treeRecursiveFirstFind(Tree tree, void *x, treeNode y);

void treeLeftRotate(Tree tree, treeNode x);
void treeRightRotate(Tree tree, treeNode x);
void treeTransplant(Tree tree, treeNode u, treeNode v);
treeNode treeInsert(Tree tree, treeNode z);
treeNode treeInsertFixup(Tree tree, treeNode z);
void treeDeleteFixup(Tree tree, treeNode x);

#define treeStructPrint(tree)   if (tree->root != tree->nil) { treeRecursiveStructPrint(tree, tree->root, 0); }
void treeRecursiveStructPrint(Tree tree, treeNode node,  uint depth);
void defaultTreePrint(void* data);

void treeDestroy(Tree tree);
void treeRecursiveDestroy(Tree tree, treeNode node);

#endif