#include<stdio.h>
int steps[1008611];

void path(int n,int step){
    int i;
    if(n == 0){
        for(i = step-1; i >= 0; i--){
            if(i == step-1) printf("%d",steps[i]);
            else printf(",%d",steps[i]);
        }
        puts("");
        return;
    }

   for(i = 1; i <= 2 && i <= n; i++){
        steps[step] = i;
        path(n - i,step+1);
    }
}

//根据给定的步长求路径
void path2(int step_lengths[],int step_size,int n,int step){
    int i;
    if(n == 0){
        for(i = step-1; i >= 0; i--){
            if(i == step-1) printf("%d",steps[i]);
            else printf(",%d",steps[i]);
        }
        puts("");
        return;
    }

    for(i = 0; i < step_size && step_lengths[i] <= n; i++){
        steps[step] = step_lengths[i];
        path2(step_lengths,step_size,n - steps[step],step+1);
    }
}


int main(){
    path(4,0);

    int step_lengths[] = {2,3,5,10,20,50,100};
    int step_size = sizeof(step_lengths) / sizeof(step_lengths[0]);

    printf("case 2:\n");
    path2(step_lengths,step_size,10,0);
    return 0;
}
