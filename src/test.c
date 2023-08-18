#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
// ANSI color escape codes
#define COLOR_RESET "\x1B[0m"
#define COLOR_DIRECTORY "\x1B[34m"  // Blue
#define COLOR_EXECUTABLE "\x1B[32m" // Green
// Comparison function for sorting
int compare_entries(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]) {
    // Check if a directory path is provided
    const char *dir_path = (argc > 1) ? argv[1] : ".";

    // Open the directory
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Error opening directory");
        return EXIT_FAILURE;
    }

    // Read directory entries and store names in an array
    struct dirent *entry;
    size_t entry_count = 0;
    char **entry_names = NULL;

    while ((entry = readdir(dir)) != NULL) {
        entry_names = realloc(entry_names, (entry_count + 1) * sizeof(char *));
        if (entry_names == NULL) {
            perror("Memory allocation error");
            closedir(dir);
            return EXIT_FAILURE;
        }
        entry_names[entry_count] = strdup(entry->d_name);
        if (entry_names[entry_count] == NULL) {
            perror("Memory allocation error");
            closedir(dir);
            return EXIT_FAILURE;
        }
        entry_count++;
    }

    // Close the directory
    closedir(dir);

    // Sort the array of entry names
    qsort(entry_names, entry_count, sizeof(char *), compare_entries);

    // Print sorted entry names
    for (size_t i = 0; i < entry_count; i++) {
        const char *entry_name = entry_names[i];
        struct stat entry_info;
        if (lstat(entry_name, &entry_info) == -1) {
            perror("Error getting entry information");
            continue;
        }

        if (S_ISDIR(entry_info.st_mode)) {
            printf(COLOR_DIRECTORY "%s\n" COLOR_RESET, entry_name);
        } else if (entry_info.st_mode & S_IXUSR) {
            printf(COLOR_EXECUTABLE "%s\n" COLOR_RESET, entry_name);
        } else {
            printf("%s\n", entry_name);
        }

        free(entry_names[i]);
    }
    free(entry_names);

    return EXIT_SUCCESS;
}
