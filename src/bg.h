#ifndef BG_H
#define BG_H

struct BackgroundJobs
{
    int pid;
    char p_name[1024];
};
extern struct BackgroundJobs BJobs[1024];
extern int num_of_bg_jobs;

#endif