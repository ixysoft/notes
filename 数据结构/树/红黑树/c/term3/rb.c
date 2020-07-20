#include "rb.h"

nodep node(int key){
    nodep ret = (nodep)ralloc(sizeof(Node));

    ret->color = RED;   //设置默认颜色
    ret->parent = nullnode(NULL);
    ret->left = nullnode(ret);
    ret->right = nullnode(ret);
    ret->key = (int*)ralloc(sizeof(int));
    *(ret->key) = key;

    return ret;
}

nodep nullnode(nodep p){
    nodep ret = (nodep)ralloc(sizeof(Node));

    ret->color = BLACK;   //设置默认颜色
    ret->parent = p;
    ret->left = ret->right = NULL;
    ret->key = NULL;

    return ret;
}

treep tree(){
    treep t = (treep)ralloc(sizeof(Tree));
    t->root = NULL;
    t->size = 0;

    return t;
}

Boolean insertNode(treep t,int key){
    return _insertNode(t,&(t->root),key);
}

//以某个节点为根节点插入
Boolean _insertNode(treep t,nodep* rootp,int key){
    if(rootp == NULL) return FALSE;
    nodep root = *rootp;
    if(root == NULL){   //根节点
        t->root = node(key);
    }else{
        while(root->key != NULL){
            if(Key(root) == key) return FALSE;  //已经存在元素,返回插入失败
            
            if(Key(root) > key){
                root = root->left;
            }else{
                root = root->right;
            }
        }
        nodep leaf = root;
        root = node(key);
        transplant(t,leaf,root); //替换nill节点
        if(isRoot(root)) t->root = root;    //切换根节点
        free(leaf);  // 删除叶子节点
        

        //当前处于nil节点
        while(isRed(root) && isRed(parent(root))){     //父节点为红色
            nodep pa = parent(root);    //父节点
            nodep ga = grandpa(root);   //祖父节点
            nodep un = uncle(root);     //叔父节点
            if(isNull(ga) || isLeaf(ga)){   //祖父节点不存在
                break;
            }

            if(isRed(un)){  //叔父节点为红节点
                pa->color = un->color = BLACK;  //父节点与叔父节点颜色反转
                ga->color = RED;    //祖父节点的颜色反转
                root = ga;  //此时祖父节点视作新加入的节点
            }else{
                //叔父节点为黑色,父节点红色,祖父节点黑色
                //我们需要将当前节点与父节点两个双红节点其中一个变黑
                ga->color = RED;    //祖父节点变红色
                if(key_cmp(pa,ga) != key_cmp(root,pa)){ //非一个方向
                    if(isRight(root)){   //pa > root,LR结构
                        pa = rotate_left(t,pa);    //左旋,转成LL
                        root = pa->left;
                    }else{
                        pa = rotate_right(t,pa);   //右旋,转成RR
                        root = pa->right;
                    }
                }
                pa->color = BLACK;  //将中间元素转为黑色

                if(isRight(pa)){   //pa > root
                    root = rotate_left(t,ga);    //左旋
                }else{
                    root = rotate_right(t,ga);    //右旋
                }
            }
        }
    }
    t->size++;
    t->root->color = BLACK; //根节点为黑色
    return TRUE;
}

Boolean transplant(treep t,nodep dest,nodep src){
    if(isNull(dest) || isNull(src)) return FALSE;
    if(isLeaf(src->parent)){    //一个新节点
        free(src->parent);
    }
    src->parent = dest->parent;
    if(!isRoot(dest)){
        if(isRight(dest)){  //右孩子
            dest->parent->right = src;
        }else{
            dest->parent->left = src;
        }
    }

    if(isRoot(src)){
        t->root = src;
        if(isLeaf(src)){    //根节点不允许为NIL
            free(t->root->parent);
            t->root = NULL;
        }
    }
    return TRUE;
}

nodep rotate_left(treep t,nodep nd){
    if(isNull(t) || isNull(nd) || isNull(nd->right)) return NULL;
    nodep right = nd->right;
    nd->right = right->left;
    if(nd->right){
        nd->right->parent = nd;
    }
    right->parent = nd->parent;
    if(!isRoot(nd)){    //nd为根节点
        if(isLeft(nd)){ //左侧
            right->parent->left = right;
        }else{
            right->parent->right = right;
        }
    }
    nd->parent = right;
    right->left = nd;

    if(isRoot(right)){
        t->root = right;
        if(isLeaf(right)){    //根节点不允许为NIL
            free(t->root);
            t->root = NULL;
        }
    }

    return right;
}

