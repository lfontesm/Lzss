#include "lzss.h"

int main(int argc, char **argv){
    if (argc != 2) {
        printf("Usage:\n");
        printf("%s <target_file_path>\n", argv[0]);
    }
    
    char *file_content = read_file(argv[1]);
    // puts(file_content);
    lzss(file_content);
    free(file_content);
    return 0;
}