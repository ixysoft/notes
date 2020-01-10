#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>

#define SIZE 1000
int arr[SIZE];

typedef struct Data{
    int val;
}Data,*pdata;    //data类型

typedef struct Node{
    int key;    //键
    pdata data;  //数据
    struct Node * next;
    struct Node * next_level;
}Node,*pnode;    //普通节点

typedef struct Head{
    pnode head;          //头结点
    struct Head * prev_level; //前驱指针
    struct Head * next_level; //后继指针
}Head,*phead;    //头结点

typedef struct SkipList{
    phead head;
    phead tail;
    int level;
}SkipList,*pskiplist;

//创建一个普通节点
pnode node(int key,pdata data){
    pnode ret = (pnode)malloc(sizeof(Node));
    ret->key = key;
    ret->next = ret->next_level = NULL;
    ret->data = data;
    return ret;
}

//创建新的一层
void create_new_level(pskiplist* plist,pnode next_level,int key,pdata data){
    pskiplist list = *plist;
    phead head = (phead)malloc(sizeof(Head));
    head->prev_level = NULL;
    pnode root = node(key,data);
    root->next_level = next_level;
    head->head = root;
    if(list == NULL){   //空表
        list = (pskiplist)malloc(sizeof(SkipList));
        list->head = list->tail = head;
        list->level = 1;
        head->next_level = NULL;
        *plist = list;
    }else{
        head->next_level = list->head;
        list->head->prev_level = head;
        list->head = head;
        list->level++;
    }

}

int should_up(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_usec & 1;
}

pnode _insert(pskiplist * pList,phead * pHead,pnode * pCur,int key,int val){
    pskiplist list = * pList;
    if(list == NULL){
        pdata data = (pdata)malloc(sizeof(Data));
        data->val = val;
        create_new_level(pList,NULL,key,data);  //创建根节点
        return NULL;
    }
    phead head = (pHead == NULL?NULL:*pHead);
    pnode cur = (pCur == NULL ? NULL : *pCur);
    if(head == NULL || cur == NULL){   //头指针或当前节点为空
        return NULL;
    }

    if(cur->key == key){    //已经存在该键值
        cur->data->val = val;
        return NULL;
    }else if(cur->key < key){   //当前键值小于需要查找的键
        //printf("找%d\n",key);
        for(;cur->next != NULL && cur->next->key <= key;cur = cur->next);
        if(cur->key == key){    //存在该节点
            cur->data->val = val;
            return NULL;
        }else{    //尾部或者到临界节点
            pnode ret = NULL;
            if(cur->next_level == NULL){
                //printf("最后一层停在:%d\n",cur->key);
                pdata data = (pdata)malloc(sizeof(Data));
                data->val = val;
                pnode root = node(key,data);
                root->next = cur->next;
                cur->next = root;
                if(should_up()){
                    if(head->prev_level == NULL)    //第一层
                        create_new_level(pList,root,key,root->data);
                    else
                        return root;
                }
                return NULL;
            }

            ret = _insert(pList,&(head->next_level),&(cur->next_level),key,val);
            if(ret != NULL){    //存在返回值
                pnode root = node(key,ret->data);//当前节点的下一节点
                root->next = cur->next;
                root->next_level = ret;
                cur->next = root;
                if(should_up()){
                    if(head->prev_level == NULL)    //第一层
                        create_new_level(pList,root,key,ret->data);
                    else
                        return root;
                }
            }
            return NULL;
        }
    }else{  //当前键值大于需要查找的键
        //printf("最左端找%d\n",key);
        pnode ret = NULL;
        if(head->next_level == NULL){
            pdata data = (pdata)malloc(sizeof(Data));
            data->val = val;
            ret = node(key,data);
            ret->next = head->head;
        }else{
            ret = _insert(pList,&(head->next_level),&(head->next_level->head),key,val);
            if(ret != NULL){
                //printf("添加:%d\n",ret->key);
                pnode tmp = ret;
                ret = node(key,ret->data);
                ret->next = head->head;
                ret->next_level = tmp;
            }
        }

        if(head->head == cur && ret != NULL){  //当前为第一个元素
            head->head = ret;
        }
        if(should_up()){
            if(head->prev_level == NULL && ret != NULL)
                create_new_level(pList,ret,key,ret->data);
            else
                return ret;
        }
    }
    return NULL;
}

void insert(pskiplist * pList,int key,int val){
    pskiplist list = *pList;
    phead * pHead = list == NULL ? NULL:&(list->head);
    pnode * pCur = pHead == NULL ? NULL : &((*pHead)->head);
    _insert(pList,pHead,pCur,key,val);
}

void visit(pskiplist list){
    if(list == NULL) return;
    phead head = list->head;
    for(;head != NULL; head = head->next_level){
        pnode tmp = NULL;
        for(tmp = head->head; tmp != NULL; tmp = tmp->next){
            printf("[%d]%d",tmp->key,tmp->data->val);
            //printf("[%d]",tmp->key);
            //printf("[%d]%p",tmp->key,tmp->next_level,tmp->data->val);
            if(tmp->next) printf("->");
        }
        puts("");
    }
}

void gen(int arr[],int size,int scale){
    int i;
    for(i = 0; i < size; i++){
        arr[i] = rand() % scale;
    }
}

int search(pskiplist list,int key,int * ret){
    if(list == NULL || list->head == NULL) return 0;
    phead head = list->head;
    pnode tmp = head->head;
    while(tmp != NULL){
        if(key == tmp->key){
            *ret = tmp->data->val;
            return 1;
        }else if(key < tmp->key || tmp->next == NULL || tmp->next->key > key){
            if(head->head == tmp){
                head = head->next_level;
                tmp = head == NULL ? NULL:head->head;
            }else{
                head = head->next_level;
                tmp = tmp->next_level;
            }
        }else{
            tmp = tmp->next;
        }
    }
    return 0;
}

int main(){
    srand(time(NULL));
    gen(arr,SIZE,40);
    int i;
    pskiplist list = NULL;
    int d[] = {
        1,3,4,0,0,5,8,5,9,0
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    for(i = 0; i < size; i++){
        insert(&list,arr[i],i);
        //visit(list);
        //puts("");
    }
    visit(list);
    int ret = 0;
    int key = 4;
    if(search(list,key,&ret)){
        printf("val:%d\n",ret);
    }else{
        printf("没有找到:%d\n",key);
    }

    return 0;
}
