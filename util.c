#include "util.h"

char *replace(char *s, char t, char r) {
    while (*s++)
        if (*s == t){
            *s = r;
            return s;
        }
    return s;
}

int elem(char c, char *buf) {
    for (int i = 0; i < strlen(buf); i++) {
        if (buf[i] == c)
            return i;
    }
    return -1;
}

void strapnd(char *buf, char c) {
    while (*buf++);
    *--buf = c;
}

void strshl(char *buf, int p) {
    int buf_len = strlen(buf);
    // char last_c = buf[buf_len - 1];

    for (int i = p; i<buf_len-1; i++) {
        buf[p] = buf[p+1];
    }
}

char *read_file(char *file_name) {
    int fd;

    off_t tgt_file_size = get_file_size(file_name, &fd);
    ssize_t bytes_read;

    char *file_content = malloc(tgt_file_size);
    if (!file_content){
        perror("Failed to allocate space for reading target file\n");
        exit(1);
    }
    bytes_read = read(fd, file_content, tgt_file_size);
    if (bytes_read == -1) {
        perror("Failed to read target file");
        exit(1);
    }
    replace(file_content, '\n', '\0');
    close(fd);

    return file_content;
}