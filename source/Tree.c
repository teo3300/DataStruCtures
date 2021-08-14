#include "../include/Tree.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

Tree treeInit(int (*sorting_criteria)(void*, void*), uint memAlloc, uint data_size) {
    Tree tree = (Tree)malloc(sizeof(TREE));                         if (!tree) return NULL;
    tree->nil               = (treeNode)malloc(sizeof(TreeNode));   if (!tree->nil) return NULL;
    tree->root              = tree->nil;
    tree->sorting_criteria  = sorting_criteria;
    tree->data_size         = data_size;
    tree->libAlloc          = memAlloc;
    tree->tree_size         = 0;

    *(tree->nil) = (TreeNode){  .left = tree->nil,
                                .parent = tree->nil,
                                .right = tree->nil,
                                .data = NULL,
                                .color = BLACK};
    return tree;
}

void treePrintProp(Tree tree){
    printf("tree:\n\ttree:\t\t\t%p\n", tree);
    printf("\ttree->nil:\t\t%p\n", tree->nil);
    printf("\ttree->root:\t\t%p\n", tree->root);
    printf("\ttree->sorting_criteria:\t%p\n", tree->sorting_criteria);
    printf("\ttree->data_size:\t%u\n", tree->data_size);
    printf("\ttree->libAlloc:\t\t%s\n", tree->libAlloc ? "true" : "false");
    printf("\ttree->tree_size:\t%u\n", tree->tree_size);
}

treeNode treeMinimum(Tree tree, treeNode x){
    while (x->left != tree->nil){
        x = x->left;
    }
    return x;
}

treeNode treeMaximum(Tree tree, treeNode x){
    while (x->right != tree->nil){
        x = x->right;
    }
    return x;
}

treeNode treePred(Tree tree, treeNode x){
    if (x->left != tree->nil){
        return treeMaximum(tree, x->left);
    }
    treeNode y = x->parent;
    while (y != tree->nil && x == y->left){
        x = y;
        y = y->parent;
    }
    return y;
}

treeNode treeSucc(Tree tree, treeNode x){
    if (x->right != tree->nil){
        return treeMinimum(tree, x->right);
    }
    treeNode y = x->parent;
    while (y != tree->nil && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}

treeNode treeAppend(Tree tree, void* data){
    treeNode tmp = (treeNode)malloc(sizeof(TreeNode));
    if (!tmp) return NULL;
    if (tree->libAlloc) {
        tmp->data = (void*)malloc(tree->data_size);
        if (!tmp->data) return NULL;
        memcpy(tmp->data, data, tree->data_size);
    } else {
        tmp->data = data;
    }
    return(treeInsert(tree, tmp));
}

treeNode treeRemove(Tree tree, treeNode z){
    if (z == tree->nil) return z;
    treeNode y = z;
    treeNode x;
    color_type y_original_color = y->color;
    if (z->left == tree->nil){
        x = z->right;
        treeTransplant(tree, z, z->right);
    } else if (z->right == tree->nil){
        x = z->left;
        treeTransplant(tree, z, z->left);
    } else {
        y = treeMinimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z){
            x->parent = y;
        } else {
            treeTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        treeTransplant(tree, z, y);     // that was bad
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK){
        treeDeleteFixup(tree, x);
    }
    tree->tree_size--;
    return z;
}

void* treeDelete(Tree tree, treeNode z){
    void* ret = z->data;
    treeRemove(tree, z);
    if (tree->libAlloc) {
        if (z->data) free(z->data);
    }
    free(z);
    return ret;
}

Tree treeRebuild(Tree tree, int(*sorting_criteria)(void*, void*)){

    TREE tmpTree;
    tmpTree.nil               = tree->nil;
    tmpTree.root              = tree->nil;
    tmpTree.sorting_criteria  = sorting_criteria;
    tmpTree.data_size         = tree->data_size;
    tmpTree.libAlloc          = tree->libAlloc;
    tmpTree.tree_size         = 0;

    while(treeSize(tree))
        treeInsert(&tmpTree, treeRemove(tree, tree->root));
    *tree = tmpTree;
    return tree;
}

treeNode treeRecursiveFirstFind(Tree tree, void *x, treeNode y){
    if (y != tree->nil){
        if (tree->sorting_criteria(x, y->data) < 0){
            return treeRecursiveFirstFind(tree, x, y->right);
        } if (tree->sorting_criteria(x, y->data) > 0){
            return treeRecursiveFirstFind(tree, x, y->left);
        }
    }
    return y;
}

void treeLeftRotate(Tree tree, treeNode x) {
    treeNode y = x->right;
    x->right = y->left;

    if (y->left != tree->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void treeRightRotate(Tree tree, treeNode x) {
    treeNode y = x->left;
    x->left = y->right;

    if (y->right != tree->nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void treeTransplant(Tree tree, treeNode u, treeNode v){
    if (u->parent == tree->nil){
        tree->root = v;
    } else if (u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

treeNode treeInsert(Tree tree, treeNode z){
    treeNode y = tree->nil;
    treeNode x = tree->root;
    while(x != tree->nil){
        y = x;
        if (tree->sorting_criteria(z->data, x->data)>0){
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if(y == tree->nil){
        tree->root = z;
    } else if (tree->sorting_criteria(z->data, y->data)>0){
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;
    tree->tree_size++;
    return(treeInsertFixup(tree, z));
}

treeNode treeInsertFixup(Tree tree, treeNode z){
    treeNode y;
    while (z->parent->color == RED){
        if (z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if (y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right){
                    z = z->parent;
                    treeLeftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                treeRightRotate(tree, z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left){
                    z = z->parent;
                    treeRightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                treeLeftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
    return z;
}

void treeDeleteFixup(Tree tree, treeNode x){
    while (x != tree->root && x->color == BLACK){
        treeNode w;
        if (x == x->parent->left){
            w = x->parent->right;
            if (w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                treeLeftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK){
                    w->left->color = BLACK;
                    w->color = RED;
                    treeRightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                treeLeftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            w = x->parent->left;
            if (w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                treeRightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK){
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK){
                    w->right->color = BLACK;
                    w->color = RED;
                    treeLeftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                treeRightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

void treeRecursiveStructPrint(Tree tree, treeNode node, uint depth){
    if (node->left != tree->nil){
        treeRecursiveStructPrint(tree, node->left, depth+1);
    }
    for(uint i=0; i<depth; i++){putchar('-');}
    printf("%c<%p>\n", node->color ? 'R' : 'B', node->data);
    if (node->right != tree->nil){
        treeRecursiveStructPrint(tree, node->right, depth+1);
    }
}

void treeRecursiveDestroy(Tree tree, treeNode node){
    if (node->left != tree->nil){
        treeRecursiveDestroy(tree, node->left);
    }
    if (node->right != tree->nil){
        treeRecursiveDestroy(tree, node->right);
    }
    tree->tree_size--;
    if(node->data && tree->libAlloc) free(node->data);
    free(node);
}

void treeDestroy(Tree tree){
    if (tree->tree_size){
        treeRecursiveDestroy(tree, tree->root);
    }
    free(tree->nil);
    free(tree);
}