#include <stdio.h>
#include <dirent.h>
#include <string.h>


void print_file (const char* name, int is_dir, int indent) {
        printf("%*c", indent * 2, ' ');

        if (is_dir)  {
                printf("\033[0;36m%s\033[m\n", name);
        } else {
                printf("\033[0;33m%s\033[m\n", name);
        }
}