#include "lzss.h"

int main(int argc, char **argv){
    if (argc != 2) {
        printf("Usage:\n");
        printf("%s <target_file_path>\n", argv[0]);
    }
    
    o_file *file_content = read_file(argv[1]);
    // puts(file_content->buffer);
    lzss(file_content);

    destroy_file(file_content);
    return 0;
}