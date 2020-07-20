#include"huffman.h"

int main(){
    // hufflistp list = hufflist();

    // int kvs[][2] = {    //key,weight
    //     {1,12},
    //     {2,18},
    //     {3,9},
    //     {4,15},
    //     {5,11},
    //     {6,16},
    //     {7,12},
    // };
    
    // int kvl = sizeof(kvs) / sizeof(kvs[0]);

    // for(int i = 0; i < kvl; i++){
    //     insertHuffNode(list,huffnode(kvs[i][0],kvs[i][1]));
    // }

    // hufflistnodep tmp = NULL;

    // // for(tmp = list->head; tmp != NULL; tmp = tmp->next){
    // //     printf("%d{%d}\n",tmp->node->key,tmp->node->weight);
    // // }

    // hufftreep tree = hufftree(list);
    char* input = "test1.txt";
    char* output = "test2.huff";

    huffresultp result = getHuffCodesByFile(input);
    if(result != NULL){
        int l = strlen(result->code);
        // printf("%s\n",result->code);
        huffbufp origin = getOriginBuf(result);
        if(origin != NULL){
            // printf("%s\n",origin->code);
            // printf("原文大小:%d\n",origin->size);
            // printf("压缩大小:%d[%d]\n",l,(l/8)+(l%8 > 0));
        }else
            printf("解析失败\n");

        putOriginToFile(result,output);
    }else
        printf("Failed\n");

    huffbufp tmp = readHuffFile(output);
    printf("%s\n",tmp ? tmp->code : "Failed\n");

    return 0;
}
