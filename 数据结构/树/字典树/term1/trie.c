#include "trie.h"

triep trie(){
    triep tree = (triep)malloc(sizeof(Trie));
    tree->root = NULL;
    tree->size = 0;

    return tree;
}

trienodep trienode(byte key,void* data,int size){
    trienodep node = (trienodep)malloc(sizeof(TrieNode));
    node->key = key;
    node->data = data;
    node->size = size;
    node->next = NULL;
    node->next_level = NULL;

    return node;
}

Boolean insertNode(triep tree,string key,void* data,int size){
    return _insertNode(tree,key,data,size,TRUE,FALSE);
}

Boolean _insertNode(triep tree,string key,void* data,int size,Boolean fail_when_exists,Boolean fail_when_not_exists){
    if(tree == NULL || key == NULL) return FALSE;
    int col,row;
    trienodep* nodep = &(tree->root);
    trienodep* last_nodep = NULL;
    trienodep node = tree->root;
    for(row = 0; key[row] != '\0'; row++){  //遍历所有字符
        byte ch = (byte)key[row];
        for(;node != NULL && node->key != ch;node = node->next){
            nodep = &(node->next);
        }
        if(node == NULL){   //节点不存在,则创建节点
            if(fail_when_not_exists == TRUE){  //如果fail_when_not_exists设定为true
                return FALSE;
            }
            node = trienode(ch,NULL,size);
            *nodep = node;
        }
        last_nodep = nodep; //记录最后一级的指针
        nodep = &(node->next_level);
        node = node->next_level;    //node移至下一级
    }
    if(last_nodep == NULL) return FALSE;    //空字符串
    trienodep last = *last_nodep;
    if(fail_when_exists == TRUE && last->data != NULL) return FALSE;    //设置fail_when_exists标志
    if(last->data != NULL){
        free(last->data);
        last->data = NULL;
    }else{  //当前元素不存在
        tree->size++;
    }
    last->data = malloc(size);
    memcpy(last->data,data,size);

    return TRUE;    //插入成功
}

trienodep  searchNode(triep tree,string key){
    int col,row;
    trienodep node = tree->root;
    trienodep last = NULL;
    for(row = 0; key[row] != '\0'; row++){  //遍历所有字符
        byte ch = (byte)key[row];
        for(;node != NULL && node->key != ch;node = node->next);
        if(node == NULL){   //节点不存在,则创建节点
            return NULL;
        }
        last = node;
        node = node->next_level;    //node移至下一级
    }
    return last;    //返回找到的节点
}

searchresultp search(triep tree,string key){
    trienodep res = searchNode(tree,key);
    searchresultp result = (searchresultp)malloc(sizeof(SearchResult));
    result->data = NULL;
    result->status = (res != NULL ? TRUE : FALSE);
    if(result->status == TRUE){
        result->data = res->data;
    }
    return result;
}

Boolean updateNode(triep tree,string key,void* data,int size){
    return _insertNode(tree,key,data,size,FALSE,TRUE);
}

Boolean updateOrSetNode(triep tree,string key,void* data,int size){
    return _insertNode(tree,key,data,size,FALSE,FALSE);
}

Boolean deleteNode(triep tree,string key){
    return _deleteNode(tree,key,FALSE); //采用普通方式抹除
}

Boolean _deleteNode(triep tree,string key,Boolean recusive_delete){
    if(tree == NULL || key == NULL) return FALSE;
    int col,row;
    trienodep* path[8192];   //路径栈
    int path_idx = -1;      //路径顶部
    trienodep node = tree->root;
    trienodep* nodep = &tree->root;
    trienodep* last_nodep = NULL;
    trienodep last = NULL;
    for(row = 0; key[row] != '\0'; row++){  //遍历所有字符
        byte ch = (byte)key[row];
        for(;node != NULL && node->key != ch;node = node->next);
        if(node == NULL){   //节点不存在,则创建节点
            return FALSE;
        }
        path[++path_idx] = nodep;    //记录当前路径节点的指针
        last = node;
        last_nodep = nodep;
        nodep = &(node->next_level);
        node = node->next_level;    //node移至下一级
    }
    if(recusive_delete == TRUE){
        for(;path_idx >= 0;path_idx--){
            trienodep* tmp = path[path_idx];    //节点缓存
            if(tmp == NULL) return FALSE;
            if((*tmp) != last && (*tmp)->data != NULL) break; 
            if((*tmp)->next_level == NULL){
                trienodep next = (*tmp)->next;
                if(*tmp != NULL)
                    free(*tmp); //释放*tmp
                *tmp = next;
            }
        }
    }else{
        if(last->data != NULL)
            free(last->data);
        last->data = NULL;
    }
    tree->size--;

    return TRUE;
}

Boolean hardDeleteNode(triep tree,string key){
    return _deleteNode(tree,key,TRUE);
}