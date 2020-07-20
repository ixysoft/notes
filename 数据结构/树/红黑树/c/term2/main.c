#include<stdio.h>
#include "rb.h"

int main(){
    nodep root = NULL;
    // insert(&root,3);
    // insert(&root,5);
    // insert(&root,7);
    // insert(&root,9);
    // insert(&root,11);
    // insert(&root,13);
    // insert(&root,15);
    // for(int i = 0; i < 10; i++)
    //     insert(&root,i*2+1);
    insert(&root,1);
    insert(&root,3);
    insert(&root,4);
    insert(&root,0);

    visit(root);
    return 0;
}

