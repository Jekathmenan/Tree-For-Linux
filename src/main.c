#include <stdio.h>
#include <dirent.h>
#include <string.h>

int walk (const char* path, int intent);
void print_file(const char* name, int is_dir, int indent);

int main (int argc, char **argv) {
        const char* path = ".";

        if (argc > 1) {
                path = argv[1];
        }

        // print top-dir
        print_file(path, 1, 0);

        // walk dir
        int err = walk(path, 2);

        return err;
}

int walk (const char* path, int intent) {
        DIR *dir = opendir(path);

        // handle error opening file
        if (!dir) {
                perror("Error opening path");
                return 1;
        }

        struct dirent *dp;
        while ((dp = readdir(dir)) != NULL) {
                const char *name = dp->d_name;

                // ignore files 
                if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
                        continue;
                }

                if (dp->d_type == DT_DIR) {
                        // directory
                        // print name
                        print_file(name, 1, intent);

                        // walk to sub dir
                        size_t len = strlen(path) + strlen(name) + 2;
                        char sub_path[len];
                        snprintf(sub_path, len, "%s/%s", path, name);

                        // recursive call to walk
                        walk(sub_path, intent + 2);
                }
                else {
                        // print file name
                        print_file(name, 0, intent);
                }
        }

        // close dir
        closedir(dir);

        return 0;
}

void print_file (const char* name, int is_dir, int indent) {
        printf("%*c", indent * 2, ' ');

        if (is_dir)  {
                printf("\033[0;36m%s\033[m\n", name);
        } else {
                printf("\033[0;33m%s\033[m\n", name);
        }
}