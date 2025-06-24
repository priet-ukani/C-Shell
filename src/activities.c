#include "activities.h"


struct for_sorting
{
    int indx;
    char *store;
    char *job_name;
    int job_pid;
    int val;
};

int Comp(const void *a, const void *b)
{
    return strcmp(((struct for_sorting *)a)->job_name,((struct for_sorting *)b)->job_name) >= 0;
}

struct for_sorting temp_store_for_sorting[1024];

char *helper_function_for_jobs(int len,char *file_name)
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

void activities()
{
    int output_count=0;
    for(int i=0;i<num_of_bg_jobs;i++)
    {
        char *proc_file_path;
        proc_file_path=(char *)malloc(1024);
        sprintf(proc_file_path,"/proc/%d/stat",BJobs[i].pid);
        FILE * file_ptr = fopen(proc_file_path,"r");
        if(file_ptr!=NULL)
        {
            char*    store=(char *)malloc(1024);
            char *temp_ptr=(char *)malloc(1024);

            fgets(temp_ptr,1024,file_ptr);
            strcpy(store,helper_function_for_jobs(3,temp_ptr));
            if(strcmp(store,"T") && strcmp(store,"I"))
                strcpy(store,"Running");
            else
                strcpy(store,"Stopped");
            
            temp_store_for_sorting[i].job_name=(char *)malloc(1024);
            temp_store_for_sorting[i].indx=i+1;
            temp_store_for_sorting[i].store=(char *)malloc(1024);
            output_count++;
            strcpy(temp_store_for_sorting[i].store,store);
            temp_store_for_sorting[i].job_pid=BJobs[i].pid;
            temp_store_for_sorting[i].job_name=BJobs[i].p_name;
            free(temp_ptr);
            free(store);
        }
        else
        {
            // fprintf(stderr,"Can't open process directory for process %d",BJobs[i].pid);
        }
        free(proc_file_path);
    }
    qsort(temp_store_for_sorting,output_count,sizeof(struct for_sorting),Comp);
    for(int i=0;i<output_count;i++)
    {
        printf("%d : %s - %s\n",temp_store_for_sorting[i].job_pid, temp_store_for_sorting[i].job_name, temp_store_for_sorting[i].store);
    }
}   