#include "display_user_prompt.h"
#include "colours.h"

void format_directory(char *cwd, char *parent_directory)
{
    // This formats the directory to show only ~ when run from default dir
    if(strlen(cwd)<strlen(parent_directory))
    {
        // if current cwd size is less than size of path where shell was started then whole cwd is printed
        return;
    }
    else
    {
        // if cwd path size > size of path where shell is started ~/path in subdir of where shell was started  
        int i=0;
        while(i<strlen(parent_directory))
        {
            if(cwd[i]!=parent_directory[i])
            {
                return;
            }
            i++;
        }
        cwd[0]='~';
        cwd[1]='/';
        int j=2;
        while(j<strlen(cwd))
        {
            cwd[j]=cwd[i];
            j++;
            i++;
        }
        cwd[j]='\0';
    }
}

char *username;
const int SYSTEM_NAME_SIZE=1024;
char *system_name;
void display_user_prompt_function(char *parent_directory)
{
    // printf("output flag: %d\n", print_bg_output_flag);
    // printf("%s", parent_directory);
    username=getenv("USER");
    // This gets the Username of the user

    system_name=malloc(SYSTEM_NAME_SIZE*sizeof(char));
    gethostname(system_name, SYSTEM_NAME_SIZE);  
    // This gets the hostname of the system  

    char *cwd = getcwd(NULL, 0); 
    // This gets the current working directory

    format_directory(cwd, parent_directory);
    // This formats the directory to show only ~ when run from default dir

    int time_taken=endtime-begin;
    if(time_taken>0)
    {
        begin=0;
        endtime=0;
        printf(GREEN "[%s@%s " RESET "%s" GREEN "]"RESET  " sleep: %ds " GREEN "$ " RESET, username, system_name, cwd, time_taken);
    
    }
    else
    {
        printf(GREEN "[%s@%s " RESET "%s" GREEN "]$ " RESET, username, system_name, cwd);
    }
    
    strcpy(previous_prompt_username, username);
    strcpy(previous_prompt_system_name, system_name);
    strcpy(previous_prompt_cwd, cwd);
    input=(char*)malloc(4096*sizeof(char));
    fgets(input,4096,stdin);

    // This takes the input from the user
    // This takes the input from the user
    int success = execute_multi_commands(input);
    // write_to_file(success);
    
    write_to_file(1,input); // this always writes also invalid commands
}

// int main()
// {
//     char *parent_directory = getcwd(NULL, 0); 

//     display_user_prompt_function(parent_directory);
//     return 0;
// }