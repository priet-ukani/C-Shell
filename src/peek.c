#include "execute.h"
#include "extra_functions.h"
#include "peek.h"

char mode_permission[10];
mode_t permissions_macros[10] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
int sum = 0;
char *buffer_s;
struct for_sorting_str
{
    char *for_sorting_name;
    int color_print;
};

int cmp(const void *a, const void *b)
{
    // printf("%s %s\n",*(char**)a,*(char**)b);
    return strcmp(*(char **)a, *(char **)b) >= 0;
}

int cmp1(const void *a, const void *b)
{
    const struct for_sorting_str *struct_a = (const struct for_sorting_str *)a;
    const struct for_sorting_str *struct_b = (const struct for_sorting_str *)b;

    return strcmp(struct_a->for_sorting_name, struct_b->for_sorting_name);
}

// Function to get file permissions as a string (e.g., "rwxr-xr-x")
char *get_permissions(mode_t mode)
{
    static char perms[10];
    strcpy(perms, "---------");

    if (S_ISDIR(mode))
        perms[0] = 'd';
    if (mode & S_IRUSR)
        perms[1] = 'r';
    if (mode & S_IWUSR)
        perms[2] = 'w';
    if (mode & S_IXUSR)
        perms[3] = 'x';
    if (mode & S_IRGRP)
        perms[4] = 'r';
    if (mode & S_IWGRP)
        perms[5] = 'w';
    if (mode & S_IXGRP)
        perms[6] = 'x';
    if (mode & S_IROTH)
        perms[7] = 'r';
    if (mode & S_IWOTH)
        perms[8] = 'w';
    if (mode & S_IXOTH)
        perms[9] = 'x';

    return perms;
}

