#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

void print_time(time_t *t) {
    struct tm tm;
    localtime_r(t, &tm);
    printf("%04d %2d %02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    printf(" %02d:%02d", tm.tm_hour, tm.tm_min);
}

void print_stat(char *path) {
    struct stat st_buf;
    stat(path, &st_buf);
    // printf("st_dev: %d\n", st_buf.st_dev);
    // printf("st_ino: %llu\n", st_buf.st_ino);
    // printf("st_mode: %d\n", st_buf.st_mode);
    // printf("st_nlink: %d\n", st_buf.st_nlink);
    // printf("st_uid: %d\n", st_buf.st_uid);
    // printf("st_gid: %d\n", st_buf.st_gid);

    // printf("st_size: %lld\n", st_buf.st_size);
    printf("  %5lld  ", st_buf.st_size);

    // printf("st_blksize: %d\n", st_buf.st_blksize);
    // printf("st_blocks: %lld\n", st_buf.st_blocks);

    //printf("st_mtime: %ld\n", st_buf.st_mtime);
    print_time(&st_buf.st_mtime);
}

void ls(char *dname) {
    DIR *dir_ptr;
    struct dirent *direntp;

    dir_ptr = opendir(dname);
    if (dir_ptr == NULL) {
        printf("err\n");
    } else {
	    while ((direntp = readdir(dir_ptr)) != NULL) {
            if (!(strcmp(direntp->d_name, ".") && strcmp(direntp->d_name, "..")))
                continue;

            print_stat(direntp->d_name);
            printf(" %s\n", direntp->d_name);
        }
	    closedir(dir_ptr);
    }
}

int main() {
    ls(".");
    return 0;
}
