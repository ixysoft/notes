#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int val;
    struct Node *next;
}Node,*node;

void insert(node* proot,int val);
node delete(node root,int k);
void visit(node root);

int main(){
    node root = NULL;
    insert(&root,1);
    insert(&root,2);
    insert(&root,3);
    insert(&root,4);
    insert(&root,5);
    root = delete(root,0);
    insert(&root,5);
    visit(root);
    return 0;
}

//遍历元素
void visit(node root){
    if(root == NULL) return;
    node tmp = NULL;
    for(tmp = root; tmp ; tmp = tmp->next){
        printf("%d%s",tmp->val,tmp->next ? "->" : "");
    }
    puts("");
}

//插入元素
void insert(node* proot,int val){
    node root = *proot;
    root = (node)malloc(sizeof(Node));
    root->val = val;
    root->next = *proot;
    *proot = root;
}

//这里假设k从0开始
node delete(node root,int k){
    node tmp = NULL;
    if(k == 0){ //删除第一个元素
        tmp = root->next;
        free(root);
        root = tmp;
    }else{  //删除其他元素
        int i;
        tmp = root;
        for(i = 1; i < k && tmp != NULL; i++){
            tmp = tmp->next;
        }
        if(tmp->next){
            node next = tmp->next;
            tmp->next = tmp->next->next;
            free(next);
        }
    }
    return root;
}
