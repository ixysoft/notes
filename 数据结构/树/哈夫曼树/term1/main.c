#include<stdio.h>
#include<stdlib.h>

typedef enum{
    FALSE = 0,
    TRUE = 1,
}Boolean;

typedef struct Node{
    int key;        //关键字
    int weight;     //权重
    struct Node *left;
    struct Node *right;
}Node,*nodep;

typedef struct RateNode{
    nodep data;             //当前节点
    struct RateNode* next;  //后继节点
}RateNode,*ratenodep;

nodep node(int key,int weight); //插入节点
Boolean insertNode(ratenodep *rootp,nodep nd);
void visit(ratenodep root);
nodep popNode(ratenodep* rootp);
void printCode(nodep root); //输出代码
char dirs[100];
int idx = -1;

int main(){
    ratenodep root = NULL;

    int kvs[][2] = {
        {1,10},
        {2,5},
        {3,15},
        {5,12},
        {4,32},
        {7,1},
    };
    int kvl = sizeof(kvs) / sizeof(kvs[0]);
    for(int i = 0; i < kvl; i++)
        insertNode(&root,node(kvs[i][0],kvs[i][1]));

    visit(root);
    nodep a = NULL;
    nodep b = NULL;
    nodep res = NULL;
    while(root->next != NULL){
        a = popNode(&root);
        b = popNode(&root);
        res = node(0,a->weight + b->weight);  //创建新的节点
        res->left =  a;
        res->right = b;
        insertNode(&root,res);
    }

    printCode(res);
    
    return 0;
}

nodep node(int key,int weight){ //插入节点
    nodep ret = (nodep)malloc(sizeof(Node));
    ret->key = key;
    ret->weight = weight;
    ret->left = NULL;
    ret->right = NULL;
}


Boolean insertNode(ratenodep *rootp,nodep ins){
    if(rootp == NULL || ins == NULL) return FALSE;
    ratenodep root = *rootp;
    ratenodep* lastp = NULL;
    for(;root != NULL && root->data->weight < ins->weight;root = root->next){
        lastp = rootp;
        rootp = &(root->next);
    }

    ratenodep nd =  (ratenodep)malloc(sizeof(RateNode));
    nd->next = NULL;
    nd->data = ins;

    if(root == NULL){
        *rootp = nd;
    }else if(lastp == NULL){
        nd->next = root;
        *rootp = nd;
    }else{
        root = *lastp;
        nd->next = root->next;
        root->next = nd;
    }
    return TRUE;
}

nodep popNode(ratenodep* rootp){
    ratenodep root = *rootp;
    if(root == NULL) return NULL;
    nodep ret = root->data;
    *rootp = root->next;
    free(root);
    return ret;
}

void visit(ratenodep root){
    while(root != NULL){
        printf("%d{%d}\n",root->data->key,root->data->weight);
        root = root->next;
    }
}

void printCode(nodep root){
    if(root == NULL) return;
    if(root->right != NULL || root->left != NULL ){
        idx++;
        dirs[idx] = 1;
        printCode(root->right);
        dirs[idx] = 0;
        printCode(root->left);
        idx--;
    }else if(root->left == NULL && root->right == NULL){
        printf("%d:",root->key);
        for(int i = 0; i <= idx;i++){
            printf("%d",dirs[i]);
        }
        printf("\n");
        return;
    }
}