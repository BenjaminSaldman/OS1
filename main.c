#include <stdio.h>
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#define BUFF_SIZE 4096
#define SERVER_PORT 5060
#define SERVER_IP_ADDRESS "127.0.0.1"
int main(int argc, char *argv[]){
    char* EXIT="EXIT";
    char* ECHO = "ECHO";
    char* TCP="TCP PORT";
    char* DIR1="DIR";
    char* CD="CD";
    char* COPY="COPY";
    char* DEL="DELETE";
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
            continue;
        }
        if (strncmp(TCP,command,strlen(TCP))==0)
        {
            int sock = socket(AF_INET, SOCK_STREAM, 0);
        }
        //This part was taken from: https://stackoverflow.com/questions/3554120/open-directory-using-c
        if (strncmp(DIR1,command,strlen(DIR1))==0)
        {
            struct dirent *pDirent;
            
            DIR *pDir=opendir(cwd);
            if (pDir == NULL) {
            printf ("Cannot open directory '%s'\n", cwd);
         }   
        while ((pDirent = readdir(pDir)) != NULL) {
            printf ("[%s]\n", pDirent->d_name);
        }
         closedir (pDir);
         continue;
        }
        if (strncmp(CD,command,strlen(CD))==0)
        {

            char dir[BUFF_SIZE];
            int index=0;
            for(int i=strlen(CD)+1;i<strlen(command);i++)
            {
                dir[index++]=command[i];
            }
            dir[index]=0;
            if(chdir(dir)==-1)
            {
                perror("ERR");
            }
            continue;
        }
        if (strncmp(COPY,command,strlen(COPY))==0)
        {
            char* temp=strtok(command," ");
            char* com=temp;
            temp=strtok(NULL," ");
            char* FILE1=temp;
            temp=strtok(NULL," ");
            char* FILE2=temp;
            FILE *f1=fopen(FILE1,"rb");
            FILE *f2=fopen(FILE2,"wb");
            if(f1==NULL || f2==NULL)
            {
                perror("ERR");

            }
            else{
                char content[BUFF_SIZE];
                while(fread(content,BUFF_SIZE,1,f1)!=EOF)
                {
                    fwrite(content,BUFF_SIZE,1,f2);
                }
                fclose(f1);
                fclose(f2);
            }
            continue;
        }
        if (strncmp(DEL,command,strlen(DEL))==0)
        {
            char* temp=strtok(command," ");
            char* com=temp;
            temp=strtok(NULL," ");
            char* filename=temp;
            if(unlink(filename)==-1)
            {
                perror("ERR");
            }
            continue;
        }
        if (strncmp(DEL,command,strlen(DEL))==0)
        {
            char* temp=strtok(command," ");
            char* com=temp;
            temp=strtok(NULL," ");
            char* filename=temp;
            if(unlink(filename)==-1)
            {
                perror("ERR");
            }
            continue;
        }
        // else{
        //     if(system(command)==-1)
        //     {
        //         perror("ERR");
        //     }
        // }
        else{
            if(!fork())
            {
                char *argList[BUFF_SIZE];
                char* temp=strtok(command," ");
                char* com=temp;
                int index=0;
                while(temp!=NULL)
                {
                    argList[index++]=temp;
                    temp=strtok(NULL," ");
                }
                if(execvp(com,argList)==-1)
                {
                    perror("ERR");
                    exit(1);
                }
            }
            else{
                int status;
                wait(&status);
            }

        }
            
    }
    printf("BYE BYE\n");
}