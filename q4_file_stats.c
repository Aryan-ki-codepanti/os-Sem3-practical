#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Invalid arguments entered\n");
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    struct stat stats;

    if (fstat(fd, &stats) == -1)
    {
        printf("Error while getting the file\n");
        return -1;
    }

    printf("User id : %d\n", stats.st_uid);
    printf("Group id : %d\n", stats.st_gid);
    printf("Dev id : %ld\n", (unsigned long int)(stats.st_dev));
    printf("Last access time : %s\n", ctime(&stats.st_atime));

    printf("Size : %ld\n", (unsigned long int)(stats.st_size));

    printf("Mode : %d\n", stats.st_mode);
    printf("Octal Mode : %o\n", stats.st_mode);

    int mode = stats.st_mode;

    // Permissions
    // Owner
    printf("\nPermissions\n");
    printf("Owner : %c%c%c\n", (mode & S_IRUSR ? 'r' : '-'), (mode & S_IWUSR ? 'w' : '-'), (mode & S_IXUSR ? 'x' : '-'));
    // Group
    printf("Group : %c%c%c\n", (mode & S_IRGRP ? 'r' : '-'), (mode & S_IWGRP ? 'w' : '-'), (mode & S_IXGRP ? 'x' : '-'));
    // Other
    printf("Other : %c%c%c\n", (mode & S_IROTH ? 'r' : '-'), (mode & S_IWOTH ? 'w' : '-'), (mode & S_IXOTH ? 'x' : '-'));

    return 0;
}