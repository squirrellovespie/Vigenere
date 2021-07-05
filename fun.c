#include<stdio.h>
#include<string.h>
/*read(f,inp)
1. Opens input.txt in read mode
2. Traverses through the text until EOF is reached and assigns each character to inp
3. Adds a '\0' to the end of inp
4. Closes the file
*/
void read(FILE *f,char *input){
    char ch;int i;
    f=fopen("input.txt","r");
    for(i=0;(ch=getc(f))!=EOF;i++) input[i]=ch;
    input[i]='\0';
    fclose(f);
}
/*write(f,inp)
1. Opens output.txt in write mode(Rewrites previous text)
2. Prints out to the file
3. Closes the file
*/
void write(FILE *f,char *output){
    f=fopen("output.txt","w");
    fprintf(f,"%s",output);
    fclose(f);
}
/*capncheck(inp/key)
1. Traverses through the input string
2. Returns 0 if any character is a special character(not an alphabet or a space or a newline)
3. Capitalises the small alphabets
4. Returns 1 at the end
*/
int capncheck(char *input){
    for(int i=0;input[i]!='\0';i++){
        if(!(((input[i]>='A'&&input[i]<='Z')||(input[i]>='a'&&input[i]<='z'))||input[i]==' '||input[i]=='\n')) return 0;
        if(input[i]>='a'&&input[i]<='z') input[i]=(char)((int)input[i]-32);
    }
    return 1;
}
/*keypad(inp,key)
1. Adds the key to itself until input text length is reached
2. Adds a '\0' to the end of key
*/
void keypad(char *in,char *k){
    int check=0,klen=strlen(k),inlen=strlen(in),flag=0,icopy=klen;//icopy replicates i unless the input has ' ' or '\n'(only used with input text)
    for(int i=klen;i<inlen;i++){//Start loop from klen and iterate until input length
        if(flag==1){//If '\n' or ' ' was encountered
            i--;//Key index must go back
            inlen--;//Input text length must decrease
            flag=0;//Flag is re-initialized to 0
        }
        if(in[icopy]=='\n'||in[icopy]==' '){//Key padding must not take place if input has '\n' or ' '
            flag=1;//'\n' or ' ' has been encountered
            icopy++;//icopy must increase irrespective
            continue;//Restarts the for loop
        }
        k[i]=k[check];//Store each value of the inputted key
        check+=1;//Increment check to access the next element of the inputted key
        if(check==klen) check=0;//check becomes 0 at the end of the inputted key
        icopy++;//Increments after each iteration(To go through input text)
    }
    k[inlen]='\0';
}
/*encrypt(inp,out,key)
1. Calls keypad() to create final key
2. Traverses through inp and applies encryption formula if the character is an alphabet
3. Otherwise(' ' or '\n') output character is the same as input
4. icopy is used to adjust the absence of ' ' or '\n' in the key
5. '\0' is added to the end of out
*/
void encrypt(char *in,char *out,char *k){
    keypad(in,k);int i,icopy=0;//Padded key is created
    for(i=0;in[i]!='\0';i++){
        if(in[i]!=' '&&in[i]!='\n'){
            out[i]=(char)(((((int)in[i]-65)+((int)k[icopy]-65))%26)+65);//Encryption Formula:E=(P+K)%26
        }
        else{
            out[i]=in[i];
            icopy--;
        }
        icopy++;
    }
    out[i]='\0';
}
/*Similar to encrypt()
If Decryption Formula(D=(E-K)%26) becomes negative, add 26*/
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