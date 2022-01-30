#include "lzss.h"

#define MAX_SLIDING_WINDOW_SIZE 4096
#define MIN_CHAR_PER_TOKEN_SIZE 3
#define MAX_MATCHING_LENGTH 5

// TODO: Try to implement a minimum lenght for a token

typedef struct {
    size_t size;
    size_t init;
    size_t currently_matched;
    size_t offset;
} sliding_window;

void iter_window(char *buf, char *out_buf, sliding_window *s_w, int len, int *pos) {
    s_w->currently_matched = 0;
    s_w->offset=0;
    
    for (int i = s_w->init; ((i < *pos - 1) && (s_w->size > *pos - s_w->init)); i++){
        int fin = 0;
        if (buf[i] == buf[*pos]){
            fin = 1;
            s_w->currently_matched++;
            int aux_pos = *pos + 1;
            for (int j = i+1; j < *pos; j++){
                if (buf[j] != buf[aux_pos]){
                    break;
                }
                aux_pos++;
                s_w->currently_matched++;
                s_w->offset++;
            }
            if (fin && s_w->currently_matched > MIN_CHAR_PER_TOKEN_SIZE) {
                off_t offset = *pos - i;
                *pos = aux_pos;
                sprintf(out_buf + strlen(out_buf), "<%ld, %ld>", offset, s_w->currently_matched);
                return;
            }
        }
        s_w->offset++;
        s_w->currently_matched = 0;
    }

}

char *lzss(o_file *f){
    ssize_t buf_len = f->buf_size + 1;
    char *out_buf = malloc(buf_len * 2);
    memset(out_buf, 0, buf_len*2);
    sliding_window s_w = {.init=0, .offset=0, .currently_matched=0, .size=MAX_SLIDING_WINDOW_SIZE};

    for (int i=0; i<buf_len;i++) {

        iter_window(f->buffer, out_buf, &s_w, f->buf_size, &i);
        strapnd(out_buf, f->buffer[i]);
        if ((i + s_w.init) >= s_w.size)
            s_w.init++;
    }
    return out_buf;
}