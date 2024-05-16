#include<stdio.h>
#include<string.h>
#define S 20

int data1[S];

void sender();
void reciver(int data1[]);

void main(){
    sender();
    reciver(data1);
}

void sender(){
    char data[S];
    printf("Enter Data:");
    scanf("%s",data);
    int i;
    for(i=0; i<strlen(data); i++){
        if(data[i]=='1'){
            data1[i+1] = 1; 
        }else{
            data1[i+1] = 0;
        }
    }
    data1[0]= i;
    printf("Data to be sent:");
    for(int i=0; i<strlen(data)+1; i++){
        printf("%d",data1[i]);
    }
    printf("\n");
}

void reciver(int data1[]){
    int len = data1[0];
    char fdata[S];

    for(int i=0; i<len; i++){
        if(data1[i+1]==1){
            fdata[i] = '1';
        }else{
            fdata[i] = '0';
        }
    }
    fdata[len]= '\0';
    printf("Final recived data: %s\n",fdata);
}