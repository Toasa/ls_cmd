#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

void print_time(time_t *t) {
    struct tm tm;
    localtime_r(t, &tm);
    printf("%2d %02d", tm.tm_mon + 1, tm.tm_mday);
    printf(" %02d:%02d", tm.tm_hour, tm.tm_min);
}

void print_perm(int p, char c) {
    if (p) {
        printf("%c", c);
    } else {
        printf("-");
    }
}

void print_type_perm(mode_t mt) {
    if (mt & S_IFDIR) {
        printf("d");
    } else if (mt & S_IFREG) {
        printf("-");
    } else if (mt & S_IFLNK) {
        printf("l");
    } else if (mt & S_IFBLK) {
        printf("b");
    } else if (mt & S_IFCHR) {
        printf("c");
    }

    print_perm(mt & S_IRUSR, 'r');
    print_perm(mt & S_IWUSR, 'w');
    print_perm(mt & S_IXUSR, 'x');
    print_perm(mt & S_IRGRP, 'r');
    print_perm(mt & S_IWGRP, 'w');
    print_perm(mt & S_IXGRP, 'x');
    print_perm(mt & S_IROTH, 'r');
    print_perm(mt & S_IWOTH, 'w');
    print_perm(mt & S_IXOTH, 'x');

}

void print_stat(char *path) {
    struct stat st_buf;
    stat(path, &st_buf);
    // printf("st_dev: %d\n", st_buf.st_dev);
    // printf("st_ino: %llu\n", st_buf.st_ino);
    print_type_perm(st_buf.st_mode);
    printf("%3d", st_buf.st_nlink);
    printf(" %5d", st_buf.st_uid);
    printf("     %5d", st_buf.st_gid);
    printf(" %5lld ", st_buf.st_size);
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