int IsDirectory(char *path_dir)
{
    struct stat path_stat;
    stat(path_dir, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

void return_permissions(char *filename)
{
    struct stat file;
    char temp[3] = {'r', 'w', 'x'};
    if (stat(filename, &file) == -1)
    {
        perror("Error occured");
        return;
    }
    else
    {
        mode_t current_file_permission_mode = file.st_mode;
        for (int i = 0; i < 9; i++)
        {
            if (permissions_macros[i] & current_file_permission_mode)
            {
                mode_permission[i] = temp[i % 3];
            }
            else
            {
                mode_permission[i] = '-';
            }
        }
        mode_permission[9] = '\0';
    }
}

void print_ls_with_details(char *directory_address_path, char *file_name)
{
    char *adress_of_file;
    adress_of_file = (char *)malloc(1024);
    strcpy(adress_of_file, directory_address_path);

    strcat(adress_of_file, "/");
    strcat(adress_of_file, file_name);
    struct stat info;
    if (stat(adress_of_file, &info) != -1)
    {
        // sum+=info.st_blocks;
        return_permissions(adress_of_file);
        struct passwd *password_1 = getpwuid(info.st_uid);
        struct group *group_1 = getgrgid(info.st_gid);

        char *time = (char *)malloc(50);
        strftime(time, 50, "%b  %d %H:%M", localtime(&info.st_mtime));
        if (!S_ISDIR(info.st_mode) && mode_permission[2] != 'x')
        {
            printf("-%s   %ld\t%s\t %s\t%ld\t%s\t", mode_permission, info.st_nlink, password_1->pw_name, group_1->gr_name, info.st_size, time);
            printf("%s\n", file_name);
        }
        else if (!S_ISDIR(info.st_mode) && mode_permission[2] == 'x')
        {
            printf("-%s   %ld\t%s\t %s\t%ld\t%s\t", mode_permission, info.st_nlink, password_1->pw_name, group_1->gr_name, info.st_size, time);
            printf(GREEN "%s\n" RESET, file_name);
        }
        else
        {
            printf("d%s   %ld\t%s\t %s\t%ld\t%s\t", mode_permission, info.st_nlink, password_1->pw_name, group_1->gr_name, info.st_size, time);
            printf(BLUE "%s\n" RESET, file_name);
        }
        free(adress_of_file);
    }
    else
    {
        perror("Error in execution of stat");
    }
}

void compute_total(char *directory_address_path, char *file_name)
{
    char *adress_of_file;
    adress_of_file = (char *)malloc(1024);
    strcpy(adress_of_file, directory_address_path);

    strcat(adress_of_file, "/");
    strcat(adress_of_file, file_name);
    struct stat info;
    if (stat(adress_of_file, &info) == -1)
    {
        // last_Command_words_list_status = -1;
        perror("Error in execution of stat");
        return;
    }
    else
    {
        sum += info.st_blocks;
        // free(adress_of_file);
    }
}

void display_ls(char *directory_address_path, int flag_ls_a, int flag_ls_l)
{
    bool flag_to_break = false;
    if (!IsDirectory(directory_address_path) && !flag_ls_l)
    {
        char *adress_of_file;
        adress_of_file = (char *)malloc(1024);
        strcpy(adress_of_file, directory_address_path);
        return_permissions(adress_of_file);
        struct stat info;
        if (stat(adress_of_file, &info) == 0 && S_ISDIR(info.st_mode)) // directory blue
        {
            printf(BLUE "%s\t" RESET, adress_of_file);
        }
        else if (mode_permission[2] == 'x')
        {
            printf(GREEN "%s\t" RESET, adress_of_file);
        }
        else
        {
            printf("%s\t", adress_of_file);
        }
        // dire++;
        free(adress_of_file);
    }
    else if (!IsDirectory(directory_address_path))
    {
        char *adress_of_file;
        adress_of_file = (char *)malloc(1024);
        strcpy(adress_of_file, directory_address_path);

        struct stat info;
        if (stat(adress_of_file, &info) != -1)
        {
            return_permissions(adress_of_file);
            char *time = (char *)malloc(50);
            struct group *group_1 = getgrgid(info.st_gid);
            struct passwd *password_1 = getpwuid(info.st_uid);
            strftime(time, 50, "%b  %d %H:%M", localtime(&info.st_mtime));

            if (!S_ISDIR(info.st_mode) && mode_permission[2] == 'x')
            {
                printf("-%s   %ld\t%s\t %s\t%ld\t%s\t", mode_permission, info.st_nlink, password_1->pw_name, group_1->gr_name, info.st_size, time);
                printf(GREEN "%s\n" RESET, adress_of_file);
            }
            else if (!S_ISDIR(info.st_mode) && mode_permission[2] != 'x')
            {
                printf("-%s   %ld\t%s\t %s\t%ld\t%s\t%s\n", mode_permission, info.st_nlink, password_1->pw_name, group_1->gr_name, info.st_size, time, adress_of_file);
            }
            else
            {
                printf("d%s   %ld\t%s\t %s\t%ld\t%s\t", mode_permission, info.st_nlink, password_1->pw_name, group_1->gr_name, info.st_size, time);
                printf(BLUE "%s\n" RESET, adress_of_file);
            }
            free(adress_of_file);
        }
        else
        {
            perror("Error in execution of stat");
            return;
        }
    }
    else
    {
        struct dirent *file_ptr;
        DIR *directory = opendir(directory_address_path);
        if (directory == NULL)
        {
            perror("Error : can't open directory");
            return;
        }
        else
        {
            char **for_sorting;
            struct for_sorting_str *for_sorting1;
            int *colouring_print_flag;
            int dire = 0;
            buffer_s = (char *)malloc(sizeof(char) * 1024);
            while ((file_ptr = readdir(directory)) != NULL)
                dire++;
            colouring_print_flag = (int *)malloc(dire * sizeof(int));
            directory = opendir(directory_address_path);
            for_sorting = (char **)malloc(dire * sizeof(char *));
            for_sorting1 = (struct for_sorting_str *)malloc(dire * sizeof(struct for_sorting_str));
            dire = 0;
            buffer_s = NULL;

            while ((file_ptr = readdir(directory)) != NULL)
            {
                if ((file_ptr = readdir(directory)) == NULL)
                    break;
                if (flag_ls_l == 1)
                    compute_total(directory_address_path, file_ptr->d_name);
                if (flag_ls_a == 0 && file_ptr->d_name[0] == '.')
                    continue;
            }
            directory = opendir(directory_address_path);
            int tmep_print = sum / 2;
            if (sum != 0)
            {
                printf("total : %d\n", tmep_print);
            }
            while ((file_ptr = readdir(directory)) != NULL)
            {
                if ((file_ptr = readdir(directory)) == NULL)
                    break;
                if (flag_ls_a == 0 && file_ptr->d_name[0] == '.')
                {

                    if (flag_to_break)
                        break;
                    // ignore hidden files
                    continue;
                }
                if (flag_ls_l == 0)
                {
                    if (flag_to_break)
                        break;

                    char *adress_of_file;
                    adress_of_file = (char *)malloc(1024);
                    struct stat info;
                    strcpy(adress_of_file, directory_address_path);
                    strcat(adress_of_file, "/");
                    strcat(adress_of_file, file_ptr->d_name);
                    return_permissions(adress_of_file);
                    if (stat(adress_of_file, &info) == 0 && S_ISDIR(info.st_mode)) // directory blue
                    {
                        if (flag_to_break)
                            break;

                        for_sorting[dire] = (char *)malloc(strlen(file_ptr->d_name));
                        for_sorting1[dire].for_sorting_name = (char *)malloc(strlen(file_ptr->d_name));
                        strcpy(for_sorting[dire], file_ptr->d_name);
                        strcpy(for_sorting1[dire].for_sorting_name, file_ptr->d_name);

                        colouring_print_flag[dire] = 1;
                        for_sorting1[dire].color_print = 1;
                    }
                    else if (mode_permission[2] == 'x')
                    {
                        if (flag_to_break)
                            break;

                        for_sorting[dire] = (char *)malloc(strlen(file_ptr->d_name));
                        for_sorting1[dire].for_sorting_name = (char *)malloc(strlen(file_ptr->d_name));
                        strcpy(for_sorting[dire], file_ptr->d_name);
                        strcpy(for_sorting1[dire].for_sorting_name, file_ptr->d_name);

                        colouring_print_flag[dire] = 2;
                        for_sorting1[dire].color_print = 2;
                        // printf("\033[1;32m%s\033[0m    ",file_ptr->d_name);
                    }
                    else
                    {
                        if (flag_to_break)
                            break;

                        for_sorting[dire] = (char *)malloc(strlen(file_ptr->d_name));
                        for_sorting1[dire].for_sorting_name = (char *)malloc(strlen(file_ptr->d_name));
                        strcpy(for_sorting[dire], file_ptr->d_name);
                        if (flag_to_break)
                            break;

                        strcpy(for_sorting1[dire].for_sorting_name, file_ptr->d_name);
                        colouring_print_flag[dire] = 3;
                        for_sorting1[dire].color_print = 3;
                        // printf("%s    ",file_ptr->d_name);
                    }
                    dire++;
                    free(adress_of_file);
                }
                else
                {
                    if (flag_to_break)
                        break;

                    print_ls_with_details(directory_address_path, file_ptr->d_name);
                }
            }
            if (flag_ls_l == 0)
            {
                qsort(for_sorting, dire, sizeof(char *), cmp);
                qsort(for_sorting1, dire, sizeof(struct for_sorting_str), cmp1);
                for (int i = 0; i < dire; i++)
                {

                    if (for_sorting1[i].color_print == 1)
                        printf(BLUE "%s" RESET, for_sorting1[i].for_sorting_name);
                    else if (for_sorting1[i].color_print == 2)
                        printf(GREEN "%s\033[0m" RESET, for_sorting1[i].for_sorting_name);
                    else
                        printf("%s", for_sorting1[i].for_sorting_name);
                    printf("\n");
                }
            }
            closedir(directory);
        }
    }
}

int peek_peek(char *command)
{
    char **Command_words_list = (char **)malloc(sizeof(char *) * 1024);
    for (int i = 0; i < 1024; i++)
    {
        Command_words_list[i] = (char *)malloc(sizeof(char) * 1024);
    }
    Command_words_list = separate_by_delimeter(command, " ");

    int curr_indx = 1;
    int flag_ls_a = 0;
    int flag_ls_l = 0;
    int is_printed = 0;
    int sum = 0;
    while (1)
    {
        if (Command_words_list[curr_indx] == NULL)
            break;

        if (Command_words_list[curr_indx][0] != '-')
        {
            if (Command_words_list[curr_indx] == NULL)
                break;

            struct stat info;
            sum += info.st_blocks;
            stat(Command_words_list[curr_indx], &info);
        }
        else
        {

            if (Command_words_list[curr_indx] == NULL)
                break;

            int length = strlen(Command_words_list[curr_indx]);
            for (int i = 0; i < length; i++)
            {
                if (Command_words_list[curr_indx] == NULL)
                    break;

                if (Command_words_list[curr_indx][i] == 'a')
                {
                    flag_ls_a = 1;
                }
                else if (Command_words_list[curr_indx][i] == 'l')
                {
                    if (Command_words_list[curr_indx] == NULL)
                        break;

                    flag_ls_l = 1;
                }
                else
                {
                    continue;
                }
                if (Command_words_list[curr_indx] == NULL)
                    break;
            }
        }
        curr_indx++;
    }
    // printf("%d ",sum);
    curr_indx = 1;
    while (1)
    {
        if (Command_words_list[curr_indx] == NULL)
            break;
        if (Command_words_list[curr_indx][0] != '-')
        {
            char *directory_address_path = (char *)malloc(1024);
            if (Command_words_list[curr_indx][0] == '~')
            {
                if (Command_words_list[curr_indx] == NULL)
                    break;

                strcpy(directory_address_path, shell_open_path);
                strcat(directory_address_path, Command_words_list[curr_indx] + 1);
                strcat(directory_address_path, "\0");
            }
            else
            {
                strcpy(directory_address_path, Command_words_list[curr_indx]);
            }
            if (Command_words_list[curr_indx] == NULL)
                break;

            display_ls(directory_address_path, flag_ls_a, flag_ls_l);
            is_printed = 1;
            free(directory_address_path);
            printf("\n");
        }
        else
        {
            int length = strlen(Command_words_list[curr_indx]);
            for (int i = 0; i < length; i++)
            {
                if (Command_words_list[curr_indx] == NULL)
                    break;

                if (Command_words_list[curr_indx][i] == 'l')
                {
                    flag_ls_l = 1;
                }
                else if (Command_words_list[curr_indx][i] == 'a')
                {
                    flag_ls_a = 1;
                }
                if (Command_words_list[curr_indx] == NULL)
                    break;
            }
        }
        if (Command_words_list[curr_indx] == NULL)
            break;

        curr_indx++;
    }
    if (is_printed == 0)
    {
        display_ls(".", flag_ls_a, flag_ls_l);
        return 1;
    }
    return 0;
}

int compare_entries(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

void print_ls(char *path, bool l, bool a)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        // Check if file
        struct stat s;

        if (stat(path, &s) == 0)
        {
            if (S_ISREG(s.st_mode))
            {
                if (l)
                {
                    // file_details(path, );
                }
                char *filename = strrchr(path, '/');
                if (filename == NULL)
                    filename = path;
                printf("%s\n", filename);
                return;
            }
        }

        char *message = malloc(sizeof(char) * (strlen(path) + strlen("ls: cannot access ''") + 1));
        sprintf(message, "ls: cannot access '%s'", path);
        // check_and_throw_error(0, 0, message);
        perror(message);
        free(message);
        return;
    }

    struct dirent *entry;
    if (l)
    {
        int block_count = 0;
        while ((entry = readdir(dir)) != NULL)
        {
            if (!a && entry->d_name[0] == '.')
                continue;
            char *file = malloc(sizeof(char) * (strlen(entry->d_name) + strlen(path) + 2));
            sprintf(file, "%s/%s", path, entry->d_name);
            struct stat s;
            if (lstat(file, &s) == -1)
                continue;
            block_count += s.st_blocks;
            free(file);
        }
        printf("total %d\n", block_count / 2);
        rewinddir(dir);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (!a && entry->d_name[0] == '.')
            continue;

        if (l)
        {
            char *file = malloc(strlen(path) + strlen(entry->d_name) + 2);
            sprintf(file, "%s/%s", path, entry->d_name);
            char *temp = (char *)malloc(sizeof(int) * 1024);
            strcpy(temp, entry->d_name);
            file_details(file, temp);
            free(file);
        }
    }
    closedir(dir);
}

// Returns char of file type
int file_type_letter(mode_t mode)
{
    char c;
    if (S_ISREG(mode))
        c = '-';
    else if (S_ISDIR(mode))
        c = 'd';
    else if (S_ISBLK(mode))
        c = 'b';
    else if (S_ISCHR(mode))
        c = 'c';
    else if (S_ISFIFO(mode))
        c = 'p';
    else if (S_ISLNK(mode))
        c = 'l';
    else if (S_ISSOCK(mode))
        c = 's';
    else
    {
        c = '?';
    }
    return (c);
}

// Prints details for a file in ls format
void file_details(char *path, char *filename)
{
    struct stat s;
    if (lstat(path, &s) == -1)
    {
        char *message = malloc(sizeof(char) * (strlen(path) + strlen("ls: cannot access ''") + 1));
        sprintf(message, "ls: cannot access '%s'", path);
        // check_and_throw_error(0, 0, message);
        perror(message);
        free(message);
        return;
    }

    char *rwx[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
    static char modes[11];

    modes[0] = file_type_letter(s.st_mode);
    strcpy(&modes[1], rwx[(s.st_mode >> 6) & 7]);
    strcpy(&modes[4], rwx[(s.st_mode >> 3) & 7]);
    strcpy(&modes[7], rwx[(s.st_mode & 7)]);
    // Special file mode handling
    if (s.st_mode & S_ISUID)
        modes[3] = (s.st_mode & S_IXUSR) ? 's' : 'S';

    if (s.st_mode & S_ISGID)
        modes[6] = (s.st_mode & S_IXGRP) ? 's' : 'l';

    if (s.st_mode & S_ISVTX)
        modes[9] = (s.st_mode & S_IXOTH) ? 't' : 'T';
    modes[10] = '\0';

    // print stuff
    char date[21];
    printf("%s ", modes);
    printf("%3.ld ", s.st_nlink);
    printf("%s ", getpwuid(s.st_uid)->pw_name);
    printf("%s ", getgrgid(s.st_gid)->gr_name);
    printf("%6.ld ", s.st_size);
    if (time(0) - s.st_mtime < 15780000)
        strftime(date, 20, "%b %d %H:%M", localtime(&(s.st_mtime)));
    else
        strftime(date, 20, "%b %d  %Y", localtime(&(s.st_mtime)));
    printf("%s ", date);
    if (s.st_mode & S_IXUSR)
    {
        printf(GREEN "%s\n" RESET, filename);
    }
    else if (s.st_mode & S_IFDIR)
    {
        printf(BLUE "%s\n" RESET, filename);
    }
    else if (S_ISLNK(s.st_mode))
    {
        printf(BLUE "%s\n" RESET, filename);
    }
    else
    {
        printf("%s\n", filename);
    }

    return;
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

void print_directory_contents(char *path)
{
    DIR *dir = opendir(path);
    if (dir)
    {
        struct dirent *entry;
        char **entry_items;
        entry_items = (char **)malloc(sizeof(char *) * 1024);
        int entry_count = 0;
        while ((entry = readdir(dir)) != NULL)
        {
            printf("%s\n", entry->d_name);
            entry_items[entry_count++] = entry->d_name;
        }
        qsort(entry_items, entry_count, sizeof(char *), compare_entries);
    }
    else
    {
        perror("Error opening directory");
    }
}

int peek_peek_1(char *Command_words_list)
{
    // peek works as ls Command_words_list to list all files and folders
    char *peek_to = substr(Command_words_list, 5, strlen(Command_words_list) - 5);

    flag_a = false;
    flag_l = false;
    ignore_start = 0;
    flags_check(peek_to);
    // printf("Flag_A: %d, Flag_L: %d\n", flag_a, flag_l);
    // remove the first ignore_start characters from the peek_to path
    char *dir_path = (char *)malloc(sizeof(1024 * sizeof(char)));
    dir_path = substr(peek_to, ignore_start, strlen(peek_to) - ignore_start);
    // printf("%d<- len, path-> %s\n", strlen(peek_to), peek_to);
    char *path = (char *)malloc(1024 * sizeof(char));
    path = dir_path;
    path = remove_extra_spaces_and_tabs(path);
    printf("%s", path);
    path[strcspn(path, "\n")] = '\0'; // Remove the newline character
    // Check if the path is relative, and if so, make it absolute
    if (path[0] != '/' && path[0] != '\\')
    {
        char current_dir[256];
        if (getcwd(current_dir, sizeof(current_dir)) != NULL)
        {
            strcat(current_dir, "/");
            strcat(current_dir, path);
            strcpy(path, current_dir);
        }
    }
    printf("%s\n", path);
    path = replace_home(path);

    // print_directory_contents(path);
    // print_ls(path,flag_l,flag_a);
    display_ls(path, flag_a, flag_l);
}
