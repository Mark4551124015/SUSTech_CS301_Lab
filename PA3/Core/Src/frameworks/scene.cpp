#include "scene.h"

#include <cstdint>
#include <cstdio>

#include "main.h"

extern unsigned char IMAGE_back[9448];
extern uint8_t EVENT[32];

bar::bar(string name, pii pos, pii shape) : dpo(name, pos, shape) {
    // back.img = (unsigned short*)IMAGE_back;
    this->back.font_size = 24;
    this->home.font_size = 24;
    this->add_son(&this->back);
    this->add_son(&this->home);
    back.backgroud = GRAY;
    home.backgroud = GRAY;
}

void bar::update(display_object *father, pii axis) {
    if (this->back.isClicked()) EVENT[RETURN_BACK] = 1;
    if (this->home.isClicked()) EVENT[RETURN_HOME] = 1;
    dpo::update(father, axis);
}

main_menu::main_menu(string name, pii pos, pii shape) : dpo(name, pos, shape) {
    this->add_son(&this->title);
    this->add_son(&this->start);
}

void main_menu::update(display_object *father, pii axis) {
    dpo::update(father, axis);
    EVENT[START_GAME] = this->start.isClicked();
}

void main_menu::reset() {}