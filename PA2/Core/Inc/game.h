#ifndef __GAME_H
#define __GAME_H

#include "stdlib.h"
#include <queue>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus  // 使用C语言的方式编译方法名。
extern "C" {
#endif

#define Default_Question_Cnt 5
#define Panalty 1
#define eps 1e-6
#define mode_plus 0
#define mode_minus 1
#define mode_multiply 2
#define mode_divide 3



class Game {
   public:
    // int counter;
    int time_remains;
    int question_remains;
    int current_answer;
    // enum mode {plus, minus, multiply, divide};
    enum state {waiting, win, lose, playing};
    int current_mode;
    int level;
    state current_state;
   public:
    void Init();
    void update_time();
    void set_question_cnt(int cnt);
    void add_question_cnt(int cnt);
    void generate_question();
    bool answer_question(const char *answer);
    void tick();
    state get_game_state();
    void update_mode();
    Game();
};


#ifdef __cplusplus  // 使用C语言的方式编译方法名。
}
#endif
#endif
