#include "characteristics.h"

off_t get_file_size(char *file_name, int *fd) {
    struct stat statbuf;
    memset(&statbuf, 0, sizeof(struct stat));

    *fd = open(file_name, O_RDONLY);

    if (*fd == -1){
        printf("Error occurred while opening file %s: %d\n", file_name, errno);
        exit(1);
    }

    int err = fstat(*fd, &statbuf);
    if (err == -1){
        printf("Error occurred reading file %s: %d\n", file_name, errno);
        exit(1);
    }

    return statbuf.st_size;
}