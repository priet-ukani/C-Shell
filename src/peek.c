#include "execute.h"
#include "extra_functions.h"
#include "peek.h"
#include "colours.h"

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
    int index=0;
    while((entries=readdir(directory))!=NULL)
    {
        entries_store[index++]=entries;
    }
    qsort(entries_store, index, sizeof(struct dirent*), compare);
    for (int i = 0; i < index; i++)
    {
        if (entries_store[i]->d_name[0] == '.' && peek_to[0] != '.')
            continue;
        printf("%s\n", entries_store[i]->d_name);
    }
}