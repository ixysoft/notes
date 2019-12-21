/**
 *  AVL树的c语言实现  
 **/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Node{
    int key;    //键
    int val;    //值，实际中键和值都可以用替换为其他类型
    int height; //节点的高度，从1算起
    struct Node *left;  //左子节点
    struct Node *right; //右子节点
}Node,*pnode;

//获取某个节点的高度
#define height(p) ((p) == NULL ? 0 : (p)->height)
//取两个数字中的较大值
#define max(a,b) ((a) > (b) ? (a) : (b))
//获取某个节点的平衡因子
#define bf(p) ((p) == NULL ? 0 : height(p->left) - height(p->right))

void LL(pnode* proot);
void RR(pnode* proot);
void LR(pnode* proot);
void RL(pnode* proot);
void insert(pnode* proot,int key,int val);  //插入节点
int delete(pnode* proot,int key);   //删除节点
int search(pnode root,int key); //查找节点
int cmp(const void* a,const void* b);
int batchInsert(pnode* proot,int arr[],int size);//批量插入
void preOrderVisit(pnode root); //先序遍历
void genRandom(int arr[],int size); //生成随机数据
void deleteMax(pnode *proot,int* key,int* val);   //删除左边最大元素
void deleteMin(pnode *proot,int* key,int* val);   //删除右边最小元素
pnode adjust(pnode root);

#define SIZE 10000000
//int arr[SIZE];
int arr[] = {
    1,3,4,0,0,5,8,5,9,0
};

int main(){
    srand(time(NULL));
    size_t size = sizeof(arr) / sizeof(arr[0]);
    //genRandom(arr,size);
    pnode root = NULL;
    int i;

    //在batchInsert中对arr进行了一次排序
    batchInsert(&root,arr,size);
    for(i = 0; i < 5; i++)delete(&root,arr[i]);;

    preOrderVisit(root);
    //int finder = 4;
    //printf("search %d:%d\n",finder,search(root,finder));
    return 0;
}

void genRandom(int arr[],int size){ //生成随机数据
    int i;
    for(i = 0; i < size; i++){
        arr[i] = random() % size;
    }
}

int batchInsert(pnode* proot,int arr[],int size){
    int i;
    qsort(arr,size,sizeof(int),cmp);
    for(i = 0; i < size; i++)
        insert(proot,arr[i],arr[i]);
    return size;
}

int cmp(const void* a,const void* b){
    return *(int*)a > *(int*)b;
}

//父子孙左左排布
void LL(pnode * proot){ //选择二重指针的原因是跟节点的地址需要变动并传递到外界
    pnode root = *proot;
    if(root == NULL) return;
    pnode left = root->left;
    root->left = left->right;
    left->right = root; //根节点变为左节点的右孩子
    
    //先更新根节点的高度，因为此时根节点位于左孩子下方
    root->height = max(height(root->left),height(root->right))+1;
    //更新左节点的高度
    left->height = max(height(left->left),root->height)+1;
    *proot = left;
}

//父子孙右右排列
void RR(pnode * proot){
    pnode root = *proot;
    if(root == NULL) return;
    pnode right = root->right;
    root->right = right->left;
    right->left = root;

    root->height = max(height(root->left),height(root->right))+1;
    right->height = max(height(root),height(right->right))+1;
    *proot = right;
}

//LR排列
void LR(pnode * proot){
    pnode root = * proot;
    if(root == NULL) return;
    RR(&(root->left));
    LL(proot);
}

//RL排列
void RL(pnode * proot){
    pnode root = * proot;
    if(root == NULL) return;
    LL(&(root->right));
    RR(proot);
}

//调整节点
pnode adjust(pnode root){
    root->height = max(height(root->left),height(root->right))+1;   //更新当前节点的高度
    if(bf(root) == 2){  //树向左倾斜
        if(height(root->left) > height(root->right)){    //向左倾斜
            LL(&root);
        }else{
            LR(&root);
        }
    }else if(bf(root) == -2){   //向右倾斜
        if(height(root->left) > height(root->right)){   //向左倾斜
            RL(&root);
        }else{
            RR(&root);
        }
    }
    return root;
}

void insert(pnode * proot,int key,int val){
    pnode root = * proot;
    if(root == NULL){   //根节点为空,创建新节点
        root = (pnode)malloc(sizeof(Node));
        root->left = root->right = NULL;
        root->height = 1;
        root->key = key;
        root->val = val;
    }else if(root->key == key){
        root->val = val;    //替换为当前值
    }else if(root->key < key){  //key可能在当前节点右边
        insert(&(root->right),key,val);
    }else{  //key可能在当前节点左边
        insert(&(root->left),key,val);
    }

   *proot = adjust(root);
}

void preOrderVisit(pnode root){
    if(root == NULL) return;
    printf("[%d]=>%d\n",root->key,root->val);
    preOrderVisit(root->left);
    preOrderVisit(root->right);
}


int delete(pnode* proot,int key){
    pnode root = *proot;
    if(root == NULL) return 0;  //删除失败
    if(root->key == key){   //找到节点
        int key,val;
        //如果找到节点，则使用左侧最大的节点或者右侧最小的节点替换当前节点
        if(root->left != NULL){ //左节点存在
            deleteMax(&(root->left),&key,&val);
        }else if(root->right != NULL){
            deleteMin(&(root->right),&key,&val);
        }else{
            free(root);
            *proot = NULL;
            return 1;
        }
        root->key = key;
        root->val = val;
        *proot = adjust(root);
        return 1;
    }else if(root->key > key){
        return delete(&(root->left),key);
    }else{
        return delete(&(root->right),key);
    }
}

int search(pnode root,int key){
    if(root == NULL) return -1;
    if(root->key == key) return root->val;
    else if(root->key < key) return search(root->right,key);    //向右查找
    else return search(root->left,key); //向左查找
}

//删除左边最大元素并返回
void deleteMax(pnode *proot,int* key,int* val){   //删除左边最大元素
    pnode root = *proot;
    if(root->right == NULL){    //这里假定root节点存在
        *key = root->key;
        *val = root->val;
        free(root);
        root = NULL;
    }else{
        deleteMax(&(root->right),key,val);
        root = adjust(root);
    }
    *proot = root;
}
void deleteMin(pnode *proot,int* key,int* val){   //删除右边最小元素
    pnode root = *proot;
    if(root->left == NULL){
        *key = root->key;
        *val = root->val;
        free(root);
        root = NULL;
    }else{
        deleteMin(&(root->left),key,val);
    }
    *proot = root;
}
