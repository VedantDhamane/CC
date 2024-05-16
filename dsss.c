#include <stdio.h>
#include <string.h>
#define S 110

char *org_signl(char data[], char data1[]);
char *XNOR(char data1[], char result[]);
char *org_dataa(char org_result[], char org_data[]);

int main(){
    char data[10];
    char data1[S] = {'\0'};
    char result[S] = {'\0'};
    char org_result[S] = {'\0'};
    char org_data[10] = {'\0'};
    printf("Enter Data: ");
    scanf("%s",data);
    org_signl(data,data1);
    printf("%s\n",data1);
    XNOR(data1,result);
    printf("Result: %s\n",result);
    XNOR(result,org_result);
    printf("Org_result: %s\n",org_result);
    org_dataa(org_result,org_data);
    printf("Org_Data: %s\n",org_data);
    return 0;
}

char *org_signl(char data[], char data1[]){
    int k=0;
    for(int i=0; i<strlen(data); i++){
        if(data[i]=='1'){
            for(int j=0; j<11; j++){
                data1[k++] = '1';
            }
        }else{
            for(int j=0; j<11; j++){
                data1[k++] = '0';
            }
        }
    }
    data1[strlen(data)*11]='\0';
    return data1;
}

char *XNOR(char data1[], char result[]){
    char pattern[] = {'1','0','1','1','0','1','1','1','0','0','0'};
    int l = strlen(data1);
    int k=0;
    for(int i = 0; i < l; i += 11){
        for(int j = 0; j < 11; j++){
            if(data1[i+j] == pattern[j]){
                result[k++]='1';
            }else{
                result[k++]='0';
            }
        }
    }
    result[k] = '\0';
    return result;
}

char *org_dataa(char org_result[], char org_data[]){
    int flag = -1, j = 0;
    int l = strlen(org_result);

    for(int i = 0; i < l; i += 11){
        if(org_result[i] == '1'){
            flag = 1;
        }else if(org_result[i] == '0'){
            flag = 0;
        }else{
            flag = -1;
            printf("Something Wrong\n");
            break;
        }
        org_data[j++] = flag + '0';
    }

    org_data[j]='\0';
    return org_data;
}