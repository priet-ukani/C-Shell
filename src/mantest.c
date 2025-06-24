#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 4096

// Function to perform DNS resolution and return the IP address
int resolveDNS(const char *host, char *ip) {
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ((he = gethostbyname(host)) == NULL) {
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **)he->h_addr_list;

    for (i = 0; addr_list[i] != NULL; i++) {
        // Return the first IP address found
        strcpy(ip, inet_ntoa(*addr_list[i]));
        return 0;
    }

    return 1;
}

// Function to fetch and display the man page
void fetchManPage(const char *command_name) {
    char ip[INET_ADDRSTRLEN];
    char request[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];
    int sockfd;
    struct sockaddr_in server_addr;
    struct hostent *server;

    // Resolve DNS for man.he.net
    if (resolveDNS("man.he.net", ip) != 0) {
        fprintf(stderr, "Error: Unable to resolve DNS for man.he.net\n");
        return;
    }

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error: Unable to create socket");
        return;
    }

    server = gethostbyname("man.he.net");
    if (server == NULL) {
        fprintf(stderr, "Error: No such host\n");
        return;
    }

    // Prepare server_addr struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error: Unable to connect to server");
        return;
    }

    // Prepare the GET request
    snprintf(request, sizeof(request), "GET /%s HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command_name);

    // Send the GET request
    if (write(sockfd, request, strlen(request)) < 0) {
        perror("Error: Unable to send request");
        return;
    }

    // Read and print the response
    while (read(sockfd, buffer, sizeof(buffer)) > 0) {
        printf("%s", buffer);
    }

    // Close the socket
    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <command_name>\n", argv[0]);
        return 1;
    }

    const char *command_name = argv[1];
    fetchManPage(command_name);

    return 0;
}
