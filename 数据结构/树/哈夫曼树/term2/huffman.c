#include "huffman.h"

huffnodep huffnode(int key,int weight){
    huffnodep ret = (huffnodep)malloc(sizeof(HuffNode));
    ret->key = key;
    ret->weight = weight;
    ret->left = ret->right = NULL;

    return ret;
}

hufflistp hufflist(){
    hufflistp ret = (hufflistp)malloc(sizeof(HuffList));
    ret->head = NULL;
    memset(ret->keys,0,sizeof(ret->keys[0])*256);
    ret->size = 0;

    return ret;
}

Boolean insertHuffNode(hufflistp list,huffnodep node){
    if(list == NULL || node == NULL || node->weight <= -256) return FALSE;
    hufflistnodep cur = list->head;
    hufflistnodep* rootp = &(list->head);
    hufflistnodep* last = NULL; //当前指针的前驱指针
    hufflistnodep tmp = (hufflistnodep)malloc(sizeof(HuffListNode));
    tmp->node = node;
    tmp->next = NULL;
    if(node->key >= 0 && node->key < 256){
        list->keys[node->key] = node->weight;   //添加key到keys字典
    }
    list->size++;

    for(;cur != NULL  && cur->node->weight < node->weight; cur = cur->next){
        last = rootp;
        rootp = &(cur->next);
    }

    tmp->next = cur;
    if(last == NULL){   //第一个元素
        list->head = tmp;
    }else{  //向当前节点前面插入tmp节点
        (*last)->next = tmp;
    }

    return TRUE;
}

huffnodep shiftHuffNode(hufflistp list){
    if(list == NULL || list->head == NULL) return NULL;
    huffnodep ret = list->head->node;
    hufflistnodep next = list->head->next;
    free(list->head);
    list->head = next;
    list->size--;

    return ret;
}

//通过huffman list构建
hufftreep hufftree(hufflistp list){
    hufftreep tree = (hufftreep)malloc(sizeof(HuffTree));
    tree->root = NULL;
    tree->size = 0;
    memset(tree->codes,0,sizeof(tree->codes));

    huffnodep a = NULL;
    huffnodep b = NULL;
    huffnodep c = NULL;
    tree->size = 2 * list->size - 1;
    while(list->size > 1){  //hufflistp长度大于1
        a = shiftHuffNode(list);
        b = shiftHuffNode(list);
        c = huffnode(-256,a->weight+b->weight);    //新的节点
        c->left = a;
        c->right = b;
        insertHuffNode(list,c); //将c压回list
    }
    tree->root = c;

    //生成所有key的huffman编码
    char codes[8092];   //huffman编辑路径

    return genhuffcodes(tree,tree->root,codes,0);
}

//获取文件内容的BUF
huffbufp getFileBuf(const char* filename){
    FILE* fp = fopen(filename,"r");
    if(fp == NULL) return NULL;
    fseek(fp,0L,SEEK_END);
    int len = ftell(fp);
    rewind(fp); //重设
    huffbufp ret = (huffbufp)malloc(sizeof(HuffBuf));
    ret->code = (char*)malloc(len+1);
    ret->size = len;
    fread(ret->code,1,len,fp);
    fclose(fp);

    return ret;
}

hufftreep genhuffcodes(hufftreep tree,huffnodep node,char codes[],int idx){
    if(tree == NULL || node == NULL){   //到达底部
        return NULL;
    }

    if(node->left == NULL && node->right == NULL){  //叶子节点
        int key = node->key;
        huffcodep code = (huffcodep)malloc(sizeof(HuffCode));
        code->code = (char*)malloc(idx+1);
        code->size = idx;
        memcpy(code->code,codes,code->size);
        code->code[code->size] = '\0';
        tree->codes[key] = code;
    }{
        codes[idx] = '1'; //右
        genhuffcodes(tree,node->right,codes,idx+1);
        codes[idx] = '0'; //左
        genhuffcodes(tree,node->left,codes,idx+1);
    }

    return tree;
}

//通过文件生成huffman list
hufflistp getHuffListByFile(const char* filename){
    huffbufp buf = getFileBuf(filename);
    if(buf == NULL) return NULL;

    hufflistp list = getHuffListByBuf(buf);
    free(buf->code);
    buf->code = NULL;
    free(buf);
    buf = NULL;

    return list;
}

