#include "execute.h"
#include "extra_functions.h"
#include "peek.h"

int compare_entries(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void peek_peek(char*command)
{
    // peek works as ls command to list all files and folders 
    char* peek_to=substr(command,5,strlen(command)-5);
    char *dir_path = (strlen(peek_to) > 0) ? peek_to : ".";
   
       DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Error opening directory");
        return EXIT_FAILURE;
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
        const char *entry_name = entry_names[i];
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
            printf("%s\n", entry_name);
        }

        free(entry_names[i]);
    }
    free(entry_names);
   
   
    // DIR *directory = opendir(dir_path);
    // if(directory==NULL)
    // {
    //     perror(RED"Error"RESET);
    // }

    // struct dirent* entries;
    // struct dirent** entries_store;
    // entries_store=(struct dirent **)malloc(sizeof(struct dirent*)*1024);
    // int entry_count=0;
    // while((entries=readdir(directory))!=NULL)
    // {
    //     entries_store[entry_count++]=entries;
    // }
    // qsort(entries_store, entry_count, sizeof(struct dirent*), compare);
    // for (size_t i = 0; i < entry_count; i++) {
    //     const char *entry_name = entries_store[i];
    //     struct stat entry_info;
    //     if (lstat(entry_name, &entry_info) == -1) {
    //         perror("Error getting entry information");
    //         continue;
    //     }

    //     if (S_ISDIR(entry_info.st_mode)) {
    //         printf(COLOR_DIRECTORY "%s\n" COLOR_RESET, entry_name);
    //     } else if (entry_info.st_mode & S_IXUSR) {
    //         printf(COLOR_EXECUTABLE "%s\n" COLOR_RESET, entry_name);
    //     } else {
    //         printf("%s\n", entry_name);
    //     }

    //     free(entries_store[i]);
    // }
    // free(entries);
}