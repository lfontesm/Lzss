#include "lzss.h"

#define MAX_SLIDING_WINDOW_SIZE 4096

typedef struct {
    char *buf;
    int initial_pos;
    int current_pos;
    int size;
} sliding_window;

int elements_in_array(char *check_elements, char *elements, int filter_last_char) {
    int offset = 0;
    int chk_len;
    if (filter_last_char)
        chk_len = strlen(check_elements) - 1;
    else
        chk_len = strlen(check_elements);
    for (int i = 0; i < strlen(elements); i++) {
        if (chk_len <= offset) 
            return i - chk_len;

        if (check_elements[offset] == elements[i])
            offset++;
        else
            offset = 0;
    }
    return -1;
}

char *lzss(char *buf){
    ssize_t buf_len = strlen(buf) + 1;
    char *search_buf = malloc(buf_len);
    char *check_characters = malloc(buf_len);
    memset(search_buf, 0, buf_len);
    memset(check_characters, 0, buf_len);
    // size_t search_buf_size = 3;
    int pos, offset;
    for (int i = 0; i < buf_len; i++) {
        strapnd(check_characters, buf[i]);
        size_t len_chk_char = strlen(check_characters);
        pos = elements_in_array(check_characters, search_buf, 0);
        // printf("ihu %d\n", pos);
        
        if (pos == -1 || i == (buf_len - 1)) {
            if (len_chk_char > 1) {
                pos = elements_in_array(check_characters, search_buf, 1);
                offset = i - pos - len_chk_char + 1;
                int length = len_chk_char;

                char token[20];
                int tok_len = sprintf(token, "<%d, %d>", offset, length);

                if (tok_len > length)
                    printf("%s\n", check_characters);
                else
                    puts(token);
                
            }
            else
                printf("%c\n", buf[i]);
            memset(check_characters, 0, buf_len);
        }
        
        search_buf[i] = buf[i];
        
        if (strlen(search_buf) > MAX_SLIDING_WINDOW_SIZE)
            strshl(search_buf, 0);
    }

    // puts(search_buf);
    free(search_buf);
    free(check_characters);
    return buf;
}