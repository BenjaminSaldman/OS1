#include <stdio.h>
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUFF_SIZE 4096
#define SERVER_PORT 5060
#define SERVER_IP_ADDRESS "127.0.0.1"
int main(){
    char* EXIT="EXIT";
    char* ECHO = "ECHO";
    char* TCP="TCP PORT";
    while (1==1){
        char cwd[BUFF_SIZE];
        char command[BUFF_SIZE];
        // printf("Enter a command:");
        if(getcwd(cwd,sizeof(cwd))==NULL)
        {
            perror("getcwd() error");
        }
        else
            printf("%s ->",cwd);
        fgets(command,sizeof(command),stdin);
        if (*command && command[strlen(command)-1] == '\n')
            command[strlen(command)-1]=0;
        if(strcmp(EXIT,command)==0)
            break;
        if (strncmp(ECHO,command,strlen(ECHO))==0)
        {
            int i=strlen(ECHO)+1;
            while (command[i]!='\0')
            {
                printf("%c",command[i++]);
            }
            printf("\n");
        }
        if (strncmp(TCP,command,strlen(TCP))==0)
        {
            int sock = socket(AF_INET, SOCK_STREAM, 0);
        }
            
    }
    printf("BYE BYE\n");
}