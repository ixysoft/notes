#ifndef __TRIE_H__
#define __TRIE_H__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//默认删除方式,不指定则优先软删除
#ifdef HARD_DELTE_FIRST
#define deleteNode hardDeleteNode
#else
#define deleteNode softDeleteNode
#endif

typedef enum{
    FALSE = 0,
    TRUE = 1,
}Boolean;   //布尔类型

typedef struct Trie Trie,*triep;
typedef struct TrieNode TrieNode,*trienodep;
typedef unsigned char byte;
typedef char* string;
typedef struct SearchResult SearchResult,*searchresultp;    //查询结果

struct Trie{
    trienodep root; //字典的根
    int size;       //字典大小
};

struct TrieNode{
    byte key;               //节点字符
    void* data;             //节点对应的数据
    int size;               //节点数据大小
    trienodep next;         //同级下一个字符
    trienodep next_level;   //下一层
};

struct SearchResult{
    void* data;         //查询结果
    Boolean status;     //查询状态,0:成功,1:失败
};

triep trie();   //初始化一棵trie树
trienodep trienode(byte key,void* data,int size);    //创建trienode
Boolean insertNode(triep tree,string key,void* data,int size);   //插入节点
trienodep  searchNode(triep tree,string key);   //获取指定key的节点
searchresultp search(triep tree,string key);    //查询指定key的数据
Boolean updateNode(triep tree,string key,void* data,int size);   //更新节点
Boolean updateOrSetNode(triep tree,string key,void* data,int size);  //存在则更新,不存在则创建
Boolean _insertNode(triep tree,string key,void* data,int size,Boolean fail_when_exists,Boolean fail_when_not_exists);    //底层节点插入
Boolean softDeleteNode(triep tree,string key);  //删除指定的节点
Boolean hardDeleteNode(triep tree,string key);  //硬删除指定的节点
/**
 * 节点删除底层逻辑
 * @param triep tree    字典树
 * @param string key    关键词
 * @param Boolean recusive_delete   递归删除标志,FALSE表示单纯设定为NULL
 **/
Boolean _deleteNode(triep tree,string key,Boolean recusive_delete);

Boolean emptyTrie(triep tree);      //清空所有的节点
Boolean destroyTrie(triep* treep);  //清空并释放trie树的空间
#endif