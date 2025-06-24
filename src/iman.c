#include "iman.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void print_formatted(char *str)
{
    char *stop = (char *)malloc(sizeof(char) * 1024);
    strcpy(stop, "<STRONG><A HREF=");
    int it_stop = 0;
    // char *start = strstr(str, "NAME");
    char *s2 = (char *)malloc(sizeof(char) * 102400);
    strcpy(s2, str);
    char **temp = separate_by_delimeter(s2, "NAME");
    int it = 0;
    int print_flag = 0;
    bool in_tag = false;
    while (str[it] != '\0')
    {
        if (print_flag > 1)
        {

            if (str[it] == '<')
            {
                in_tag = true;
            }
            else if (str[it] == '>')
            {
                in_tag = false;
            }
            else if (!in_tag)
            {
                putchar(str[it]);
            }
        }
        else
        {
            if (str[it] == 'N' && str[it + 1] == 'A' && str[it + 2] == 'M' && str[it + 3] == 'E')
            {
                print_flag++;
                if (print_flag > 1)
                {
                    if (str[it] == '<')
                    {
                        in_tag = true;
                    }
                    else if (str[it] == '>')
                    {
                        in_tag = false;
                    }
                    else if (!in_tag)
                    {
                        putchar(str[it]);
                    }
                    // printf("%c", str[it]);
                }
            }
        }
        it++;
    }
    if(print_flag<=1)
    {
        fprintf(stderr, "NO man page found for the given command.\n");
    }
    // puts("");
    // puts(str);
}

void iman(char *command)
{

    char **Command = separate_by_delimeter(command, " ");
    if (Command[1] == NULL)
    {
        fprintf(stderr, "NO command specified for iMan\n");
        return;
    }
    char *command_name = Command[1];
    char request[102400];
    // snprintf(request, sizeof(request), "GET /%s.1.html HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command_name);
    snprintf(request, sizeof(request), "GET http://man.he.net/?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command_name);

    struct hostent *server_info;
    struct sockaddr_in server_address;

    server_info = gethostbyname("man.he.net");
    if (server_info == NULL)
    {
        error("Error in DNS resolution");
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("Error opening socket");
    }

    bzero((char *)&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    bcopy((char *)server_info->h_addr, (char *)&server_address.sin_addr.s_addr, server_info->h_length);
    server_address.sin_port = htons(80);

    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        error("Error connecting to server");
    }

    if (write(sockfd, request, strlen(request)) < 0)
    {
        error("Error writing to socket");
    }

    char response[102400];
    int total_bytes_read = 0;
    int bytes_read;

    while ((bytes_read = read(sockfd, response + total_bytes_read, sizeof(response) - total_bytes_read - 1)) > 0)
    {
        total_bytes_read += bytes_read;
    }

    if (bytes_read < 0)
    {
        error("Error reading from socket");
    }

    // Check if the page exists
    if (strstr(response, "404 Not Found") != NULL)
    {
        printf("Error: Man page for '%s' not found.\n", command_name);
    }
    else
    {
        // Print the man page
        // printf("%s\n", response);
        print_formatted(response);
        //
    }

    close(sockfd);
    return 0;
}
