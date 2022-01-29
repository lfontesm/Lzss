#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#if !defined(CHARS_H)
#define CHARS_H

off_t get_file_size(char *file_name, int *fd);

#endif // CHARS_H
