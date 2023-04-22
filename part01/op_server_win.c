#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <winsock2.h>

#define BUF_SIZE 1024
#define OPSZ 4
void ErrorHandling(char *message);
int calculate(int opnum,int opnds[], char operator);
int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	int result, opndCnt, i;
	int recvCnt, recvLen;
	SOCKADDR_IN servAdr, clntAdr;
	socklen_t clntAdrSize;

    if (argc != 2){
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }

	if(WSAStartup(MAKEWORD(2,2), &wsaData) !=0 )
		ErrorHandling("WSAStartup() error!");

    hServSock= socket(PF_INET,SOCK_STREAM,0);
    if (hServSock == -1)
        error_handling("socket() error");

    memset(&hServSock, 0 ,sizeof(hServSock));
    hServSock.sin_family = AF_INET;
    hServSock.sin_addr.s_addr = htonl(INADDR_ANY);
    hServSock.sin_port = htons(atoi(argv[1]));

    if(bind(hServSock, (struct sockaddr*)&servAdr, sizeof(servAdr))==-1)
        error_handling("bind() error");

    if(listen(hServSock, 5)==-1)
        error_handling("listen() error");

    clntAdrSize = sizeof(clntAdr); 

    for (i=0; i<5; i++)
    {
        opndCnt = 0;
        hClntSock = accept(hServSock, (struct sockaddr*)&clntAdr, &clntAdrSize);
        read(hClntSock, &opndCnt, 1);

        recvLen = 0;
        while((opndCnt*OPSZ+1)>recvLen)
        {
            recvCnt = read(hClntSock, &opinfo[recvLen], BUF_SIZE-1);
            recvLen += recvCnt;
        }
        result = calculate(opndCnt, (int*)opinfo, opinfo[recvLen-1]);
        write(hClntSock, (char*)&result, sizeof(result));
        close(hClntSock);
    }
    closesocket(hServSock);
    WSACleanup();
    return 0;
}

int calculate(int opnum, int opnds[], char op)
{
    int result = opnds[0], i;
    switch(op)
    {
        case '+':
            for(i=1; i<opnum; i++) result += opnds[i];
            break;
        case '-':
            for(i=1; i<opnum; i++) result -= opnds[i];
            break;
        case '*':
            for(i=1; i<opnum; i++) result *= opnds[i];
            break;
    }
    return result;
}

void ErrorHandling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
