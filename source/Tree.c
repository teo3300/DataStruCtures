#include "../include/Tree.h"

#define Debug
#include "../include/Debug.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

Tree* treeInit(uint (*sorting_criteria)(treeNode, treeNode)) {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = tree->nil = (treeNode*)malloc(sizeof(treeNode));
    tree->sorting_criteria = sorting_criteria;
    tree->tree_size = 0;
    *(tree->nil) = (treeNode){   .parent = NULL,
                                .left = NULL,
                                .right = NULL,
                                .data = NULL,
                                .data_size = 0,
                                .color = BLACK};
    return tree;
}


treeNode* treeMinimum(Tree* tree, treeNode* x){
    while (x->left != tree->nil){
        x = x->left;
    }
    return x;
}

treeNode* treeMaximum(Tree* tree, treeNode* x){
    while (x->right != tree->nil){
        x = x->right;
    }
    return x;
}

treeNode* treePred(Tree* tree, treeNode* x){
    if (x->left != tree->nil){
        return treeMaximum(tree, x->left);
    }
    treeNode* y = x->parent;
    while (y != tree->nil && x == y->left){
        x = y;
        y = y->parent;
    }
    return y;
}

treeNode* treeSucc(Tree* tree, treeNode* x){
    if (x->right != tree->nil){
        return treeMinimum(tree, x->right);
    }
    treeNode* y = x->parent;
    while (y != tree->nil && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}

void treeAppend(Tree* tree, void* data, uint data_size){
    treeNode* tmp = (treeNode*)malloc(sizeof(treeNode));
    tmp->data = data;
    tmp->data_size = data_size;
    treeInsert(tree, tmp);
}

void treeLeftRotate(Tree* tree, treeNode *x) {
    treeNode *y = x->right;
    x->right = y->left;

    if (y->left != treeNull) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == treeNull) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void treeRightRotate(Tree* tree, treeNode *x) {
    treeNode *y = x->left;
    x->left = y->right;

    if (y->right != treeNull) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == treeNull) {
        tree->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void treeTransplant(Tree* tree, treeNode *u, treeNode *v){
    if (u->parent == treeNull){
        tree->root = v;
    } else if (u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void treeInsert(Tree* tree, treeNode* z){
    treeNode* y = treeNull;
    treeNode* x = tree->root;
    while(x != treeNull){
        y = x;
        if (tree->sorting_criteria(*z,*x)){
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if(y == treeNull){
        tree->root = z;
    } else if (tree->sorting_criteria(*z,*y)){
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = treeNull;
    z->right = treeNull;
    z->color = RED;
    tree->tree_size++;
    treeInsertFixup(tree, z);
}

void treeInsertFixup(Tree* tree, treeNode* z){
    treeNode* y;
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
}

void treeDeleteFixup(Tree* tree, treeNode* x){
    while (x != tree->root && x->color == BLACK){
        if (x == x->parent->left){
            treeNode* w = x->parent->right;
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
            treeNode* w = x->parent->left;
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

void treeDelete(Tree* tree, treeNode* z){
    treeNode*   y = z;
    treeNode*   x;
    color_type y_original_color = y->color;
    if (z->left == treeNull){
        x = z->right;
        treeTransplant(tree, z, z->right);
    } else if (z->right == treeNull){
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
        treeTransplant(tree, x, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK){
        treeDeleteFixup(tree, x);
    }
    tree->tree_size--;
    free(z);
}

void treeRecursiveStructPrint(Tree* tree, treeNode* node, uint depth){
    if (node->left != treeNull){
        treeRecursiveStructPrint(tree, node->left, depth+1);
    }
    for(uint i=0; i<depth; i++){putchar('-');}
    printf("%c[%3d]\n", node->color ? 'R' : 'B', node->data_size);
    if (node->right != treeNull){
        treeRecursiveStructPrint(tree, node->right, depth+1);
    }
}

void treeRecursiveDestroy(Tree* tree, treeNode* node){
    if (node->left != treeNull){
        treeRecursiveDestroy(tree, node->left);
    }
    if (node->right != treeNull){
        treeRecursiveDestroy(tree, node->right);
    }
    tree->tree_size--;
    free(node);
}