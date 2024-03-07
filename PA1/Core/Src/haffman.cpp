#include <haffman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
hfm g[128];

int cnt = 1;
extern LED leddev;
const char *huffman_code[26] = {
    "000",         // A
    "101001",      // B
    "00101",       // C
    "11011",       // D
    "011",         // E
    "01000",       // F
    "001001",      // G
    "0011",        // H
    "1100",        // I
    "00100011",    // J
    "0010000",     // K
    "11010",       // L
    "01001",       // M
    "1011",        // N
    "1110",        // O
    "101011",      // P
    "0010001001",  // Q
    "0101",        // R
    "1000",        // S
    "1111",        // T
    "10011",       // U
    "101000",      // V
    "101010",      // W
    "001000101",   // X
    "10010",       // Y
    "0010001000"   // Z
};

void HUFFMAN_Init() {
    g[root].letter = 0;
    cnt++;
    for (int i = 0; i < 26; i++) {
        int node = root;
        for (int j = 0; j < strlen(huffman_code[i]); j++) {
            char c = huffman_code[i][j];
            if (c == '0') {
                if (g[node].l == 0) {
                    g[node].l = cnt;
                    cnt++;
                }
                node = g[node].l;
            } else {
                if (g[node].r == 0) {
                    g[node].r = cnt;
                    cnt++;
                }
                node = g[node].r;
            }
        }
        g[node].letter = ('a' + i);
    }
    // for (int i = 0; i < cnt; i++) {
    //     printf("node: %c, %d, %d\n", g[i].letter, g[i].l, g[i].r);
    // }
    printf("HAFFMAN Inited\n");
}

bool decode_hfm(char *str, char *out, int max_len) {
    int node = root;
    out[0] = 0;
    int out_len = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] == '0') {
            node = g[node].l;
            leddev.append(BLINK_0);
        } else {
            node = g[node].r;
            leddev.append(BLINK_1);
        }
        if (g[node].letter != 0) {
            printf("%c\n", g[node].letter);
            out[out_len++] = g[node].letter;
            node = root;
            leddev.append(BLINK_BOTH_TWICE);
        }
        if (out_len >= max_len) break;
        if (node == 0) break;
    }
    if (node == root) return true;
    leddev.append(ERROR_DECODE);
    return false;
}

bool encode_hfm(char *str, char *out, int max_len) {
    int len = strlen(str);
    out[0] = 0;
    int out_len = 0;
    int index;
    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (c == ' ') continue;
        if (!isalpha(c)) {
            leddev.append(ERROR_ENCODE);
            return false;
        }
        index = tolower(c) - 'a';
        strcat(out, huffman_code[index]);
        for (int j = 0; j < strlen(huffman_code[index]); j++) {
            if (huffman_code[index][j] == '0') {
                leddev.append(BLINK_0);
            } else {
                leddev.append(BLINK_1);
            }
        }
        leddev.append(BLINK_BOTH_TWICE);
        out_len = strlen(out);
        if (out_len >= max_len) {
            leddev.append(ERROR_ENCODE);
            return false;
        }
    }
    return true;
}

bool encode_single_hfm(char str, char *out) {
    char c = str;
    out[0] = 0;
    int out_len = 0;
    int index;
    if (c == ' ') return true;
    if (!isalpha(c)) return false;
    index = tolower(c) - 'a';
    strcpy(out, huffman_code[index]);
    for (int i = 0; i < strlen(out); i++) {
        if (out[i] == '0') leddev.append(BLINK_0);
        if (out[i] == '1') leddev.append(BLINK_1);
    }
    leddev.append(BLINK_BOTH_TWICE);

    return true;
}