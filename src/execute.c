#include "execute.h"


int STDIN_FD;
int STDOUT_FD;

void reset_I()
{
    if (dup2(STDIN_FD, STDIN_FILENO) < 0)
        fprintf(stderr, "Error resetting input.");
}

void reset_O()
{
    if (dup2(STDOUT_FD, STDOUT_FILENO) < 0)
        fprintf(stderr, "Error resetting output.");
}


void reset_IO()
{
    if (dup2(STDIN_FD, STDIN_FILENO) < 0)
        fprintf(stderr, "Error resetting input.");
    if (dup2(STDOUT_FD, STDOUT_FILENO) < 0)
        fprintf(stderr, "Error resetting output.");
    close(STDIN_FD);
    close(STDOUT_FD);
}

int argsize(char **args)
{
    int argsz = 0;
    while (args[argsz] != NULL)
    {
        argsz++;
    }
    return argsz;
}

void FreeArgs(char **args)
{
    int args_size = 0;
    while (args[args_size] != NULL)
    {
        args_size++;
    }
    for (int i = 0; i < args_size; i++)
    {
        free(args[i]);
    }
}

void InitArgs(char **args)
{
    args = (char**)malloc(sizeof(char*)*1024);
    for (int i = 0; i < 1024; i++)
    {
        args[i] = NULL;
    }
}

void AddArg(char **args, char *arg)
{
    int args_size = argsize(args);

    if (arg == NULL)
    {
        args[args_size] = NULL;
        return;
    }

    char *new_arg = malloc(sizeof(char) * (strlen(arg) + 1));
    strcpy(new_arg, arg);
    args[args_size] = new_arg;
}

void print_args(char**args)
{
    int args_size = 0;
    while (args[args_size] != NULL)
    {
        args_size++;
    }
    for (int i = 0; i < args_size; i++)
    {
        printf("%s\n", args[i]);
    }
}

char *Multiple_Commands[1024];

char *substr(char *str, int start, int len)
{
    char *substr = (char *)malloc((len + 1) * sizeof(char));
    int i = 0;
    while (i < len)
    {
        substr[i] = str[start + i];
        i++;
    }
    substr[i] = '\0';
    return substr;
}

int execute_multi_commands(char *input)
{
    input = remove_extra_spaces_and_tabs(input);
    if (input[0] == '\n')
        return 0;
    char *cppy = input;
    struct commands *ok = split_commands(cppy);

    int total_multi_commands = 0;
    while (ok[total_multi_commands].command != NULL)
    {
        Multiple_Commands[total_multi_commands] = (char *)malloc(1024 * sizeof(char));
        strcpy(Multiple_Commands[total_multi_commands], ok[total_multi_commands].command);
        total_multi_commands++;
    }

    int i = 0;
    int success = 0;
    while (Multiple_Commands[i] != NULL)
    {

        Multiple_Commands[i] = remove_extra_spaces_and_tabs(Multiple_Commands[i]);
        ok[i].command = Multiple_Commands[i];
        if (strcmp(Multiple_Commands[i], "") != 0)
        {
            struct commands temp;
            temp.command = Multiple_Commands[i];
            temp.print_pid_and_background = ok[i].print_pid_and_background;
            // fprintf(stderr, "%s\n",ok[i].command);
            // printf("%s %d\n", ok[i].command, ok[i].print_pid_and_background);
            success |= execute_function(temp, i);
            // success |= execute_function(ok[i]);
        }
        i++;
    }
    return success;
}

char*join_by_space(char**args)
{
    int args_size = 0;
    while (args[args_size] != NULL)
    {
        args_size++;
    }
    char*joined = (char*)malloc(sizeof(char)*1024);
    strcpy(joined, "");
    for (int i = 0; i < args_size; i++)
    {
        strcat(joined, args[i]);
        strcat(joined, " ");
    }
    return joined;
}

