#include "rb.h"
static void _insert(Tree tree,node* proot,int key,int val);

node rotate_left(node root){
    if(root == NULL) return NULL;
    if(root->right == NULL) return root;    //右节点为空
    node right = root->right;
    root->right = right->left;
    right->left = root;

    if(root->parent != NULL){  //存在父节点
        if(root->parent->left == root){
            root->parent->left = right;
        }else{
            root->parent->right = right;
        }
    }

    if(root->right) root->right->parent = root;
    node tmp = root->parent;
    root->parent = right;
    right->parent = tmp;
    
    return right;
}

node rotate_right(node root){
    if(root == NULL) return NULL;
    if(root->left == NULL) return root; //左节点为空
    node left = root->left;
    root->left = left->right;
    left->right = root;

    if(root->parent != NULL){
        if(root->parent->left == root){
            root->parent->left = left;
        }else{
            root->parent->right = left;
        }
    }

    if(root->left) root->left->parent = root;
    node tmp = root->parent;
    root->parent = left;    //这里root的父节点应该是left节点而不是left的父节点,rotate_left同理
    left->parent = tmp;
    
    return left;
}

void adjust(Tree tree,node root){
    if(root == NULL) return;
    if(parent(root) == NULL){   //父节点为空
        root->color = BLACK;    //世界没有你想想的那么好，记得加上黑色
        *tree = root;
        return;
    }
    if(isBlack(root) || isBlack(parent(root))) return;   //父节点为黑色

    if(isRed(uncle(root))){
        parent(root)->color = uncle(root)->color = BLACK;
        grandpa(root)->color = RED;
        //getNodeInfo(grandpa(root),"DEBUG ");
        adjust(tree,grandpa(root));
        return;
    }else{
        node pa = parent(root);
        node ga = grandpa(root);
        pa->color = BLACK;
        ga->color = RED;
        if(ga->left == pa){ //左子树
            if(pa->right == root){
                rotate_left(pa);
            }
            ga = rotate_right(ga);
            adjust(tree,ga);
        }else{
            if(pa->left == root){
                rotate_right(pa);
            }
            ga = rotate_left(ga);
            adjust(tree,ga);
        }
    }
}

int search(Tree tree,int key){
    node root = *tree;
    if(root == NULL) return -1;
    if(root->key == key) return root->val;
    else if(root->key > key) return search(&(root->left),key);
    else return search(&(root->right),key);
}

static void _insert(Tree tree,node *proot,int key,int val){
    node root = *proot;
    if(root == NULL){
        root = (node)malloc(sizeof(Node));
        root->left = root->right = root->parent = NULL;
        root->key = key;
        root->val = val;
        root->color = BLACK;
        if(*tree == NULL) *tree = root;
        *proot = root;
    }else if(root->key == key){
        root->val = val;
    }else if(root->key > key){
        _insert(tree,&(root->left),key,val);
        if(root->left != NULL && root->left->parent == NULL){
            root->left->color = RED;
            root->left->parent = root;
            adjust(tree,root->left);
        }
    }else{
        _insert(tree,&(root->right),key,val);
        if(root->right != NULL && root->right->parent == NULL){
            root->right->color = RED;
            root->right->parent = root;
            adjust(tree,root->right);
        }
    }
}

//插入键值对
void insert(Tree tree,int key,int val){
    _insert(tree,tree,key,val);
}

void getNodeInfo(node root,char* prefix){
    if(prefix == NULL) prefix = "";
    if(root == NULL){
        printf("%s%p\n",prefix,root);
    }else{
        printf("%s[%d]=>%d[%s]{%p=>%p}\n",prefix,root->key,root->val,isRed(root)?"red":"black",root,root->parent);
    }
}

void preOrderVisit(node root){
    if(root == NULL) return;
    getNodeInfo(root,NULL);
    preOrderVisit(root->left);
    preOrderVisit(root->right);
}


//删除最小节点并返回其属性值
void deleteMin(Tree tree,int *key,int *val){
    node root = *tree;
    *key = 0;
    *val = 0;
    if(root == NULL) return;
    if(root->left == NULL){
        *key = root->key;
        *val = root->val;
        free(root);
        *tree = NULL;
    }else{
        deleteMin(&(root->left),key,val);    //递归删除左节点
    }
}

//删除最大节点并返回其属性值
void deleteMax(Tree tree,int *key,int *val){
    node root = *tree;
    *key = 0;
    *val = 0;
    if(root == NULL) return;
    if(root->right == NULL){
        *key = root->key;
        *val = root->val;
        free(root);
        *tree = NULL;
    }else{
        deleteMax(&(root->right),key,val);
    }
}

void delete(Tree tree,int key){
    node root = *tree;
    if(root == NULL) return;
    if(root->key == key){
        int key,val;
        if(root->left != NULL && root->right != NULL){ //选取左节点
            deleteMax(&(root->left),&key,&val);
            root->key = key;
            root->val = val;
        }else{
            *tree = NULL;
            if(root->left){ //左节点存在
                *tree = root->left;
            }else if(root->right){  //右节点存在
                *tree = root->right;
            }
            free(root);
            adjust(tree,*tree);
        }
        if(*tree != NULL){
            root->key = key;
            root->val = val;
            *tree = root;
        }
    }else if(root->key > key){
        delete(&(root->left),key);
    }else{
        delete(&(root->right),key);
    }
}
