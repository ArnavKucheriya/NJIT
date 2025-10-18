// Arnav Kucheriya - script_3.c

#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>

static int has_txt_ext_ci(const char *name) {
    const char *dot = strrchr(name, '.');
    if (!dot) return 0;
    const char *e = dot + 1;
    return (tolower((unsigned char)e[0])=='t' &&
            tolower((unsigned char)e[1])=='x' &&
            tolower((unsigned char)e[2])=='t' &&
            e[3]=='\0');
}

static long long count_lines_in_file(const char *path) {
    long long lines = 0;
    FILE *f = fopen(path, "r");
    if (!f) return 0;  // skip unreadable files
    char buf[1001];
    while (fgets(buf, sizeof(buf), f)) ++lines;
    fclose(f);
    return lines;
}

static long long walk_dir(const char *path) {
    long long total = 0;
    DIR *d = opendir(path);
    if (!d) return 0;

    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
        if (!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..")) continue;

        char child[1001];
        int n = snprintf(child, sizeof(child), "%s/%s", path, ent->d_name);
        if (n <= 0 || n >= (int)sizeof(child)) continue;

        struct stat st;
        if (stat(child, &st) != 0) continue;

        if (S_ISDIR(st.st_mode)) {
            total += walk_dir(child);
        } else if (S_ISREG(st.st_mode)) {
            if (has_txt_ext_ci(ent->d_name)) total += count_lines_in_file(child);
        }
    }
    closedir(d);
    return total;
}

int main(void) {
    char dir[1001];
    printf("Enter directory path: ");
    if (!fgets(dir, sizeof(dir), stdin)) return 1;
    size_t len = strlen(dir);
    if (len && dir[len-1]=='\n') dir[len-1]='\0';

    long long total = walk_dir(dir);
    printf("Total .txt lines: %lld\n", total);
    return 0;
}
