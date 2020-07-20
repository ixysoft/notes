#include "rb.h"

nodep new_node(int key){
    nodep tmp = (nodep)malloc(sizeof(Node));
    tmp->parent = tmp->left = tmp->right = NULL;
    tmp->key = key;
    tmp->color = RED;
    return tmp;
}

int visit(nodep root){  //中序遍历
    // if(root != NULL){
    //     visit(root->left);
    //     printf("%d ",root->key);
    //     visit(root->right);
    // }
    nodep stack[1024];
    int len = 0;
    stack[len++] = root;
    stack[len++] = NULL;
    nodep tmp = NULL;
    int i;
    for(i = 0; i < len; i++){
        tmp = stack[i];
        if(tmp == NULL){
            if(len > 0 && stack[len-1] != NULL)
                stack[len++] = NULL;
            printf("\n");
        }else{
            printf("%d[%s]{%d} ",tmp->key,isRed(tmp) ? "R" : "B",tmp->parent == NULL ? -1 : tmp->parent->key);
            // printf("%p\n",tmp);
            if(tmp->left != NULL)
                stack[len++ % 1024] = tmp->left;

            if(tmp->right != NULL)
                stack[len++ % 1024] = tmp->right;
        }
    }

}

/**
 * 绕node左旋
 */
nodep rotate_left(nodep node){
    if(node == NULL || node->right == NULL) return node;   //左旋失败
    nodep right = node->right;  //右节点
    if(node->parent != NULL){
        if(isLeft(node)){   //当前节点为父节点的左节点
            parent(node)->left = right;
        }else{
            parent(node)->right = right;
        }
    }
    right->parent = node->parent;
    node->right = right->left;
    if(right->left != NULL)
        right->left->parent = node;
    right->left = node; //将right的左节点设定为node
    node->parent = right;   //将node的父节点设定为right

    return right;
}

/**
 * 绕node右旋
 */
nodep rotate_right(nodep node){
    if(node == NULL || node->left == NULL) return node;   //左旋失败
    nodep left = node->left;  //右节点
    if(node->parent != NULL){
        if(isLeft(node)){   //当前节点为父节点的左节点
            parent(node)->left = left;
        }else{
            parent(node)->right = left;
        }
    }
    left->parent = node->parent;
    node->left = left->right;
    if(left->right != NULL)
        left->right->parent = node;
    left->right = node; //将right的左节点设定为node
    node->parent = left;   //将node的父节点设定为right

    return left;
}


int insert(nodep* rootp,int key){
    return _insert(rootp,key,NULL,rootp);
}

int _insert(nodep* entryp,int key,nodep pa,nodep* rootp){
    if(rootp == NULL || entryp == NULL) return 0;
    nodep entry = *entryp;
    nodep root = *rootp;
    if(entry == NULL){
        entry = new_node(key);
        entry->parent = pa;
        *entryp = entry;
        insert_fix(rootp,entry);
        return 1;
    }

    if(entry->key == key) return 0;  //插入失败
    if(entry->key > key) return _insert(&(entry->left),key,entry,rootp);
    return _insert(&(entry->right),key,entry,rootp);
}

int insert_fix(nodep* rootp,nodep node){
    if(rootp == NULL) return 0; //rootp不允许为NULL
    nodep root = *rootp;
    if(node != NULL && isRed(parent(node))){    //父节点为红色
        while(isRed(parent(node))){ //父节点为红色
            if(isRed(uncle(node))){ //叔父节点为红色
                parent(node)->color = uncle(node)->color = BLACK;
                node = grandparent(node);
                if(node == NULL)
                    break;
                node->color = RED;
            }else{  //叔父节点为黑色或不存在,(不存在两层时,根节点是红色的情况)
                nodep p = parent(node);
                nodep g = grandparent(node);
                if(isLeft(p)){  //左孩子
                    if(isRight(node)){  //LR
                        rotate_left(node);
                    }
                    node = rotate_right(g);
                }else{
                    if(isLeft(node)){
                        rotate_right(node);
                    }
                    node = rotate_left(g);
                }
                //父节点变黑色,祖父节点变红色,旋转后,父节点作为根节点,此时黑节点高度不破坏
                p->color = BLACK;
                g->color = RED;
            }
        }
    }
    if(node != NULL){
        if(parent(node) == NULL) root = node; //设定新的根节点
    }
    root->color = BLACK;    //根节点设定为黑色
    *rootp = root;
    return 1;
}

//删除指定的键
int delete(nodep* rootp,int key){

}