hufflistp getHuffListByBuf(huffbufp buf){
    if(buf == NULL || buf->code == NULL) return NULL;

    char* code = buf->code;

    hufflistp list = hufflist();
    for(int i = 0; code[i] != '\0'; i++){
        unsigned char ch = code[i];
        list->keys[ch]++;
    }

    for(int i = 0; i < 256; i++){
        if(list->keys[i] > 0){   //插入存在的字符
            insertHuffNode(list,huffnode(i,list->keys[i]));
        }
    }

    return list;
}

huffcodep getHuffCode(hufftreep tree,int key){
    if(key < 256 && key >= 0 && tree->codes[key] > 0){
        return tree->codes[key];
    }
    return NULL;
}

huffresultp getHuffCodesByFile(const char* filename){
    huffresultp result = (huffresultp)malloc(sizeof(HuffResult));
    result->code = NULL;
    huffbufp buf = getFileBuf(filename);   //文件缓存
    if(buf == NULL) return NULL;

    hufflistp list = getHuffListByBuf(buf); //huffman list

    result->tree = hufftree(list);
    int buf_len = buf->size;
    int len = 0;
    for(int i = 0; buf->code[i] != '\0'; i++){
        int key = (unsigned char)buf->code[i];
        huffcodep code = getHuffCode(result->tree,key);
        if(code == NULL){
            printf("LLL:%c{%d}\n",key,key);
            return NULL;
        }
        len+=code->size;
    }
    result->code = (char*)malloc(len+1);
    result->code[0] = '\0';
    for(int i = 0; buf->code[i] != '\0'; i++){
        unsigned char key = buf->code[i];
        huffcodep code = getHuffCode(result->tree,key);
        strncat(result->code,code->code,code->size);
    }

    return result;
}

huffbufp getOriginBuf(huffresultp result){
    if(result == NULL || result->code == NULL || result->tree == NULL) return NULL;
    hufftreep tree = result->tree;
    char* code = result->code;
    int len = 0;
    for(int i = 0; code[i] != '\0';){
        huffnodep root = tree->root;    //根节点
        while(root->left != NULL && root->right != NULL && code[i] != '\0'){   //双子节点存在
            root = (code[i] == '0' ? root->left : root->right);
            i++;
        }
        if((root->left != NULL || root->right != NULL) && code[i] == '\0'){ //错误
            return NULL;
        }
        len++;
        // printf("解析:%c{%s}\n",root->key,tree->codes[root->key]->code);
    }

    huffbufp ret = (huffbufp)malloc(sizeof(HuffBuf));
    ret->code = (char*)malloc(len+1);
    ret->code[0] = '\0';
    ret->size = len;

    int idx = 0;
    for(int i = 0; code[i] != '\0';){
        huffnodep root = tree->root;    //根节点
        while(root->left != NULL && root->right != NULL && code[i] != '\0'){   //双子节点存在
            root = (code[i] == '0' ? root->left : root->right);
            i++;
        }
        ret->code[idx++] = root->key;
    }
    ret->code[idx] = '\0';

    return ret;
}

int putOriginToFile(huffresultp result,const char* filename){
    if(result == NULL) return 0;
    // printf("res1[%d]:%s\n",(int)strlen(result->code),result->code);
    // huffbufp b = str2bin(result->code);
    // printf("%d\n",b->size);
    // printf("res2:%s\n",bin2str(b));
    // return 0;

    huffbufp buf = str2bin(result->code);   //huffman code转成buf
    int i = 0;
    int len = 0;    
    for(i = 0; i < 256; i++){
        if(result->tree->codes[i] > 0){ //
            len+= 5+result->tree->codes[i]->size;   //key[1]:len[4]:size
        }
    }
    huffbufp keys = (huffbufp)malloc(sizeof(HuffBuf));
    keys->code = (char*)malloc(len);
    keys->size = 0;
    //获取keys
    int idx = 0;
    for(i = 0; i < 256; i++){
        if(result->tree->codes[i] > 0){ //
            keys->code[idx++] = i;    //key
            int len = result->tree->codes[i]->size;
            memcpy(keys->code+idx,&len,4);    //key size
            // printf("%c[%d]:%d{%s}\n",i,i,len,result->tree->codes[i]->code);
            idx+=4;
            huffbufp tmp = str2bin(result->tree->codes[i]->code);
            // printf("%d,%d\n",tmp->code[0],tmp->size);
            int tsize = toByte(tmp->size);
            memcpy(keys->code+idx,tmp->code,tsize);
            idx+=tsize;
        }
    }

    keys->size = idx;   //诸多键的总空间
    
    //写出标准文件
    //HUF\n
    //size: 4b
    //keys
    //size: 4b
    //codes
    FILE* fp = fopen(filename,"w");
    if(fp == NULL) return -1;
    fwrite("HUF\n",1,4,fp);
    fwrite(&idx,1,4,fp);    //size
    fwrite(keys->code,1,keys->size,fp); //写入code
    fwrite(&(buf->size),1,4,fp);    //size
    fwrite(buf->code,1,toByte(buf->size),fp);
    fclose(fp);

    return 4+4+keys->size+4+buf->size;
}


