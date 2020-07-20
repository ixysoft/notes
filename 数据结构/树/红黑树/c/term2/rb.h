#ifndef __RB_H__
#define __RB_H__
#include<stdio.h>
#include<stdlib.h>

#define parent(n)   ((n) == NULL ? NULL : (n)->parent)  //父节点
#define isBlack(n)  ((n) != NULL && (n)->color == BLACK)
#define isRed(n)    ((n) != NULL && (n)->color == RED)
#define isLeaf(n)   ((n) == NULL)
#define isLeft(n) (parent(n) != NULL && parent(n)->left == (n))      //左节点
#define isRight(n) (parent(n) != NULL && parent(n)->right == (n))    //右节点
#define brother(n)  (parent(n) == NULL ? NULL : isLeft(n) ? parent(n)->right : parent(n)->left)
#define grandparent(n) (parent(parent(n)))  //祖父节点
#define uncle(n)    (brother(parent(n)))    //叔父节点

typedef enum{
    BLACK = 0,
    RED = 1,
}Color;

typedef struct Node{
    Color color;
    int key;
    struct Node *left,*right,*parent;
}Node,*nodep;

typedef struct Tree{
    nodep root;
    int size;
}Tree,*treep;   //红黑树

int     visit(nodep root);              //遍历指定的树
treep   new_tree();                     //创建一个tree
nodep   new_node(int key);              //创建新的node
nodep   rotate_left(nodep node);        //左旋指定节点
nodep   rotate_right(nodep node);       //右旋指定节点
int     insert(nodep* rootp,int key);   //向指定的树中插入节点
int     _insert(nodep* entryp,int key,nodep pa,nodep* rootp);   //插入节点底层
int     insert_fix(nodep* rootp,nodep node);         //调整指定的节点
#endif