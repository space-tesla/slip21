/*Read the current directory and display the names of the files and the number of files in the current directory.*/
#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *d;
    struct dirent *dir;
    int count = 0;

    d = opendir(".");
    if (d) {
        printf("Files in current directory:\n");
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                printf("%s\n", dir->d_name);
                count++;
            }
        }
        closedir(d);
        printf("Total number of files: %d\n", count);
    }

    return 0;
}

/*Files in current directory:
file1.txt
file2.c
image.png
Total number of files: 3
*/