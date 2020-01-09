#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct NODE{
    int key;
    int val;
    struct NODE *next;
    struct NODE *next_level;
}Node,*pnode;

typedef struct SKIPNODE{
    pnode head;
    struct SKIPNODE *prev;
    struct SKIPNODE *next;
}Skipnode,*pskipnode;

typedef struct{
    pskipnode head;
    pskipnode tail;
}Skiplist,*skiplist;

pnode node(int key,int val){
    pnode ret = (pnode)malloc(sizeof(Node));
    ret->key = key;
    ret->val = val;
    ret->next = NULL;
    ret->next_level = NULL;
    return ret;
}

pnode _insert(skiplist* plist,pskipnode* phead,pnode * pcur,int key,int val){
    skiplist list = *plist;
    pskipnode head = (phead == NULL ? NULL : *phead);
    pnode cur = (pcur == NULL ? NULL : *pcur);
    if(list == NULL){   //空list
        list = (skiplist)malloc(sizeof(Skiplist));
        head = (pskipnode)malloc(sizeof(Skipnode));
        list->head = list->tail = head;
        head->head = node(key,val);
        head->prev = head->next = NULL;
        *plist = list;
        printf("创建第一个节点\n");
        return head->head;
    }else if(head == NULL){ //跑到了list顶端上一层
        head = (pskipnode)malloc(sizeof(Skipnode));
        head->head = node(key,val);
        head->prev = NULL;
        head->next = list->head;
        list->head = head;  //设置新的head
        return head->head;
    }else if(cur == NULL){  //当前元素为空
        return NULL;    //这种情况不存在
    }else{
        if(cur->key == key){    //找到当前key
            cur->val =val;
            if(head->next && cur->next_level) return _insert(plist,&(head->next),&(cur->next_level),key,val);  //递归到下一层
            return NULL;    //到达最底端
        }else if(cur->key < key){   //当前key可能在右边
            for(;cur->next != NULL && cur->next->key < key;cur = cur->next);
            pnode next= cur->next;
            if(cur->next_level == NULL){    //到达最后一层
                cur->next = node(key,val);
                cur->next->next = next;
                int rnd = rand();
                if(head->prev == NULL && (rnd&1)){ //第一层
                    printf("RUN:%d\n",key);
                    head = (pskipnode)malloc(sizeof(head));
                    head->head = node(key,val);
                    head->head->next_level = cur->next;
                    head->prev = NULL;
                    head->next = list->head;
                    list->head->prev = head;
                    list->head = head;
                    return NULL;
                }
                return cur->next;
            }else{
                pnode next_level = _insert(plist,&(head->next),&(cur->next_level),key,val);
                if(next_level != NULL && (rand()&1)){   //需要上升一层
                    //创建新节点
                    pnode n = node(key,val);
                    n->next_level = next_level;
                    n->next = cur->next;
                    cur->next = n;
                    if(head->prev == NULL){ //到达第一层
                        head = (pskipnode)malloc(sizeof(Skipnode));
                        head->next = list->head;
                        head->prev = NULL;
                        head->head = n;
                        list->head->prev = head;
                        list->head = head;
                        return NULL;    //不再更新
                    }
                    return n;   //创建了新的节点,将其返回
                }
                return NULL;    //不需要更新
            }
        }else{  //当前节点比key大,这种情况可能出现在插入一个比现有表中的数据小的数据的时候.
            pnode n = node(key,val);
            n->next = head->head;
            head->head = n;
            if(cur->next_level != NULL){    //非最后一层
                n->next_level = _insert(plist,&(head->next),&(cur->next_level),key,val);
            }
            return NULL;
        }
    }
}
int insert(skiplist* plist,int key,int val){
    skiplist list = *plist;
    pskipnode* phead = (list == NULL) ? NULL : &(list->head);
    pnode *pcur = (phead == NULL) ? NULL : &((*phead)->head);
    return NULL != _insert(plist,phead,pcur,key,val);
}

void visit(skiplist list){
    if(list == NULL) return;
    pskipnode head = list->head;
    for(;head != NULL;head = head->next){
        pnode tmp = NULL;
        for(tmp = head->head; tmp != NULL; tmp = tmp->next){
            //printf("%d(%p:%p)",tmp->key,tmp,tmp->next_level);
            printf("[%d]%d",tmp->key,tmp->val);
            if(tmp->next) printf("->");
        }
        puts("");
    }
}

int search(skiplist list,int key,int *ret){
    if(list == NULL) return 0; //查找失败
    pskipnode head = list->head;
    for(;head != NULL; head = head->next){
        pnode tmp = NULL;
        for(tmp = head->head; tmp != NULL; tmp = tmp->next){
            if(tmp->key == key){
                *ret = tmp->val;
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    srand(time(NULL));
    skiplist list = NULL;
    int arr[] = {1,3,4,0,0,5,8,5,9,0};
    int size = sizeof(arr) / sizeof(arr[0]);
    int i;
    //插入
    for(i = 0; i < size; i++)
        insert(&list,i,arr[i]);
    //遍历
    visit(list);
    //查找
    int ret;
    for(i = 0; i < size; i++){
        int result = search(list,i,&ret);
        if(result)
            printf("%d\n",ret);
        else
            printf("没有找到%d\n",i);
    }
    return 0;
}
