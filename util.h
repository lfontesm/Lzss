#include "characteristics.h"

#if !defined(UTIL_H_)
#define UTIL_H_

char *read_file(char *file_name);
int elem(char c, char *buf);
void strapnd(char *buf, char c);
void strshl(char *buf, int p);



#endif // UTIL_H_
