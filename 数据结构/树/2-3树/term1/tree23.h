#ifndef __TREE23_H__
#define __TREE23_H__
#include<stdlib.h>
#include<stdio.h>
typedef struct Key Key,*keyp;               //关键词链
typedef struct Node Node,*nodep;            //节点
typedef struct Tree Tree,*treep;            //23树
typedef enum{
    FALSE = 0,
    TRUE = 1,
}Boolean;

struct Key{
    int key;
    struct Key* next;
};  //关键词

struct Node{
    struct Node *parent;    //父节点
    keyp        keys;       //关键词链
    nodep       children;   //孩子
    int         size;       //关键词链
    struct Node *next;      //后继节点
};

struct Tree{
    nodep   root;   //树根
    int     size;   //树的大小
};

treep tree();   //新的2，3树
nodep create_node(treep t,keyp first_key,nodep first_child,int size);    //创建新的2-3节点
Boolean insertNode(treep t,int key);            //向t中插入节点key
Boolean _insertNode(treep t,nodep n,int key);   //底层节点插入
Boolean fixNode(treep t,nodep n);               //修复节点
keyp    searchNode(treep t,int key);            //查找关键词
Boolean deleteNode(treep t,int key);
#endif