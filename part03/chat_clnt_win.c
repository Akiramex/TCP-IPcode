#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <process.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

unsigned WINAPI SendMsg(void * arg);
unsigned WINAPI RecvMsg(void * arg);
void ErrorHandling(char *msg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

int main(int argc, char *argv[])
{
    WSADATA wsaData;
    SOCKET hSock;
    struct sockaddr_in servAdr;
    HANDLE hSndThread, hRcvThread;
    if(argc != 4) {
        printf("Usage : %s <IP> <port> <name>\n", argv[0]);
        exit(1);
    }

    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error");

    sprintf(name,"[%s]",argv[3]);
    hSock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&servAdr, 0, sizeof(servAdr));
    servAdr.sin_family = AF_INET;
    servAdr.sin_addr.s_addr = inet_addr(argv[1]);
    servAdr.sin_port = htons(atoi(argv[2]));

    if (connect(hSock, (struct sockaddr*)&servAdr, sizeof(servAdr)) == -1)
        error_handling("connect() error");

    hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSock, 0 ,NULL);
    hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSock, 0 ,NULL);
    WaitForSingleObjects(hSndthread, INFINITE);
    WaitForSingleObjects(hRcvthread, INFINITE);
    closesocket(hSock);
    WSACleanup();
    return 0;
}

unsigned WINAPI SendMsg(void *arg)
{
    SOCKET hSock = *((SOCKET*)arg);
    char nameMsg[NAME_SIZE + BUF_SIZE];
    while (1)
    {
        fgets(msg, BUF_SIZE, stdin);
        if(!strcmp(msg, "q\n")|| !strcmp(msg, "Q\n"))
        {
            closesocket(hSock);
            exit(0);
        }
        sprintf(nameMsg, "%s %s", name, msg);
        write(hSock, nameMsg, strlen(nameMsg), 0);
    }
    return 0;
}

unsigned WINAPI RecvMsg(void *arg)
{
    SOCKET hSock = *((SOCKET*)arg);
    char name_msg[NAME_SIZE + BUF_SIZE];
    int str_len;
    while(1)
    {
        strLen = read(hSock,nameMsg,NAME_SIZE+BUF_SIZE-1, 0);
        if(str_len == -1)
            return (void*)-1;
        nameMsg[strLen] = 0;
        fputs(nameMsg, stdout);
    }
    return 0;
}

void ErrorHandling(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}