#ifndef __HAFFMAN
#define __HAFFMAN

#include <ctype.h>
#include <led.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus  // 使用C语言的方式编译方法名。
extern "C" {
#endif

typedef struct huffman {
    char letter;
    int l, r;
} hfm;

const int root = 1;

void HUFFMAN_Init();
bool decode_hfm(char *str, char *out, int max_len);
bool encode_hfm(char *str, char *out, int max_len);
bool encode_single_hfm(char str, char *out);

#ifdef __cplusplus  // 使用C语言的方式编译方法名。
}
#endif
#endif
