// header-only cpp tree library
#ifndef RB_TREE_HPP
#define RB_TREE_HPP

class TreeData {
  int ciccioculone;

public:
    bool operator>(TreeData par){return par.ciccioculone > this->ciccioculone;}
    bool operator<(TreeData par){return par.ciccioculone < this->ciccioculone;}
};

#define INLINE static inline
#define uint unsigned int
typedef TreeData *treeData;

typedef enum { black, red } _color_;

class TreeNode {
  TreeNode *left;
  TreeNode *parent;
  TreeNode *right;
  _color_ color;
  friend class Tree;

public:
  TreeData data;
  TreeNode() {left = nullptr, parent = nullptr, right = nullptr, color = black;}
  ~TreeNode() {delete &data;}
  TreeNode(TreeData data) {this->data = data;}
};
typedef TreeNode *treeNode;

class Tree : private TreeNode {
  treeNode nil;
  treeNode root;
  uint size;

  void leftRot(treeNode x);
  void rightRot(treeNode x);
  void transPlant(treeNode u, treeNode v);
  treeNode insertFixup(treeNode z);
  void deleteFixup(treeNode x);
  void destroy(treeNode x);

public:
  Tree();
  ~Tree();
  treeNode min(treeNode x);
  treeNode max(treeNode x);
  treeNode absMin(treeNode x);
  treeNode absMax(treeNode x);
  treeNode prev(treeNode x);
  treeNode next(treeNode x);
  treeNode append(TreeData data);
  treeNode find(TreeData data);
  void remove(treeNode z);

  treeNode recFind(TreeData data, treeNode y);
  treeNode insert(treeNode z);
};

Tree::Tree() {
  nil = new TreeNode();
  root = nil;
  size = 0;
}

Tree::~Tree() {destroy(root);}


void Tree::leftRot(treeNode x) {
  treeNode y = x->right;
  x->right = y->left;

  if (y->left != this->nil) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == this->nil) {
    this->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void Tree::rightRot(treeNode x) {
  treeNode y = x->left;
  x->left = y->right;

  if (y->right != this->nil) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == this->nil) {
    this->root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

void Tree::transPlant(treeNode u, treeNode v) {
  if (u->parent == this->nil) {
    this->root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

treeNode Tree::insertFixup(treeNode z) {
  treeNode y;
  while (z->parent->color == red) {
    if (z->parent == z->parent->parent->left) {
      y = z->parent->parent->right;
      if (y->color == red) {
        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          leftRot(z);
        }
        z->parent->color = black;
        z->parent->parent->color = red;
        rightRot(z->parent->parent);
      }
    } else {
      y = z->parent->parent->left;
      if (y->color == red) {
        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rightRot(z);
        }
        z->parent->color = black;
        z->parent->parent->color = red;
        leftRot(z->parent->parent);
      }
    }
  }
  root->color = black;
  return z;
}

void Tree::deleteFixup(treeNode x) {
  while (x != root && x->color == black) {
    treeNode w;
    if (x == x->parent->left) {
      w = x->parent->right;
      if (w->color == red) {
        w->color = black;
        x->parent->color = red;
        leftRot(x->parent);
        w = x->parent->right;
      }
      if (w->left->color == black && w->right->color == black) {
        w->color = red;
        x = x->parent;
      } else {
        if (w->right->color == black) {
          w->left->color = black;
          w->color = red;
          leftRot(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = black;
        w->right->color = black;
        leftRot(x->parent);
        x = root;
      }
    } else {
      w = x->parent->left;
      if (w->color == red) {
        w->color = black;
        x->parent->color = red;
        rightRot(x->parent);
        w = x->parent->left;
      }
      if (w->right->color == black && w->left->color == black) {
        w->color = red;
        x = x->parent;
      } else {
        if (w->left->color == black) {
          w->right->color = black;
          w->color = red;
          leftRot(w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = black;
        w->left->color = black;
        rightRot(x->parent);
        x = root;
      }
    }
  }
  x->color = black;
}

void Tree::destroy(treeNode x) {
  if (x->left != nil) {
    destroy(x->left);
  }
  if (x->right != nil) {
    destroy(right);
  }
  size--;
  delete x;
}

treeNode Tree::min(treeNode x) {
  while (x->left != nil) {
    x = x->left;
  }
  return x;
}

treeNode Tree::max(treeNode x) {
  while (x->right != nil) {
    x = x->right;
  }
  return x;
}

treeNode Tree::absMin(treeNode x) { return min(root); }


treeNode Tree::absMax(treeNode x) { return max(root); }


treeNode Tree::prev(treeNode x) {
  if (x->left != nil) {
    return max(x->left);
  }
  treeNode y = x->parent;
  while (y != nil && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

treeNode Tree::next(treeNode x) {
  if (x->right != nil) {
    return min(x->right);
  }
  treeNode y = x->parent;
  while (y != nil && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

treeNode Tree::append(TreeData data) {
  treeNode tmp = new TreeNode(data);
  if (!tmp)
    return nullptr;
  return (insert(tmp));
}

treeNode Tree::find(TreeData data){ return recFind(data, root);}


void Tree::remove(treeNode z) {
    if (z == nil) return;
    treeNode y = z;
    treeNode x;
    _color_ y_original_color = y->color;
    if (z->left == nil){
        x = z->right;
        transPlant(z, z->right);
    } else if (z->right == nil){
        x = z->left;
        transPlant(z, z->left);
    } else {
        y = min(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z){
            x->parent = y;
        } else {
            transPlant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transPlant(z, y);     // that was bad
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == black){
        deleteFixup(x);
    }
    size--;
}

treeNode Tree::recFind(TreeData data, treeNode y){
    if(y != nil){
        if (y->data > data){
            return recFind(data, y->right);
        } if (y->data < data){
            return recFind(data, y->left);
        }
    }
    return y;
}

treeNode Tree::insert(treeNode z){
    treeNode y = nil;
    treeNode x = root;
    while(x != nil){
        y = x;
        if (z->data < x->data){
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if(y == nil){
        root = z;
    } else if (z->data < y->data){
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = red;
    size++;
    return(insertFixup(z));
}

#undef uint

#endif