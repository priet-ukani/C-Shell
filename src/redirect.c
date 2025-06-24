#include "redirect.h"

void display_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    // exit(1);
}

char* remove_double_quotes(char *str) {
    char *ok=(char*)malloc(sizeof(char)*1024);
    int index=0;
    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]=='\"')
        {
            continue;
        }
        ok[index++]=str[i];
    }
    ok[index]='\0';return ok;
}

void Redirect(char *command, int curr_indx)
{

        char *arguments[64];
        int input_fd, output_fd;
        int append_mode = 0;
        char *tmp=(char* )malloc(sizeof(char)*1024);
        strcpy(tmp, command);
        char *input_buffer=remove_double_quotes(tmp);
        // Parse the command line
        char *token = strtok(input_buffer, " ");
        int arg_count = 0;
        int redirect_input = 0;
        int redirect_output = 0;

        while (token != NULL) {
            if (strcmp(token, "<") == 0) {
                // Input redirection
                token = strtok(NULL, " ");
                if (token != NULL) {
                    input_fd = open(token, O_RDONLY);
                    if (input_fd == -1) {
                        display_error("No such input file found!");
                        return;
                    }
                    redirect_input = 1;
                } else {
                    display_error("Missing input file after <");
                }
            } else if (strcmp(token, ">") == 0) {
                // Output redirection (overwrite)
                token = strtok(NULL, " ");
                if (token != NULL) {
                    output_fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (output_fd == -1) {
                        display_error("Failed to create or open output file");
                        return;
                    }
                    redirect_output = 1;
                } else {
                    display_error("Missing output file after >");
                    return;
                }
            } else if (strcmp(token, ">>") == 0) {
                // Output redirection (append)
                token = strtok(NULL, " ");
                if (token != NULL) {
                    output_fd = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    if (output_fd == -1) {
                        display_error("Failed to create or open output file");
                        return;
                    }
                    redirect_output = 1;
                    append_mode = 1;
                } else {
                    display_error("Missing output file after >>");
                    return;
                }
            } else {
                // Regular argument
                arguments[arg_count++] = token;
            }

            token = strtok(NULL, " ");
        }

        // Null-terminate the arguments array
        arguments[arg_count] = NULL;

        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            if (redirect_input) {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }
            if (redirect_output) {
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            }

            // Execute the command
            execvp(arguments[0], arguments);
            display_error("Failed to execute the command");
        } else if (pid > 0) {
            // Parent process
            wait(NULL);

            // Reset append_mode
            append_mode = 0;
        } else {
            display_error("Failed to fork a new process");
        }
}