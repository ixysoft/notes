#ifndef __RB_H__
#define __RB_H__
#include<stdio.h>
#include<stdlib.h>

// #define DEBUG
#ifdef DEBUG
#define ralloc(n)       (printf("line[%d]: alloc %d bytes\n",__LINE__,(int)(n)),malloc(n))
#else
#define ralloc(n)       (malloc(n))
#endif
#define isNull(n)       ((n) == NULL)                     //判断是否为空
#define isLeaf(n)       (!isNull(n) && isNull((n)->key))  //判断是否为叶子节点
#define isRoot(n)       (!isNull(n) && ((n)->parent == NULL || isLeaf((n)->parent))) //判断是否为根节点
#define isRed(n)        (!isNull(n) && n->color == RED) //判断是否为红节点
#define isBlack(n)      (!isRed(n))                     //判断是否为黑节点
#define isLeft(n)       (!isNull(parent(n)) && parent(n)->left == (n))
#define isRight(n)      (!isNull(parent(n)) && parent(n)->right == (n))
#define Key(n)          (*(n)->key)
#define key_cmp(a,b)    ((isNull(a) || isNull(b) || Key(a) < Key(b)) ? 0 : 1)
#define parent(n)       (isNull(n) ? NULL : (n)->parent)//父节点
#define sibling(n)      (isRoot(n) ? NULL : isLeft(n) ? n->parent->right : n->parent->left)
#define grandpa(n)      (parent(parent(n)))               //祖父节点
#define uncle(n)        (sibling(parent(n)))            //叔父节点

typedef enum{
    BLACK = 0,
    RED = 1,
}Color;

typedef enum{
    FALSE = 0,
    TRUE = 1,
}Boolean;

typedef struct Node{
    Color color;        //颜色
    int* key;           //键值
    struct Node *parent,*left,*right;
}Node,*nodep;

typedef struct Tree{
    nodep root; //根节点
    int size;   //节点数目
}Tree,*treep;

nodep node(int key);            //创建一个节点
nodep nullnode(nodep pa);       //创建一个nil节点
treep tree();           //创建一棵空树
Boolean insertNode(treep t,int key);    //向树中插入
Boolean _insertNode(treep t,nodep* rootp,int key);  //原始的insert方法
Boolean insertFix(treep t,nodep n);     //插入修复
Boolean deleteNode(treep t,int key);    //删除树中指定的元素
Boolean _deleteNode(treep t,nodep* rootp,int key);  //原始的insert方法
Boolean deleteFix(treep t,nodep n);     //删除修复
nodep rotate_left(treep t,nodep nd);    //左旋nd节点
nodep rotate_right(treep t,nodep nd);   //右旋nd节点
Boolean transplant(treep t,nodep dest,nodep src); //使用src子树替换dest子树
nodep minimum(nodep root);  //获取以root为根节点的最小键
void visit(treep t);        //遍历指定的数
void _visit(nodep root);    //遍历指定根节点子树
nodep search(treep t,int key);      //查找指定的键
#endif