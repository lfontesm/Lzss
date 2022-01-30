#include "lzss.h"

int main(int argc, char **argv){
    if (argc != 2) {
        printf("Usage:\n");
        printf("%s <target_file_path>\n", argv[0]);
    }
    
    o_file *file_content = read_file(argv[1]);
    char *compressed_buffer = lzss(file_content);
    puts(compressed_buffer);

    destroy_file(file_content);
    free(compressed_buffer);
    return 0;
}