huffbufp str2bin(char* str){ //二进制字符串转二进制数组
    // printf("bin:%s\n",str);
    if(str == NULL) return NULL;
    huffbufp buf = (huffbufp)malloc(sizeof(HuffBuf));
    int l = strlen(str);
    int size = (l / 8) + (l % 8 > 0);

    buf->code = (char*)malloc(l);
    memset(buf->code,0,l);
    for(int i = 0; i < l; i++){
        int idx = i/8;
        int bi = i%8;
        buf->code[idx] |= (str[i] == '0' ? 0:1) << bi;
    }
    buf->size = l;

    return buf;
}

char* bin2str(huffbufp buf){
    char* ret = (char*)malloc(buf->size+1);
    for(int i = 0; i < buf->size; i++){
        int idx = i / 8;
        int offset = i % 8;
        ret[i] = (buf->code[idx] & (0x01 << offset)) ? '1' : '0';
    }
    ret[buf->size] = '\0';

    return ret;
}

huffbufp readHuffFile(const char* filename){
    huffbufp buf = getFileBuf(filename);
    if(buf == NULL) return NULL;

    if(memcmp(buf->code,"HUF\n",4) != 0) return NULL;   //文件不以BUF\n开头
    huffresultp result = (huffresultp)malloc(sizeof(HuffResult));
    //BUF\n
    //key size
    int key_size = *(int*)(buf->code+4);
    int base = 8; //偏移量
    hufftreep tree = (hufftreep)malloc(sizeof(HuffTree));
    tree->root = NULL;
    tree->size = 0;
    huffcodep* codes = tree->codes;   //key对应代码
    memset(codes,0,sizeof(huffcodep)*256);
    
    int oft = 0;
    for(;oft < key_size;){
        int offset = base+oft;
        unsigned char key = buf->code[offset];
        // printf("%d[%c]\n",key,key);
        int size = *(int*)(buf->code+offset+1); //长度
        int byte = toByte(size);
        huffbufp htmp = (huffbufp)malloc(sizeof(HuffBuf));
        //键对应代码
        htmp->code = buf->code+offset+5;    //缓存代码
        htmp->size = size;  //缓存大小
        // printf("[%c]%d\n",key,key);
        huffcodep tmp = (huffcodep)malloc(sizeof(HuffCode));
        tmp->size = size;   //key的大小
        tmp->code = bin2str(htmp);
        tree->codes[key] = tmp;
        tree->size++;   //树的大小增加
        huffnodep root = tree->root;
        if(root == NULL){
            tree->root = huffnode(-256,0);
            root = tree->root;
        }
        for(int i = 0; i < tmp->size; i++){
            char ch = tmp->code[i];
            huffnodep node = NULL;
            if(ch == '0'){
                node = root->left;
                if(node == NULL){
                    node = huffnode(-256,0);
                }
                root->left = node;
            }else{
                node = root->right;
                if(node == NULL){
                    node = huffnode(-256,0);
                }
                root->right = node;
            }
            if(i == tmp->size - 1)
                node->key = key;
            root = node;
        }
        oft+=5+byte;
    }

    huffbufp tmp = (huffbufp)malloc(sizeof(HuffBuf));
    tmp->code = buf->code+base+oft+4;
    tmp->size = *(int*)(buf->code+base+oft);
    // printf("tmp size:%d\n",tmp->size);
    result->tree = tree;
    result->code = bin2str(tmp);
    // printf("%s\n",result->code);

    // for(int i = 0; i < 256; i++){
    //     if(codes[i]!=NULL){
    //         printf("%c[%d]:%s\n",i,i,codes[i]->code);
    //     }
    // }

    return getOriginBuf(result);
}
