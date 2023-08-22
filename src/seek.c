#include "seek.h"

int atleast_one_found=0;
char *path_of_first_found;
int first_dir_found=0;
int first_file_found=0;

void searchFile(char *path, char *name, bool searchFiles, bool searchDirs) {
    
    if(strcmp(path, "~" )==0) path=shell_open_path;
    
    char*cur_dir=(char*)malloc(sizeof(char)*1024);
    getcwd(cur_dir, 1024);
    int response= chdir(path);
    if(response==-1)
    {
        printf("No such directory exists!\n");
        return;
    }
    char *path2=(char*)malloc(sizeof(char)*1024);
    getcwd(path2, 1024);
    chdir(cur_dir);
    // printf("%s\n", path2);
    strcpy(path,path2);
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            // Skip "." and ".." directories
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            bool found_dir=true;
            int len = strlen(entry->d_name);
            int len2 = strlen(name);
            int lens;
            if(len<len2) lens=len;
            else lens=len2;

            for (int i = 0; i < lens; i++)
            {
                if(entry->d_name[i]!=name[i]) found_dir=false;
            }
            

            if (searchDirs && found_dir) {
                printf("Found directory: %s/%s\n", path, entry->d_name);
                sprintf(path_of_first_found, "%s/%s", path, entry->d_name);
                atleast_one_found++;
                first_dir_found=1;
            }

            // Construct the full path of the subdirectory
            char subPath[1024];
            snprintf(subPath, sizeof(subPath), "%s/%s", path, entry->d_name);

            // Recursively search in subdirectories
            searchFile(subPath, name, searchFiles, searchDirs);
        } else if (searchFiles) {
            bool found_file = true;

            int len = strlen(entry->d_name);
            int len2 = strlen(name);
            int lens;

            if (len < len2) lens = len;
            else lens = len2;

            for (int i = 0; i < lens; i++) {
                if (entry->d_name[i] != name[i]) {
                    found_file = false;
                    break; // No need to continue checking if one character doesn't match
                }
            }

            if (found_file) {
                atleast_one_found++;
                printf("Found file: %s/%s\n", path, entry->d_name); 
                sprintf(path_of_first_found, "%s/%s", path, entry->d_name);
                first_file_found=1;
            }
        }
    }

    closedir(dir);
}



int seek_seek(char*command)
{
    puts(command);
    char **Command = separate_by_delimeter(command, " " );
    bool flag_d=false;
    bool flag_f=false;
    bool flag_e=false;
    int index_it=0;
    int last_flag_index=0;

    while (Command[index_it]!=NULL)
    {
        // printf("%s, %d\n", Command[index_it], strlen(Command[index_it]));
        if(strcmp(Command[index_it], "-d")==0) {flag_d=true;last_flag_index=index_it;}
        if(strcmp(Command[index_it], "-f")==0) {flag_f=true;last_flag_index=index_it;}
        if(strcmp(Command[index_it], "-e")==0) {flag_e=true;last_flag_index=index_it;}        
        index_it++;
    }
    
    char *filename_to_search_for=(char*) malloc(sizeof(char)*1024);
    strcpy(filename_to_search_for,Command[last_flag_index+1]);
    char *filepath_to_search_for=(char*) malloc(sizeof(char)*1024);
    if(last_flag_index+2<index_it)
    {
        strcpy(filepath_to_search_for, Command[last_flag_index+2]);
    }
    else
    {
        strcpy(filepath_to_search_for, "."); 
        // search in the current directory
    }
    if(flag_d&&flag_f)
    {
        printf("Invalid flags!\n");
        return 0;
    }
    if(!flag_d&&!flag_f)
    {
        flag_d=flag_f=true;
    }

    atleast_one_found=false;
    path_of_first_found=(char*)malloc(sizeof(char)*1024);
    first_dir_found=0;
    first_file_found=0;
    searchFile(filepath_to_search_for, filename_to_search_for, flag_f, flag_d);
    // printf("indexit: %d\n", index_it);
    // printf("Flag_d: %d Flag_f: %d Flag_e: %d \n", flag_d, flag_f, flag_e);
    // printf("%s\n", filename_to_search_for);
    // printf("%s\n", filepath_to_search_for);

    if(!atleast_one_found)
    {
        printf("No match found!\n");
        return 0;
    }
    if(flag_e && atleast_one_found==1)
    {
        if(first_dir_found)
        {
            int response=chdir(path_of_first_found);
            if(response==-1){
                printf("No such directory exists!\n");
                return 0;
            }
            else
            {
                printf("Directory changed to %s\n", path_of_first_found);
                return 0;
            }
        }
        if(first_file_found)
        {
            printf("Opening file %s\n", path_of_first_found);
            FILE* f=fopen(path_of_first_found, "r");
            if(f==NULL)
            {
                printf("Error opening file!\n");
                return 0;
            }
            char *line=(char*)malloc(sizeof(char)*1024);
            while(fgets(line, 1024, f)!=NULL)
            {
                printf("%s", line);
            }
            fclose(f);
            free(line);
            return 0;
        }
    }

    return 0;
}