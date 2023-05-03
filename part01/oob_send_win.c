#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define BUF_SIZE 30
void ErrorHandling(char *message);

int main(int argv, char* argc)
{
	WSADATA wsaData;
	SOCKET hSocket;
	struct sockaddr_in sendAdr;
	if (argv != 3)
	{
		printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(sendAdr, 0, sizeof(sendAdr));
	sendAdr.sin_family = AF_INET;
	sendAdr.sin_addr.s_addr = inet_addr(argv[1]);
	sendAdr.sin_port = htons(atoi(argv[2]));

	if(connect(hSocket,(stuct sockaddr*)&sendAdr, sizeof(sendAdr))== SOCKET_ERROR)
		ErrorHandling("connect() error");

	write(hSocket, "123", strlen("123"));
	send(hSocket, "4", strlen("4"), MSG_OOB);
	write(hSocket, "567", strlen("567"));
	send(hSocket, "890", strlen("890"), MSG_OOB);


	closesocket(hSocket);
	WSACleanup();
	return 0
}

void ErrorHandling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}