#include "util.h"

void strapnd(char *buf, char c) {
    while (*buf++);
    *--buf = c;
}

o_file *open_file(char *file_name) {
    o_file *file = malloc(sizeof(o_file));
    if (!file) {
        perror("Failed to allocate space for reading file");
        exit(1);
    }
    struct stat statbuf;
    memset(&statbuf, 0, sizeof(struct stat));

    file->fd = open(file_name, O_RDONLY);

    if (file->fd == -1)  {
        printf("Error occurred while opening file %s: %d\n", file_name, errno);
        exit(1);
    }

    int err = fstat(file->fd, &statbuf);
    if (err == -1){
        printf("Error occurred reading file %s: %d\n", file_name, errno);
        exit(1);
    }

    file->buf_size = statbuf.st_size;
    file->offset = 0;

    return file;
}

o_file *read_file(char *file_name) {
    o_file *f= open_file(file_name);
    size_t tgt_file_size = f->buf_size;;
    ssize_t bytes_read;

    f->buffer = malloc(tgt_file_size + 1);
    memset(f->buffer, 0, tgt_file_size + 1);
    if (!f->buffer){
        perror("Failed to allocate space for reading target file\n");
        exit(1);
    }
    bytes_read = read(f->fd, f->buffer, tgt_file_size);
    if (bytes_read == -1) {
        perror("Failed to read target file");
        exit(1);
    }
    // replace(f->buffer, '\n', '\0');

    return f;
}

void destroy_file(o_file *f) {
    close(f->fd);
    if (f->buffer)
        free(f->buffer);
    free(f);
}