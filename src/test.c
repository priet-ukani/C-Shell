#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void print_directory_contents(const char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        printf("Contents of directory: %s\n", path);
        printf("==============================\n");

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }

        closedir(dir);
    } else {
        printf("Directory not found.\n");
    }
}

int main() {
    char path[256];  // Adjust the size as needed
    printf("Enter the directory path: ");
    fgets(path, sizeof(path), stdin);
    path[strcspn(path, "\n")] = '\0';  // Remove the newline character

    // Check if the path is relative, and if so, make it absolute
    if (path[0] != '/' && path[0] != '\\') {
        char current_dir[256];
        if (getcwd(current_dir, sizeof(current_dir)) != NULL) {
            strcat(current_dir, "/");
            strcat(current_dir, path);
            strcpy(path, current_dir);
        }
    }

    print_directory_contents(path);

    return 0;
}
