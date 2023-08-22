#include "proclore.h"

char * helper_function(int len,char *file_name)
{
    char *string=strtok(file_name," \r\t");
    int Cnt=0;
    while(Cnt<len-1)
    {
        string=strtok(NULL, " \r\t");
        Cnt++;
    }
    return string;
}

#define MAX_BUFFER_SIZE 1024
void pinfo(char *command_bro)
{
    char **Command=separate_by_delimeter(command_bro, " ");
    int number_of_arguments=0;
    while(Command[number_of_arguments]!=NULL)
    {
        number_of_arguments++;
    }
    if(number_of_arguments<3)
    {
        int pid;
        if(Command[1]!=NULL)
        pid=atoi(Command[1]);
        else
        pid=getpid();
        char path_of_file_for_stat[MAX_BUFFER_SIZE];
        char path_of_file_for_statm[MAX_BUFFER_SIZE];
        char for_stat_file[MAX_BUFFER_SIZE];
        char for_statm_file[MAX_BUFFER_SIZE];

        char store[(1<<7)][100];
        int temp_cnt=0;

        sprintf(path_of_file_for_stat,"/proc/%d/stat",pid);
        sprintf(path_of_file_for_statm,"/proc/%d/statm",pid);

        FILE *file_statm=fopen(path_of_file_for_statm,"r");
        FILE *file_stat=fopen(path_of_file_for_stat,"r");
        while(fscanf(file_stat,"%[^ ] ",store[temp_cnt])!=EOF)
        {temp_cnt++;}
        file_stat=fopen(path_of_file_for_stat,"r");
        if(file_stat==NULL)
        {
            printf("Process having pid=%d doesn't exist\n",pid);
            return;
        }
        fgets(for_stat_file,MAX_BUFFER_SIZE,file_stat);
        fgets(for_statm_file,MAX_BUFFER_SIZE,file_statm);

        printf("pid : %d\n",pid);
        // printf("%d %d\n",for_stat_file[3],for_stat_file[6]);
        if(strcmp(store[4],store[7])==0)
        {
            printf("Process Status : %s+\n",helper_function(3,for_stat_file));
        }
        else
        {
            printf("Process Status : %s\n",helper_function(3,for_stat_file));
        }
        printf("Process Group : %d\n", (int)getpgrp());
        
        printf("Virtual Memory : %s\n",helper_function(1,for_statm_file));

        char for_execution[MAX_BUFFER_SIZE];
        char for_execution_path[MAX_BUFFER_SIZE];
        sprintf(for_execution,"/proc/%d/exe",pid);
        fflush(stdout);
        if(readlink(for_execution,for_execution_path,MAX_BUFFER_SIZE)!=-1)
        {
            strcat(for_execution_path,"\0");
            char *Home_subdirectory=strstr(for_execution_path,shell_open_path);
            if(Home_subdirectory!=NULL)
            {
                strcat(Home_subdirectory,"\0");
                Home_subdirectory+=strlen(shell_open_path);
                printf("executable path : ~%s",Home_subdirectory);
            }
            else
                printf("executable path : ~%s",for_execution_path);
            printf("\n");
        }
        else
            printf("No executable found\n");
    }
    else
    {
        perror("More Arguments given than possible");
        return;
    }
}   