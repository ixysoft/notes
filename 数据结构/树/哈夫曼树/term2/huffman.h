#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define START printf("=====start=====\n")
#define END printf("=====end=====\n")
#define toByte(n) ((n) / 8 + ((n) % 8 > 0))

typedef struct HuffListNode HuffListNode,*hufflistnodep;
typedef struct HuffNode HuffNode,*huffnodep;
typedef struct HuffTree HuffTree,*hufftreep;
typedef struct HuffCode HuffCode,*huffcodep;
typedef struct HuffList HuffList,*hufflistp;
typedef struct HuffResult HuffResult,*huffresultp;
typedef struct HuffCode HuffBuf,*huffbufp;  //缓存类型

struct HuffListNode{
    huffnodep node;     //huffman节点
    hufflistnodep next; //后继节点
};  //huffman频率节点

struct HuffList{
    hufflistnodep head;         //头结点
    int keys[256];              //键值字典
    int size;                   //链表长度
};

struct HuffNode{
    int key;            //键
    int weight;         //权重
    huffnodep left;     //左节点
    huffnodep right;    //右节点
};  //huffman节点

struct HuffCode{
    char* code; //huffman code
    int size;   //huffman code size
};

struct HuffTree{
    huffnodep root;         //根
    huffcodep codes[256];   //key对应的代码
    int size;               //大小
};  //huffman树

struct HuffResult{
    char* code;      //生成的代码
    hufftreep tree;  //对应的哈夫曼树
};

#ifndef __BOOLEAN__
#define __BOOLEAN__
typedef enum{
    FALSE = 0,
    TRUE = 1,
}Boolean;
#endif

huffnodep huffnode(int key,int weight); //初始化huffman节点
hufflistp hufflist();   //初始化hufflist
Boolean insertHuffNode(hufflistp list,huffnodep node);  //向指定的节点链表添加一个节点
huffnodep shiftHuffNode(hufflistp list);    //删除第一个节点
hufftreep hufftree(hufflistp list);   //构建一棵huffman tree
huffbufp getFileBuf(const char* filename); //获取文件的buf
hufftreep genhuffcodes(hufftreep tree,huffnodep node,char codes[],int idx);  //获取当前节点之下的节点的huffman编码
hufflistp getHuffListByFile(const char* filename); //根据文件创建huffman链表
hufflistp getHuffListByBuf(huffbufp buf); //根据文件buf创建huffman链表
huffcodep getHuffCode(hufftreep tree,int key);  //获取指定键值的huffcode
huffresultp getHuffCodesByFile(const char* filename);     //获取文件的huffman code
huffbufp getOriginBuf(huffresultp result);       //从result中解析出原始的字符串
huffbufp str2bin(char* str); //二进制字符串转二进制数组
int putOriginToFile(huffresultp result,const char* filename);   //将result存储到filename中
char* bin2str(huffbufp buf);    //二进制数组转二进制字符串
huffbufp readHuffFile(const char* filename); //解析huff文件
#endif