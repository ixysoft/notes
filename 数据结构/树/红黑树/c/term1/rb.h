#ifndef __RB_H__
#define __RB_H__
/**
 *  红黑树头文件
 **/
#include<stdio.h>
#include<stdlib.h>

//颜色
typedef enum{
    RED = 0,
    BLACK = 1
}Color;

//红黑树节点
typedef struct Node{
    int key;    //键
    int val;    //值
    Color color;    //颜色
    struct Node *left;  //左子节点
    struct Node *right; //右子节点
    struct Node *parent;//父节点
}Node,*node;
typedef node* Tree;
//判断是否是红节点
#define isRed(p) ((p) != NULL && (p)->color == RED)
//判断是否为黑节点
#define isBlack(p) ((p) != NULL && (p)->color == BLACK)
//父节点
#define parent(p) ((p)->parent)
//祖父节点
#define grandpa(p) (parent(parent(p)))
//叔父节点
#define uncle(p) (grandpa(p)->left == parent(p) ? grandpa(p)->right : grandpa(p)->left)

node rotate_left(node root);    //左旋
node rotate_right(node root);   //右旋
int search(Tree tree,int key);  //查找key
void insert(Tree tree,int key,int val);
void adjust(Tree tree,node root);   //调整指定节点
void delete(Tree tree,int key);     //删除键
void deleteMin(Tree tree,int *key,int *val);    //删除最小子节点并返回键值
void deleteMax(Tree tree,int *key,int *val);    //删除最大子节点并返回键值
void getNodeInfo(node root,char* prefix);   //获取节点信息
void preOrderVisit(node root);  //先序遍历

#endif
