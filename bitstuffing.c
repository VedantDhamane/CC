#include<stdio.h>
#include<string.h>
#define S 70

char data1[S];
char data2[S];
char flag[]={'0','1','1','1','1','1','1','0'};

void sender();
void reciver(char data1[]);
void main(){
    sender();
    printf("Data to be sent: %s\n",data1);
    reciver(data1);
    printf("Recived Data: %s\n",data2);
}

void sender(){
    char data[S];
    int count =0, k=0;
    printf("Enter Data:");
    scanf("%s",data);
    for(int j=0; j<8; j++){
        data1[k++] = flag[j];
    }
    for(int i=0; i<strlen(data); i++){
        if(data[i]=='1'){
            count++;
        }else{
            count=0;
        }

        if(count==5){
            data1[k++]=data[i];
            data1[k++]='0';
            count=0;
        }
        else{
            data1[k++]=data[i];
        }
    }
     for(int j=0; j<8; j++){
        data1[k++] = flag[j];
    }
    data1[strlen(data1)]='\0';
}

void reciver(char data1[]){
    int len = strlen(data1)-8;
    int count=0, k=0;
    for(int i=8; i<len; i++){
         if(data1[i]=='1'){
            count++;
        }else{
            count=0;
        }

        if(count==5){
            data2[k++] = data1[i];
            i++;
        }else{
            data2[k++] = data1[i];
        }
    }
}
