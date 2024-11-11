/*Write a C program that receives file names as command-line arguments and displays those filenames in ascending order according to their sizes.

Example Usage: ./a.out a.txt b.txt c.txt*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

typedef struct {
    char filename[100];
    off_t size;
} FileInfo;

int compare(const void *a, const void *b) {
    return ((FileInfo *)a)->size - ((FileInfo *)b)->size;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    FileInfo files[argc - 1];
    struct stat fileStat;

    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &fileStat) == 0) {
            strcpy(files[i - 1].filename, argv[i]);
            files[i - 1].size = fileStat.st_size;
        } else {
            printf("Cannot access %s\n", argv[i]);
            return 1;
        }
    }

    qsort(files, argc - 1, sizeof(FileInfo), compare);

    printf("Files in ascending order by size:\n");
    for (int i = 0; i < argc - 1; i++) {
        printf("%s (%ld bytes)\n", files[i].filename, files[i].size);
    }

    return 0;
}

/*$ ./a.out file1.txt file2.txt file3.txt
Files in ascending order by size:
file3.txt (500 bytes)
file1.txt (1024 bytes)
file2.txt (2048 bytes)
*/