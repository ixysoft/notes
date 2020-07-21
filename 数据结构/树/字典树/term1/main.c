#include"trie.h"

#define str(n) (n),(strlen(n)+1)

void visit(trienodep root){
    if(root == NULL){
        printf("\n");
        return;
    }
    printf("%c{%d}[%p] ",root->key,root->key,root->data);
    visit(root->next);
    visit(root->next_level);
}

int main(){
    triep tree = trie();
    insertNode(tree,"apple",str("苹果"));
    insertNode(tree,"app",str("应用"));
    insertNode(tree,"boy",str("男孩"));
    insertNode(tree,"cat",str("猫"));
    insertNode(tree,"唐揚げ",str("炸鸡"));
    insertNode(tree,"ねこ",str("猫"));
    insertNode(tree,"いぬ",str("狗"));
    insertNode(tree,"お風呂",str("澡堂"));
    insertNode(tree,"風邪",str("感冒"));
    insertNode(tree,"熱",str("发烧"));
    insertNode(tree,"산채하다",str("散步"));
    insertNode(tree,"미국",str("美国"));
    insertNode(tree,"한국",str("韓国"));
    insertNode(tree,"풀",str("草"));
    insertNode(tree,"저는 중국사람입니다",str("我是中国人"));
    insertNode(tree,"アメリカ",str("美国"));

    visit(tree->root);
    // deleteNode(tree,"アメリカ");

    searchresultp result = search(tree,"アメリカ");

    string data = (string)result->data;
    printf("%s\n",(result->status == TRUE && data != NULL ? data : "查找失败"));

    deleteNode(tree,"apple");
    visit(tree->root);
    printf("========硬删除=======\n");
    hardDeleteNode(tree,"apple");
    visit(tree->root);

    return 0;
}