nodep rotate_right(treep t,nodep nd){
    if(isNull(t) || isNull(nd) || isNull(nd->left)) return NULL;
    nodep left = nd->left;
    nd->left = left->right;
    if(nd->left){
        nd->left->parent = nd;
    }
    left->parent = nd->parent;
    if(!isRoot(nd)){    //nd为根节点
        if(isLeft(nd)){ //左侧
            left->parent->left = left;
        }else{
            left->parent->right = left;
        }
    }
    nd->parent = left;
    left->right = nd;

    if(isRoot(left)){
        t->root = left;
        if(isLeaf(left)){    //根节点不允许为NIL
            free(t->root);
            t->root = NULL;
        }
    }
    return left;
}

void visit(treep t){
    return _visit(t->root);
}

//层序遍历
void _visit(nodep root){
    nodep stack[1024];
    int len = 0;
    stack[len++] = root;
    stack[len++] = NULL;
    nodep tmp = NULL;
    int i;
    for(i = 0; i < len; i++){
        tmp = stack[i];
        if(tmp == NULL){
            if(len > 0 && stack[len-1] != NULL)
                stack[len++] = NULL;
            printf("\n");
        }else{
            printf("%d[%s]{%d} ",Key(tmp),isRed(tmp) ? "R" : "B",isRoot(tmp) ? -1 : Key(tmp->parent));
            // printf("%p\n",tmp);
            if(!isLeaf(tmp->left))
                stack[len++ % 1024] = tmp->left;

            if(!isLeaf(tmp->right))
                stack[len++ % 1024] = tmp->right;
        }
    }
}

nodep search(treep t,int key){
    if(t == NULL || t->root == NULL) return NULL;
    nodep root = t->root;
    while(!isLeaf(root)){
        if(Key(root) == key){
            return root;
        }else if(Key(root) > key){
            root = root->left;
        }else{
            root = root->right;
        }
    }
    return NULL;
}

Boolean deleteNode(treep t,int key){
    nodep root = search(t,key);
    nodep current = NULL;
    if(root == NULL) return FALSE;  //结果不存在
    t->size--;
    // printf("删除:%d\n",key);
    // printf("%p\n",sibling(root)->left);
    if(isLeaf(root->left)){ //左节点不存在
        free(root->left);   //释放nil节点
        current = root->right;
        transplant(t,root,root->right);   // 将root->right移动到root
    }else if(isLeaf(root->right)){
        free(root->right);  //释放nil节点
        current = root->left;
        transplant(t,root,root->left);  // 将root->left移动到root
    }else{  //左右节点都存在
        nodep min = minimum(root->right);   //root右子树上的最小值
        int* tmp = root->key;
        root->key = min->key;
        min->key = tmp;
        current = min->right;
        free(root->left);   //释放nil节点
        transplant(t,min,min->right);   // 转移
        root = min;
    }

    Color del_color = root->color;
    free(root); //释放root

    if(del_color == BLACK){
        deleteFix(t,current);
    }
    if(!isLeaf(current))
        current->color = BLACK;

    return TRUE;
}

//删除
Boolean deleteFix(treep t,nodep current){
    while(!isRoot(current) && isBlack(current)){
        nodep pa = parent(current);
        nodep si = sibling(current);
        if(si == NULL) break; 
        // case1,si为红色
        if(isRed(si)){
            si->color = BLACK;  //si设定为黑色
            if(isRight(si)){
                rotate_left(t,pa);
                si->left->color = RED; //si的左孩子设定为红色
            }else{
                rotate_right(t,pa);
                si->right->color = RED; //si的右孩子设定为红色
            }
        }else{
            // case2,un为黑，其孩子也是黑色
            if(isBlack(si->left) && isBlack(si->right)){
                current = parent(current);
                si->color = RED;    //叔父节点设置为红色
            }else if(isBlack(si->right)){   //case3，左孩子为红色，右孩子为黑色
                current->color = BLACK;
                pa->color = RED;
                if(isLeft(current)){
                    rotate_right(t,pa);
                }else{
                    rotate_left(t,pa);
                }
            }else{  //右节点为红色
                si->color = pa->color;  //叔父节点颜色设置为父节点颜色
                si->right->color = BLACK;  //右节点设为黑色
                pa->color = BLACK;
                if(isRight(si)){
                    rotate_left(t,pa);
                }else{
                    rotate_right(t,pa);
                }

                break;  //case4调整后必然平衡
            }
        }
    }
    current->color = BLACK;

    return TRUE;
}

nodep minimum(nodep root){
    nodep m = NULL;
    while(!isLeaf(root)){
        m = root;
        root = root->left;
    }
    return m;
}