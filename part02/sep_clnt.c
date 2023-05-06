#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

int main(int argc, char* argv)
{
	int sock;
	FILE *readfp;
	FILE *writefp;

	struct sockaddr_in serv_addr;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	readfp = fdopen(sock, "r");
	writefp = fdopen(sock, "w");
	while(1)
	{	
		if(fgets(buf, sizeof(buf), readfp) == NULL)
			break;
		fputs(buf, stdout);
		fflush(stdout);
	}

	fputs("FROM CLIENT: Thank you! \n", writefp);
	fflush(writefp);

	fclose(writefp);
	fclose(readfp);
	return 0;
}