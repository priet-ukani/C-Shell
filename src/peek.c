#include "execute.h"
#include "extra_functions.h"
#include "peek.h"

int compare_entries(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

bool flag_a=false;
bool flag_l=false;
int ignore_start=0;
void flags_check(char* peek_to)
{
    char* temp2=substr(peek_to,0,2);
    char* temp2_2=substr(peek_to,3,2);
    char* temp3=substr(peek_to,0,3);
    if(strcmp(temp2, "-l")==0){ flag_l=true; }
    else if(strcmp(temp2, "-a")==0) flag_a=true;
    if(strcmp(temp2_2, "-l")==0) flag_l=true;
    else if(strcmp(temp2_2, "-a")==0) flag_a=true;
    if(strcmp(temp3, "-la")==0) flag_l=flag_a=true;
    else if(strcmp(temp3, "-al")==0) flag_l=flag_a=true;
}

void peek_peek(char*command)
{
    // peek works as ls command to list all files and folders 
    char* peek_to=substr(command,5,strlen(command)-5);

    flag_a=false;
    flag_l=false;
    flags_check(peek_to);
    // printf("Flag_A: %d, Flag_L: %d\n", flag_a,flag_l);
    
    char *dir_path = (strlen(peek_to) > 0) ? peek_to : ".";
    
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    // Read directory entries and store names in an array
    struct dirent *entry;
    size_t entry_count = 0;
    char **entry_names = NULL;

    while ((entry = readdir(dir)) != NULL) {
        entry_names = realloc(entry_names, (entry_count + 1) * sizeof(char *));
        if (entry_names == NULL) {
            perror("Memory allocation error");
            closedir(dir);
            return;
        }
        entry_names[entry_count] = strdup(entry->d_name);
        if (entry_names[entry_count] == NULL) {
            perror("Memory allocation error");
            closedir(dir);
            return;
        }
        entry_count++;
    }

    // Close the directory
    closedir(dir);

    // Sort the array of entry names
    qsort(entry_names, entry_count, sizeof(char *), compare_entries);

    // Print sorted entry names
    for (size_t i = 0; i < entry_count; i++) {
        char *entry_name = entry_names[i];
        if(entry_name[0]=='.')
        {
            // hidden files to be ignored by default 
            if(!flag_a)
            {
                // if not hidden files to be shown then continue;
                continue;
            }
        }
        struct stat entry_info;
        if (lstat(entry_name, &entry_info) == -1) {
            perror("Error getting entry information");
            continue;
        }

        if (S_ISDIR(entry_info.st_mode)) {
            printf(COLOR_DIRECTORY "%s\n" COLOR_RESET, entry_name);
        } else if (entry_info.st_mode & S_IXUSR) {
            printf(COLOR_EXECUTABLE "%s\n" COLOR_RESET, entry_name);
        } else {
            printf(COLOR_FILES "%s\n" COLOR_RESET, entry_name);
        }

        free(entry_names[i]);
    }
    free(entry_names);
}