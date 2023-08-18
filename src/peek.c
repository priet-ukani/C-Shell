#include "execute.h"
#include "extra_functions.h"
#include "peek.h"

int compare(const void*a, const void*b)
{
    struct dirent* a1=*(struct dirent**)a;
    struct dirent* b1=*(struct dirent**)b;
    return strcmp(a1->d_name, b1->d_name);
}

void peek_peek(char*command)
{
    // peek works as ls command to list all files and folders 
    char* peek_to=substr(command,5,strlen(command)-5);
    char *dir_path = (strlen(peek_to) > 0) ? peek_to : ".";
    DIR *directory = opendir(dir_path);
    if(directory==NULL)
    {
        perror(RED"Error"RESET);
    }

    struct dirent* entries;
    struct dirent** entries_store;
    entries_store=(struct dirent **)malloc(sizeof(struct dirent*)*1024);
    int entry_count=0;
    while((entries=readdir(directory))!=NULL)
    {
        entries_store[entry_count++]=entries;
    }
    qsort(entries_store, entry_count, sizeof(struct dirent*), compare);
    for (size_t i = 0; i < entry_count; i++) {
        const char *entry_name = entries_store[i];
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

        free(entries[i]);
    }
    free(entries);
}