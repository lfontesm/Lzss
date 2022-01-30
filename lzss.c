#include "lzss.h"

#define MAX_SLIDING_WINDOW_SIZE 4096

typedef struct {
    size_t size;
    size_t init;
    size_t currently_matched;
    size_t offset;
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

void iter_window(sliding_window *s_w, char *buf, int len, int *pos){
    s_w->currently_matched = 0;
    s_w->offset=0;
    int fin = 0;
    // char current_char = buf[*pos];
    
    for (int i = s_w->init; i < *pos - 1; i++){
        if (buf[i] == buf[*pos]){
            s_w->currently_matched++;
            printf("FOUND AT %ld \\/\n", s_w->offset);
            int aux_pos = *pos + 1;
            // return;
            for (int j = i+1; j < *pos; j++){
                if (buf[j] != buf[aux_pos]){
                    break;
                }
                fin = 1;
                aux_pos++;
                s_w->currently_matched++;
                s_w->offset++;
                printf("BUT WAIT, THERES MORE\n");
            }
            if (fin) {
                char token[14];
                off_t offset = *pos - s_w->init;
                *pos = aux_pos;
                sprintf(token, "<%ld, %ld>", offset, s_w->currently_matched);
                puts(token);
            }
        }
        s_w->offset++;
    }
}

char *lzss(o_file *f){
    ssize_t buf_len = f->buf_size + 1;
    sliding_window s_w = {.init=0, .offset=0, .currently_matched=0, .size=4096};

    for (int i=0; i<buf_len;i++) {
        iter_window(&s_w, f->buffer, f->buf_size, &i);
        printf("%c\n", f->buffer[i]);
        if ((i + s_w.init) >= s_w.size)
            s_w.init++;
    }
    return "a";
    
}