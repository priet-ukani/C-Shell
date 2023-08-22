#include "main.h"
// extern char **past_events;
// char* file_open_path;
// char *input;

char** past_events;
char* file_open_path;
char* input;

char* shell_open_path;
int main()
{
    char *parent_directory = getcwd(NULL, 0); 
    shell_open_path=(char*)malloc(1024*(sizeof(char)));
    strcpy(shell_open_path, parent_directory);
    // This gets the current working directory
    past_events=(char**)malloc(sizeof(char*)*17);
    char *line = NULL;
    for (int i = 0; i < 17; i++)
    {
        past_events[i]=(char*)malloc(sizeof(char)*1024);
    }

    while (1)
    {
        // // read all the commands from the pastevents;
        FILE* fp;
        file_open_path=(char*)malloc(sizeof(char)*1024);
        strcpy(file_open_path, parent_directory);
        strcat(file_open_path, "/pastevents.txt");
        // printf("%s", file_open_path);
        fp = fopen(file_open_path, "r");
        // fp = fopen("/home/prietukani/Desktop/Codes/Coding/Sem 3/OSN/C Shell/C-Shell/src/pastevents.txt", "r");
        if (fp == NULL)
        {
            perror("Error");
            exit(0);
        }
        // read all 15 commands from pastevents.txt 
        for (int i = 0; i < 15; i++)
        {
            fgets(past_events[i], 1024, fp);
            // puts(past_events[i]);
        }
        fclose(fp);
        display_user_prompt_function(parent_directory);

        input=(char*)malloc(4096*sizeof(char));
        fgets(input,4096,stdin);

        // This takes the input from the user
        int success = execute_multi_commands(input);
        // write_to_file(success);
        write_to_file(1,input); // this always writes also invalid commands
    }
    return 0;
}

