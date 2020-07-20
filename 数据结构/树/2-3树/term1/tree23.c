#include "tree23.h"

treep tree(){
    treep ret = (treep)malloc(sizeof(Tree));
    ret->root = NULL;
    ret->size = 0;

    return ret;
}

nodep create_node(treep t,keyp first_key,nodep first_child,int size){    //创建新的节点
    if(t == NULL) return NULL;
    nodep ret = (nodep)malloc(sizeof(Node));
    ret->parent = NULL;
    ret->keys = first_key;
    ret->children = first_child;
    ret->size = size;
    ret->next = NULL;
    if(first_child != NULL)
        ret->next = first_child->next;

    return ret;
}

Boolean insertNode(treep t,int key){
    return _insertNode(t,t->root,key);
}

Boolean _insertNode(treep t,nodep root,int key){
    if(t == NULL) return NULL;
    nodep node = NULL;
    keyp key = NULL;
    while(root != NULL){
        while(root->keys->key > key){
            node = root;
            root = root->next;
        }
        
    }
}

Boolean fixNode(treep t,nodep n){
    int size = n->size;
}

keyp searchNode(treep t,int key){
    
}