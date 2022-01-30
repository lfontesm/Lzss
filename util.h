#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#if !defined(UTIL_H_)
#define UTIL_H_

typedef struct {
    char *buffer;
    size_t buf_size;
    size_t offset;
    int fd;
} o_file;

o_file *read_file(char *file_name);
int elem(char c, char *buf);
void strapnd(char *buf, char c);
void strshl(char *buf, int p);
o_file *open_file(char *file_name);
void destroy_file(o_file *f);

#endif // UTIL_H_
