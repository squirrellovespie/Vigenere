#include<stdio.h>
#include<stdlib.h>
#include"fun.h"
#include<string.h>
/*VARIABLES:
1. f = file pointer
2. inp = points to the text from input.txt
3. out = points to the text to be written in output.txt
4. key = points to the key received from stdin
5. choice = stores choice of Encryption/Decryption/Exit
6. flag = Used to exit the while loop
*/
int main(){
    while(1){
        puts("");
        FILE *f;int choice,flag=0;
        char *inp=(char*)malloc(1000*sizeof(char)),*out=(char*)malloc(1000*sizeof(char)),*key=(char*)malloc(1000*sizeof(char));
        printf("VIGENERE CIPHER\n1. Encryption\n2. Decryption\n3. Exit\n\nEnter choice: ");
        scanf("%d",&choice);
        read(f,inp);
        if(choice==1||choice==2){//Only if Exit is not chosen
            printf("Enter key: ");
            scanf("%s",key);
            if(strlen(key)>strlen(inp)){//Key length must be <= Text length
                puts("The key length cannot be greater than the length of the text. Please try again.");
                continue;//Restarts the while loop
            }
            if(capncheck(inp)&&capncheck(key)){//Capitalising inp and key
                f=fopen("input.txt","w");//Rewriting input text after capitalisation
                fprintf(f,"%s",inp);
                fclose(f);
            }
            else{//capncheck() returns 0 if any other symbol is present
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
                flag=1;//To exit the while loop
                break;
            default:
                puts("Invalid choice.");
        }
        free(inp);free(out);free(key);//Freeing memory
        inp,out,key=NULL,NULL,NULL;//Assigning dangling pointers to NULL
        if(flag==1) break;//Exiting while loop if choice is 3
    }
    return 0;
}