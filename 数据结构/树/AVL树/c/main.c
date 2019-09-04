#include<stdio.h>
#include<stdlib.h>

#define max(a,b) ((a)>(b)?(a):(b))
typedef struct Node{
    struct Node *left;  //左子树
    struct Node *right; //右子树
    int key;    //树的键名
    int val;    //树存储的数据
    int height; //当前节点的高度
}Node,*pNode;

//获得树的高度
int height(pNode node){
    if(node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return (node->height = max(leftHeight,rightHeight)+1);
}

//平衡因子的高度
int factor(pNode root){
    if(root == NULL) return 0;
    return height(root->left) - height(root->right);
}

//树左旋
void rotate_left(pNode *pRoot){
    pNode root = *pRoot;
    pNode right = root->right;
    root->right = right->left;
    right->left = root;
    *pRoot = right;
}

//树右旋
void rotate_right(pNode *pRoot){
    pNode root = *pRoot;
    pNode left = root->left;
    root->left = left->right;
    left->right = root;
    *pRoot = left;
}

//LL旋转
void LL(pNode *pRoot){
    rotate_right(pRoot);
}

//RR旋转
void RR(pNode *pRoot){
    rotate_left(pRoot);
}

//LR旋转
void LR(pNode *pRoot){
    pNode root = *pRoot;
    rotate_left(&(root->left));
    rotate_right(pRoot);
}

//RL旋转
void RL(pNode *pRoot){
    pNode root = *pRoot;
    rotate_right(&(root->right));
    rotate_left(pRoot);
}


//调整
void balance(pNode *pRoot){
    pNode root = *pRoot;
    if(root == NULL) return;
    int fact = factor(root);   //平衡因子
    if(fact == 2){
        if(factor(root->left) > 0){    //LL
            LL(pRoot);
        }else{
            LR(pRoot);
        }
    }else if(fact == -2){
        if(factor(root->right) > 0){   //RL
            RL(pRoot);
        }else{
            RR(pRoot);
        }
    }
}

//插入键值对
int insert(pNode *pRoot,int key,int val){
    pNode root = *pRoot;
    if(root == NULL){   //无当前节点
        root = (pNode)malloc(sizeof(Node));
        root->key = key;
        root->val = val;
        root->height = 0;
        root->left = root->right = NULL;
        *pRoot = root;
    }else if(root->key == key){ //存在该元素
        return -1;
    }else if(root->key > key){  //当前节点大于需要查找的节点,向左子树查找
        insert(&(root->left),key,val);
    }else if(root->key < key){
        insert(&(root->right),key,val);
    }

    balance(pRoot);
}

//获取指定键的数据
int get(pNode root,int key){
    if(root == NULL) return -1;
    if(root->key == key) return root->val;
    else if(root->key > key) return get(root->left,key);
    else return get(root->right,key);
}

void preVisit(pNode root){
    if(root == NULL) return;
    printf("%d[%d] ",root->key,root->val);
    preVisit(root->left);
    preVisit(root->right);
}

int main(){
    pNode root = NULL;
    for(int i = 0; i < 10; i++)
        insert(&root,i,i);
    preVisit(root);

    return 0;
}
