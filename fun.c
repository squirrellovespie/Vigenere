#include<stdio.h>
#include<string.h>
void read(FILE *f,char *input){
    char ch;int i;
    f=fopen("input.txt","r");
    for(i=0;(ch=getc(f))!=EOF;i++) input[i]=ch;
    input[i]='\0';
    fclose(f);
}
void write(FILE *f,char *output){
    f=fopen("output.txt","w");
    fprintf(f,"%s",output);
    fclose(f);
}
int capncheck(char *input){
    for(int i=0;input[i]!='\0';i++){
        if(!(((input[i]>='A'&&input[i]<='Z')||(input[i]>='a'&&input[i]<='z'))||input[i]==' '||input[i]=='\n')) return 0;
        if(input[i]>='a'&&input[i]<='z') input[i]=(char)((int)input[i]-32);
    }
    return 1;
}
void keypad(char *in,char *k){
    int check=0,klen=strlen(k),inlen=strlen(in),flag=0,icopy=klen;
    for(int i=klen;i<inlen;i++){//Start loop from kcount and iterate until the length of plain text
        if(flag==1){
            i--;
            inlen--;
            flag=0;
        }
        if(in[icopy]=='\n'||in[icopy]==' '){
            flag=1;
            icopy++;
            continue;
        }
        k[i]=k[check];//Store each value of the inputted key
        check+=1;//Increment check to access the next element of the inputted key
        if(check==klen) check=0;//check becomes 0 at the end of the inputted key
        icopy++;
    }
    k[inlen]='\0';
}
void encrypt(char *in,char *out,char *k){
    keypad(in,k);int i,icopy=0;
    for(i=0;in[i]!='\0';i++){
        if(in[i]!=' '&&in[i]!='\n'){
            out[i]=(char)(((((int)in[i]-65)+((int)k[icopy]-65))%26)+65);
        }
        else{
            out[i]=in[i];
            icopy--;
        }
        icopy++;
    }
    out[i]='\0';
}
void decrypt(char *in,char *out,char *k){
    keypad(in,k);int i,icopy=0;
    for(i=0;in[i]!='\0';i++){
        if(in[i]!=' '&&in[i]!='\n'){
            int pt=(((int)in[i]-65)-((int)k[icopy]-65))%26;
            if(pt<0) pt=pt+26;
            out[i]=(char)(pt+65);
        }
        else{
            out[i]=in[i];
            icopy--;
        }
        icopy++;
    }
    out[i]='\0';
}