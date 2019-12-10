#include<stdio.h>

const unsigned char keys[1024] = "2222222222222222222222222222222222222";

unsigned char hex(unsigned char * s){
    int i = 0;
    unsigned char res = 0;
    unsigned char tmp = 0;
    for(i = 0; i < 2; i++){
        if(s[i] <= '9') tmp = s[i] - '0';
        else tmp = s[i] - 'a' + 10;
 //       printf("[%c]",s[i]);
        res = (res << 4) | tmp;
    }
    return res;
}

void encrypt(char str[],char out[]){
    int i;
    for(i = 0; keys[i] != '\0'; i++){
        unsigned char tmp = hex(str+i*2);
        out[i] = tmp ^ keys[i];
        //printf("%c", keys[i] ^ tmp);
        //printf("%d,%d\n",tmp,tmp^str[i]);
    }
    out[i] = '\0';
}

int main(){
    unsigned char dec[1024] = "7a575e5e5d12455d405e561254405d5f1276535b5e4b12715d565b5c551262405d505e575f";
    unsigned char out[1024];
    encrypt(dec,out);
    puts(out);
    return 0;
}
