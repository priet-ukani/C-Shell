#include "execute.h"
#include "extra_functions.h"
#include "peek.h"

int compare_entries(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

bool flag_a = false;
bool flag_l = false;
int ignore_start = 0;
void flags_check(char *peek_to)
{
    char *temp2 = substr(peek_to, 0, 2);
    char *temp2_2 = substr(peek_to, 3, 2);
    char *temp3 = substr(peek_to, 0, 3);
    if (strcmp(temp3, "-la") == 0)
    {
        flag_l = flag_a = true;
        ignore_start += 3;
        return;
    }
    else if (strcmp(temp3, "-al") == 0)
    {
        flag_l = flag_a = true;
        ignore_start += 3;
        return;
    }
    if (strcmp(temp2, "-l") == 0)
    {
        flag_l = true;
        ignore_start += 2;
    }
    else if (strcmp(temp2, "-a") == 0)
    {
        flag_a = true;
        ignore_start += 2;
    }
    if (strcmp(temp2_2, "-l") == 0)
    {
        flag_l = true;
        ignore_start += 3;
    }
    else if (strcmp(temp2_2, "-a") == 0)
    {
        flag_a = true;
        ignore_start += 3;
    }
}

void print_colored(const char *text, const char *color) {
    printf("%s%s%s", color, text, "\x1b[0m"); // Set color and reset after printing
}

int is_executable(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        return (st.st_mode & S_IXUSR) != 0;
    }
    return 0;
}
void print_directory_contents(char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        struct dirent *entry;
        char **entry_items;
        entry_items=(char**)malloc(sizeof(char*)*1024);
        int entry_count=0;
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
            entry_items[entry_count++]=entry->d_name;
        }
        qsort(entry_items, entry_count, sizeof(char *), compare_entries);

                for (int i = 0; i < entry_count; i++) {
            char *entry_name = entry_items[i];
            const char *color = NULL;

            if (is_executable(entry_name)) {
                color = "\x1b[32m"; // Green color for executables
            } else {
                color = "\x1b[34m"; // Blue color for files
            }

            if (entry_name[0] == '.') {
                color = "\x1b[90m"; // Gray color for hidden files/dirs
            }

            if (entry_name[strlen(entry_name) - 1] == '/') {
                color = "\x1b[36m"; // Cyan color for directories
            }

            print_colored(entry_name, color);
            printf("\n");
            free(entry_name);
        }

        closedir(dir);
        free(entry_items);

    }
    else {
        perror("Error opening directory");    
    }
}




void peek_peek(char *command)
{
    // peek works as ls command to list all files and folders
    char *peek_to = substr(command, 5, strlen(command) - 5);

    flag_a = false;
    flag_l = false;
    ignore_start = 0;
    flags_check(peek_to);
    // printf("Flag_A: %d, Flag_L: %d\n", flag_a,flag_l);
    // remove the first ignore_start characters from the peek_to path
    char *dir_path=(char*)malloc(sizeof(1024*sizeof(char)));
    dir_path = substr(peek_to, ignore_start, strlen(peek_to) - ignore_start);
    // printf("%d<- len, path-> %s\n", strlen(peek_to), peek_to);
    char *path=(char*)malloc(1024*sizeof(char));
    path=dir_path;
    printf("%s", path);
    path[strcspn(path, "\n")] = '\0';  // Remove the newline character
    // Check if the path is relative, and if so, make it absolute
    if (path[0] != '/' && path[0] != '\\') {
        char current_dir[256];
        if (getcwd(current_dir, sizeof(current_dir)) != NULL) {
            strcat(current_dir, "/");
            strcat(current_dir, path);
            strcpy(path, current_dir);
        }
    }

    print_directory_contents(path);
}
