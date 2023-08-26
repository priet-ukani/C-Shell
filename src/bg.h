#ifndef BG_H
#define BG_H

struct BackgroundJobs
{
    int pid;
    char p_name[1024];
};
struct BackgroundJobs BJobs[1024];
int num_of_bg_jobs=0;

#endif