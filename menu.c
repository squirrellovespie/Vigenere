#include<stdio.h>
#include<stdlib.h>
#include"fun.h"
#include<string.h>
int main(){
    while(1){
        puts("");
        FILE *f;int choice,flag=0;
        char *inp=(char*)malloc(1000*sizeof(char)),*out=(char*)malloc(1000*sizeof(char)),*key=(char*)malloc(1000*sizeof(char));
        printf("VIGENERE CIPHER\n1. Encryption\n2. Decryption\n3. Exit\n\nEnter choice: ");
        scanf("%d",&choice);
        read(f,inp);
        if(choice==1||choice==2){
            printf("Enter key: ");
            scanf("%s",key);
            if(strlen(key)>strlen(inp)){
                printf("The key length cannot be greater than the length of the text. Please try again.");
                continue;
            }
            if(capncheck(inp)&&capncheck(key)){
                f=fopen("input.txt","w");
                fprintf(f,"%s",inp);
                fclose(f);
            }
            else{
                puts("Sorry! The file and key must only contain alphabets. Please try again.");
                continue;
            }
        }
        switch(choice){
            case 1:
                encrypt(inp,out,key);
                write(f,out);
                puts("Encrypted successfully!");
                break;
            case 2:
                decrypt(inp,out,key);
                write(f,out);
                puts("Decrypted successfully!");
                break;
            case 3:
                flag=1;
                break;
            default:
                puts("Invalid choice.");
        }
        free(inp);free(out);free(key);
        inp,out,key=NULL,NULL,NULL;
        if(flag==1) break;
    }
    return 0;
}