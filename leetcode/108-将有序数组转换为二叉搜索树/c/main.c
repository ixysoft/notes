#include<stdio.h>
#include<stdlib.h>

//TreeNode结构体
struct TreeNode {
   int val;
   struct TreeNode *left;
   struct TreeNode *right;
};

//构建树,思想就是二分查找
void buildTree(struct TreeNode** pRoot,int* nums,int left,int right){
    if(pRoot == NULL) return;
    struct TreeNode* root = *pRoot;
    int mid = (left+right)/2;
    if(root == NULL){
        root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        root->val = nums[mid];
        root->left = root->right = NULL;
        *pRoot = root;
        if(left < mid)
            buildTree(&(root->left),nums,left,mid-1);
        if(mid < right)
            buildTree(&(root->right),nums,mid+1,right);
    }
}

//主要函数
struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    if(numsSize == 0) return NULL;
    struct TreeNode* root = NULL;
    buildTree(&root,nums,0,numsSize-1); //这里需要注意参数应该是numsSize-1,而不是numsSize,否则程序会出现数组下标超界.
    return root;
}

//前序遍历,用来看结果的
void preVisit(struct TreeNode* root){
    if(root == NULL) return;
    printf("%d ",root->val);
    preVisit(root->left);
    preVisit(root->right);
}

int main(){
    int nums[] = {1,2,3,4,5,6};
    struct TreeNode* root = sortedArrayToBST(nums,sizeof(nums)/sizeof(nums[0]));
    preVisit(root);
    printf("\n");

    return 0;
}
