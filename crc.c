#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N strlen(crc_key)

void sender();
void receiver();
void error();
void crc(char data[]);

char data[50]; 
char crc_key[20]; 
int data_len;     
int i, j;
char chk_val[50];
int ch;

void crc(char data[])
{
    char remainder[N + 1];
    for (i = 0; i < N; i++)
        chk_val[i] = data[i];

    i = N;

    do
    {

        if (chk_val[0] == '1')
        {
        
            for (j = 1; j < N; j++)

                chk_val[j] = ((chk_val[j] == crc_key[j]) ? '0' : '1');
        }

        
        for (j = 0; j < N - 1; j++)
        {
            chk_val[j] = chk_val[j + 1];
        }
        chk_val[j] = data[i++];
        printf("Remainder%d: %s\n", i - N, chk_val);
    } while (i <= data_len + N - 1);
}

void sender()
{
    printf("\nEnter data : ");
    scanf("%s", data);
    data_len = strlen(data);
    printf("\nEnter crc key: ");
    scanf("%s", crc_key);
    for (i = data_len; i < (data_len + N - 1); i++)
    {

        data[i] = '0';
    }
    data[data_len + N - 1] = '\0';
    printf("\nAppended data with N-1 0s: %s", data);
    printf("\n\n");
    crc(data);
    printf("\n\nCRC or Check value is : %s", chk_val);
    for (i = data_len; i < data_len + N - 1; i++)
    {
        data[i] = chk_val[i - data_len];
    }
    printf("\nFinal data to be sent : %s", data);
    printf("\n");
}

void receiver()
{
    char DataReceived[50];
    strcpy(DataReceived, data);
    printf("\nChecking data\n");
    crc(DataReceived);
    for (int k = 0; k < strlen(crc_key); k++)
    {
        if (chk_val[k] == '1')
        {
            printf("\nError in the data.\n");
            return;
        }
    }
    printf("\nData received Successfully: %s", DataReceived);
}

void error()
{
    int ErrorPosn;
    printf("\nEnter position to add error : ");
    scanf("%d", &ErrorPosn);
    data[ErrorPosn] = (data[ErrorPosn] == '1') ? '0' : '1';
    
}

int main()
{
    do
    {
        printf("\n\n1) Execute Without error\n2) Execute With error\n3) Exit");
        printf("\nEnter choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
        {
            sender();
            receiver();
            break;
        }
        case 2:
        {
            sender();
            error();
            receiver();
            break;
        }
        case 3:
        {
            exit(0);
            break;
        }
        default:
        {
            break;
        }
        }
    } while (ch < 4 && ch > 0);
    return 0;
}