int execute_function(struct commands command1, int curr_indx)
{
    char *tmp = (char *)malloc(sizeof(char) * 1024);
    strcpy(tmp, command1.command);

    bool background=command1.print_pid_and_background;

    tmp=remove_extra_spaces_and_tabs(tmp);
    char **args = separate_by_delimeter(tmp, " ");
    char *command = command1.command;

    // Default IO Streams
    STDIN_FD = dup(STDIN_FILENO);
    STDOUT_FD = dup(STDOUT_FILENO);
    if (check_and_throw_error(STDIN_FD < 0 || STDOUT_FD < 0, 1, NULL))
    {
        return;
    }

    int args_size=argsize(args);
    char **cargs = (char**)malloc(sizeof(char*)*1024);

    // execute_command(args, false);
    // return 0;
    // print_args(args);
    for (int i = 0; i < args_size; i++)
    {
        // print_args(cargs);
        if (strcmp(args[i], "|") == 0)
        {
            execute_command(cargs, true, background);
            // free(cargs);
            InitArgs(cargs);
            cargs=(char**)malloc(sizeof(char*)*1024);

            // Reset STDOUT changed by execute_command when piping
            reset_O(STDOUT_FD);
        }
        else if (strcmp(args[i], "<") == 0)
        {
            if (i + 1 == argsize(args))
            {
                fprintf(stderr, "Missing file name after '<'\n");
                return;
            }

            int fd = open(args[++i], O_RDONLY);
            if (fd < 0)
            {
                fprintf(stderr, "File '%s' not found\n", args[i + 1]);
                return 0;
            }

            dup2(fd, STDIN_FILENO);
        }
        else if (strcmp(args[i], ">") == 0)
        {
            if (i + 1 == argsize(args))
            {
                fprintf(stderr, "Missing file name after '>'\n");
                return 0;
            }

            int fd = open(args[++i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                fprintf(stderr, "File '%s' not found\n", args[i + 1]);
                return 0;
            }

            dup2(fd, STDOUT_FILENO);
        }
        else if (strcmp(args[i], ">>") == 0)
        {
            if (i + 1 == argsize(args))
            {
                fprintf(stderr, "Missing file name after '>>'\n");
                return 0;
            }
            int fd = open(args[++i], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                fprintf(stderr, "File '%s' not found\n", args[i + 1]);
                return 0;
            }

            dup2(fd, STDOUT_FILENO);
        }
        else
        {
            AddArg(cargs, args[i]);
        }
    }
    
    execute_command(cargs, false, background);
    reset_IO(STDIN_FD, STDOUT_FD);

}


// Function: execute
void execute_command(char**args, bool use_pipe, bool background)
{
    if (argsize(args) == 0)
    {
        return;
    }
    // printf("%d",argsize(args));
    // puts(args[0]);
        
    // return;
    char*command=join_by_space(args);
    // puts(command);
    // puts(command);
    int pipefd[2];
    if (use_pipe)
    {
        if (check_and_throw_error(pipe(pipefd) < 0, 1, NULL) == 1)
        {
            return;
        }
        dup2(pipefd[1], STDOUT_FILENO);
    }
    
    if (strcmp("exit", args[0]) == 0 || strcmp("quit", args[0]) == 0)
    {
        exit(0); // this terminates the program.
    }    else if (strcmp(args[0], "warp") == 0)
    {
        warp_warp(command);
    }
    else if (strcmp(args[0], "peek") == 0)
    {
        peek_peek(command);
    }
    else if (strcmp(args[0], "pastevents") == 0)
    {
        pastevents_function(command);
    }
    else if (strcmp(args[0], "proclore") == 0)
    {
        pinfo(command);
    }
    else if (strcmp(args[0], "seek") == 0)
    {
        seek_seek(command);
    }
    else if (strcmp(args[0], "activities") == 0)
    {
        activities();
    }
    else if (strcmp(args[0], "ping") == 0)
    {
        ping(command);
    }
    else if (strcmp(args[0], "neonate") == 0)
    {
        neonate(command);
    }
    else if (strcmp(args[0], "fg") == 0)
    {
        fg(command);
    }
    else if (strcmp(args[0], "bg") == 0)
    {
        bg(command);
    }
    else if (strcmp(args[0], "iMan") == 0)
    {
        iman(command);
    }
    else
    {
        other_commands(command, background);
    }
    if (use_pipe)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
    }
    // puts("done");
}


int execute_function_2(struct commands command1, int curr_indx)
{

    char *command = command1.command;
    // char  *command = Multiple_Commands[curr_indx];
    bool print_pid_and_background = command1.print_pid_and_background;
    if (print_pid_and_background)
    {
        // this should print the pid of the command and then execute it
        // get the pid of the current process
        pid_t pid = getpid();
        // printf("%s[%d]%s\n", BLUE, pid, RESET);
    }
    if (strcmp("exit", command) == 0 || strcmp("quit", command) == 0)
    {
        exit(0); // this terminates the program.
    }
    char *check_first_4 = substr(command, 0, 4);
    char *check_first_10 = substr(command, 0, 10);
    char *cppy = (char *)malloc(sizeof(char) * 1024);
    strcpy(cppy, command);
    char **Command = separate_by_delimeter(cppy, " ");
    // warp workes as cd
    // puts(check_warp);


    if (strcmp(Command[0], "warp") == 0)
    {
        warp_warp(command);
    }
    else if (strcmp(Command[0], "peek") == 0)
    {
        peek_peek(command);
    }
    else if (strcmp(Command[0], "pastevents") == 0)
    {
        pastevents_function(command);
    }
    else if (strcmp(Command[0], "proclore") == 0)
    {
        pinfo(command);
    }
    else if (strcmp(Command[0], "seek") == 0)
    {
        seek_seek(command);
    }
    else if (strcmp(Command[0], "activities") == 0)
    {
        activities();
    }
    else if (strcmp(Command[0], "ping") == 0)
    {
        ping(command);
    }
    else if (strcmp(Command[0], "neonate") == 0)
    {
        neonate(command);
    }
    else if (strcmp(Command[0], "fg") == 0)
    {
        fg(command);
    }
    else if (strcmp(Command[0], "bg") == 0)
    {
        bg(command);
    }
    else if (strcmp(Command[0], "iMan") == 0)
    {
        iman(command);
    }
    else
    {
        other_commands(command, command1.print_pid_and_background);
    }
}