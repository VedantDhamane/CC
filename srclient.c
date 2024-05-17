#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8000

int main()
{
    struct sockaddr_in serveraddress;

    int clientsocket;
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientsocket<0)
    {
        printf("socket creation failed\n");
        return -1;
    }

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_addr.s_addr = INADDR_ANY;

    int connection_status;
    connection_status = connect(clientsocket, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
    if(connection_status < 0)
    {
        printf("connection failed\n");
        return -1;
    }
    else
        printf("connection established\n");

    int n, f;
    printf("Enter the size: ");
    scanf("%d", &n);

    printf("Enter the frame size: ");
    scanf("%d", &f);

    send(clientsocket, &n, sizeof(n), 0);
    send(clientsocket, &f, sizeof(f), 0);

    int ack, read1;

    for(int j = 0; j < f; j++)
    {
        printf("\nsending the bit: %d", j);
        send(clientsocket, &j, sizeof(j), 0);
        sleep(2);
    }

    for(int i = f; i < n; i++)
    {
        sleep(2);
        send(clientsocket, &i, sizeof(i), 0);

        printf("\nsending bit %d...", i);
        sleep(2);

        recv(clientsocket, &ack, sizeof(ack), 0);

        printf("\nack bit: %d\n\n", ack);
    }

    for(int j = n-f; j < n; j++)
    {
        recv(clientsocket, &ack, sizeof(ack), 0);
        printf("\nack bit: %d\n\n", ack);
    }


    close(clientsocket);

    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>

// #define PORT 8000

// int main()
// {
//     char servermessage[256];
//     struct sockaddr_in serveraddress, clientaddress;
//     int client_address_len = sizeof(clientaddress);

//     int serversocket;
//     serversocket = socket(AF_INET, SOCK_STREAM, 0); 
//     if(serversocket < 0)
//     {
//         printf("socket failed");
//         return -1;
//     }

//     serveraddress.sin_family = AF_INET;
//     serveraddress.sin_port = htons(PORT);
//     serveraddress.sin_addr.s_addr = INADDR_ANY;

//     int bindstatus;
//     bindstatus = bind(serversocket, (const struct sockaddr*)&serveraddress, sizeof(serveraddress));
//     if (bindstatus < 0)
//     {
//         printf("binding failed\n");
//         return -1;
//     }
//     else
//     {
//         printf("binding is successful\n");
//     }


//     listen(serversocket, 3);
//     printf("Waiting for client connection...\n");

//     int clientsocket;
//     clientsocket = accept(serversocket, (struct sockaddr *)&clientaddress, (socklen_t *)&client_address_len);
//     if(clientsocket<0)
//     {
//         printf("connection is rejected by server\n");
//         return -1;
//     } 
//     else
//         printf("connection is accepted\n");

//     int n, f, j;
//     recv(clientsocket, &n, sizeof(n), 0);
//     recv(clientsocket, &f, sizeof(f), 0);
    
//     for(int k = 0; k < f; k++)
//     {
//         recv(clientsocket, &j, sizeof(j), 0);
//         printf("\nreceived bit: %d", j);
//         int ack = k+1;
//     }

//     int s = 0;
//     for(int i = f; i < n; i++)
//     {
//         recv(clientsocket, &j, sizeof(j), 0);
//         printf("\nreceived bit: %d...", j);
//         printf("\nsending ack for: %d\n\n", s);

//         send(clientsocket, &s, sizeof(i+1), 0);
//         s++;
//     }

//     for(int j = n-f; j<n; j++)
//     {
//         send(clientsocket, &s, sizeof(s), 0);
//         printf("\nack bit: %d\n\n", s);
//         s++;
//     }

//     printf("\nfinished\n");


//     close(serversocket);

//     return 0;
// }
