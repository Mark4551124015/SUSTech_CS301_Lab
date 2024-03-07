#include "game.h"

#include <stdio.h>

#include <random>

#include "led.h"
#include "stm32f1xx.h"
#include "utils.h"

using namespace std;

int levels[] = {60, 120, 180};

extern LED leddev;
Game::Game() {
    // this->counter = 0;
    this->time_remains = 0;
    this->question_remains = 0;
    this->current_answer = 0;
}

void Game::Init() {
    this->question_remains = Default_Question_Cnt;
    this->current_answer = 0xffffffff;
    this->current_mode = mode_plus;
    this->current_state = waiting;
    this->level = 0;
    this->time_remains = levels[this->level];
}

void Game::tick() {
    if (this->current_state != playing) return;
    this->time_remains--;

    if (this->time_remains <= 0) {
        uart_print("[INFO] Time out! Please press KEY0 to try again.\r\n");
        this->current_state = lose;
        return;
    }
    if (this->time_remains <= 10) {
        char *output = new char[100];
        sprintf(output, "[Warning] %d second left!\r\n", this->time_remains);
        uart_print(output);
        leddev.append(BLINK_1);
    }
}

Game::state Game::get_game_state() { return this->current_state; }

void Game::update_time() {
    this->level = (this->level + 1) % 3;
    this->time_remains = levels[this->level];
}

void Game::set_question_cnt(int cnt) { this->question_remains = cnt; }

void Game::add_question_cnt(int cnt) { this->question_remains += cnt; }

void Game::generate_question() {
    if (this->current_state != playing) return;
    srand(HAL_GetTick());
    char *out = new char[100];
    int a = rand() % 100;
    int b = rand() % 100;

    switch (this->current_mode) {
        case mode_plus:
            if (a > b) {
                a -= b;
            } else {
                b -= a;
            }
            sprintf(out, "[INFO] %d + %d = ?\r\n", a, b);
            this->current_answer = a + b;
            break;
        case mode_minus:

            if (a < b) swap(a, b);
            sprintf(out, "[INFO] %d - %d = ?\r\n", a, b);
            this->current_answer = a - b;
            break;
        case mode_multiply:
            a %= 10;
            b %= 10;
            a++, b++;
            sprintf(out, "[INFO] %d * %d = ?\r\n", a, b);
            this->current_answer = a * b;
            break;
        case mode_divide:
            a %= 10;
            b %= 10;
            a++, b++;
            sprintf(out, "[INFO] %d / %d = ?\r\n", a * b, b);
            this->current_answer = a;
            break;
        default:
            break;
    }
    uart_print(out);
}
bool Game::answer_question(const char *answer) {
    if (this->current_state != playing) return false;
    int ans = atoi(answer);
    char *output = new char[100];
    // sprintf(output, "[INFO] Your answer is %d\r\n", ans);
    // uart_print(output);
    if (abs(ans - this->current_answer) < eps) {
        this->question_remains--;
        uart_print("[INFO] True! Do a good job!\r\n");
        sprintf(output, "[INFO] %d problem remains!\r\n\r\n",
                this->question_remains);
        uart_print(output);
        leddev.append(BLINK_1);
        if (this->question_remains == 0) {
            this->current_state = win;
            for (int i = 0; i < 10; i++) leddev.append(BLINK_BOTH_TWICE);
            uart_print(
                "[INFO] You pass the practice! Please press KEY0 to try "
                "again\r\n");
        }
        this->generate_question();
        return true;
    }
    leddev.append(BLINK_0);
    uart_print("[INFO] Wrong! Please try again, one more problem added!\r\n");

    this->add_question_cnt(Panalty);
    sprintf(output, "[INFO] %d problem remains!\r\n\r\n", this->question_remains);
    uart_print(output);
    this->generate_question();

    return false;
}

void Game::update_mode() { this->current_mode = (this->current_mode + 1) % 4; }