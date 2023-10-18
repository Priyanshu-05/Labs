#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int is_directory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }
    
    DIR *dir_ptr = opendir(argv[1]);
    if (dir_ptr == NULL) {
        fprintf(stderr, "Cannot open directory: %s\n", argv[1]);
        return 1;
    }
    
    struct dirent *entry;
    char *subdirs[100]; // Adjust the size as needed
    
    int subdir_count = 0;
    
    while ((entry = readdir(dir_ptr)) != NULL) {
        if (is_directory(entry->d_name) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            subdirs[subdir_count] = strdup(entry->d_name);
            subdir_count++;
        }
    }
    
    qsort(subdirs, subdir_count, sizeof(char *), compare_strings);
    
    for (int i = 0; i < subdir_count; i++) {
        printf("%s\n", subdirs[i]);
        free(subdirs[i]);
    }
    
    closedir(dir_ptr);
    
    return 0;
}
