// #include "pipe.h"

// // Pipes are used to pass information between commands. It takes the output from command on left and passes it as standard input to the command on right. Your shell should support any number of pipes. This specification should work for all commands - user defined as well as system commands defined in bash.

// // Note :

// // Return error “Invalid use of pipe”, if there is nothing to the left or to the right of a pipe.
// // Run all the commands sequentially from left to right if pipes are present.

// char *for_piping_command[1024];
// char *Command[1024];
// int compile_command(char *st)
// {
//     // printf(",%s, check",st);
//     int curr_indx = 0;

//     if (st == NULL || strcmp(st, "\n") == 0)
//         return -1;

//     char *temp_store = (char *)malloc(strlen(st) + 10);
//     strcpy(temp_store, st);
//     if (strtok(temp_store, " \r\n\t") == NULL)
//         return -1;

//     for (int i = 0; i < 1024; i++)
//         Command[i] = (char *)malloc(1024);

//     strcpy(Command[curr_indx], strtok(st, " \t\r\n"));
//     for (; Command[curr_indx];)
//     {
//         char *temp_str = strtok(NULL, " \t\r\n");
//         if (temp_str == NULL)
//         {
//             curr_indx = curr_indx + 1;
//             Command[curr_indx] = NULL;
//             break;
//         }
//         curr_indx = curr_indx + 1;
//         strcpy(Command[curr_indx], temp_str);
//     }
//     return curr_indx + 1;
// }

// int compile_piped_commands(char *st)
// {
//     int curr_indx = 0;

//     if (st == NULL || strcmp(st, "\n") == 0)
//         return -1;

//     char *temp_store = (char *)malloc(strlen(st) + 10);
//     strcpy(temp_store, st);
//     if (strtok(temp_store, "|") == NULL)
//         return -1;

//     for (int i = 0; i < 1024; i++)
//         for_piping_command[i] = (char *)malloc(1024);

//     strcpy(for_piping_command[curr_indx], temp_store);
//     for (; for_piping_command[curr_indx];)
//     {
//         char *temp_str = strtok(NULL, "|");
//         if (temp_str == NULL)
//         {
//             curr_indx = curr_indx + 1;
//             for_piping_command[curr_indx] = NULL;
//             break;
//         }
//         curr_indx = curr_indx + 1;
//         strcpy(for_piping_command[curr_indx], temp_str);
//     }
//     return curr_indx;
// }

// void Pipe(int curr_indx)
// {
//     int input_file_descriptor = dup(STDIN_FILENO);
//     int output_file_descriptor = dup(STDOUT_FILENO);

//     int number_of_pipes = compile_piped_commands(Multiple_Commands[curr_indx]);
//     int *store;
//     store = (int *)malloc(sizeof(int) * 2);
//     int file_ptr = STDIN_FILENO;
//     for (int i = 0; i < number_of_pipes; i++)
//     {
//         if (pipe(store) >= 0)
//         {
//             pid_t child_process = fork();
//             if (child_process > 0)
//             {
//                 wait(NULL);
//                 close(store[1]);
//                 file_ptr = store[0];
//             }
//             else if (child_process == 0)
//             {
//                 dup2(file_ptr, STDIN_FILENO);
//                 if (number_of_pipes != i + 1)
//                     dup2(store[1], STDOUT_FILENO);
//                 close(store[0]);

//                 strcpy(Multiple_Commands[curr_indx], for_piping_command[i]);
//                 compile_command(for_piping_command[i]);
//                 struct commands cmd1;
//                 cmd1.command=for_piping_command[i];
//                 cmd1.print_pid_and_background = false;
//                 int ok = execute_function(cmd1, curr_indx);
//                 exit(EXIT_SUCCESS);
//             }
//             else
//             {
//                 perror("Error in forking");
//                 return;
//             }
//         }
//         else
//         {
//             perror("Error in Piping");
//             return;
//         }
//     }
//     dup2(input_file_descriptor, STDIN_FILENO);
//     dup2(output_file_descriptor, STDOUT_FILENO);
//     return;
// }