/* ************************************************************************
> File Name:     inet_aton.c
> Author:        Akira
> Created Time:  Thu 20 Apr 2023 10:07:02 AM CST
> Description:   
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
void errpr_handling(char *message);

int main(int argc, char *argv[])
{
    char *addr = "127.232.124.79";
    struct sockaddr_in addr_inet;

    if(!inet_aton(addr, &addr_inet.sin_addr))
        errpr_handling("Conversion error");
    else
        printf("Network order integer addr: %#x \n", addr_inet.sin_addr.s_addr);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
