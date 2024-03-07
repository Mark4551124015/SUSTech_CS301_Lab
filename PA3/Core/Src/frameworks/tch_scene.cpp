#include <stdint.h>

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "framework.h"
#include "main.h"
#include "scene.h"

#define MAX_POINTS 50
#define MAX_LINES 5

extern uint8_t EVENT[32];
extern pii touch;
extern bool fly;

pair<pii, pii> tch_scene::getRange(pii p) {
    return {{p.x_p - good_range.x_p, p.y_p - good_range.y_p},
            {p.x_p + good_range.x_p, p.y_p + good_range.y_p}};
}

marker::marker(string name, pii pos, pii shape, char c)
    : dpo(name, pos, shape) {
    this->c = c;
    this->font_size = 12;
    this->font_color = BLACK;
    this->isVisible = false;
    this->backup = new uint16_t[shape.x_p * shape.y_p];
    this->need_render = false;
}

void marker::backup_lcd() {
    pii p1 = {this->my_axis.x_p - this->shape.x_p / 2,
              this->my_axis.y_p - this->shape.y_p / 2};
    pii p2 = {this->my_axis.x_p + this->shape.x_p / 2,
              this->my_axis.y_p + this->shape.y_p / 2};

    for (int i = p1.first; i < p2.first; i++) {
        for (int j = p1.second; j < p2.second; j++) {
            this->backup[(i - p1.first) * this->shape.y_p + j - p1.second] =
                LCD_BGR2RGB(LCD_ReadPoint(i, j));
        }
    }
}

void marker::restore_lcd() {
    pii p1 = {this->my_axis.x_p - this->shape.x_p / 2,
              this->my_axis.y_p - this->shape.y_p / 2};
    pii p2 = {this->my_axis.x_p + this->shape.x_p / 2,
              this->my_axis.y_p + this->shape.y_p / 2};

    for (int i = p1.first; i < p2.first; i++) {
        for (int j = p1.second; j < p2.second; j++) {
            LCD_Fast_DrawPoint(
                i, j,
                this->backup[(i - p1.first) * this->shape.y_p + j - p1.second]);
        }
    }
}

void marker::set(pii pos) {
    printf("[Marker] %s set %d, %d\n", this->name.c_str(), pos.x_p, pos.y_p);
    this->pos = pos;
    this->setVisbility(true);
}

void marker::remove() {
    this->restore_lcd();
    this->isVisible = false;
}

void marker::update(dpo *father, pii axis) {
    this->my_axis = adding(axis, this->pos);
    if (father != nullptr) {
    }
    pii p1 = {this->my_axis.x_p - this->shape.x_p / 2,
              this->my_axis.y_p - this->shape.y_p / 2};
    pii p2 = {this->my_axis.x_p + this->shape.x_p / 2,
              this->my_axis.y_p + this->shape.y_p / 2};

    if (this->need_render && this->isVisible) {
        POINT_COLOR = BLACK;
        pii start = {-this->font_size / 4, -this->font_size / 2};
        start = adding(start, this->my_axis);
        this->backup_lcd();
        LCD_Fill(p1.first, p1.second, p2.first - 1, p2.second - 1, LIGHTBLUE);
        BACK_COLOR = LIGHTBLUE;
        LCD_ShowChar(start.x_p, start.y_p, this->c, this->font_size, 1);
        // LCD_Draw_Circle(this->pos.first, this->pos.second, 7);
        LCD_DrawRectangle(p1.first, p1.second, p2.first - 1, p2.second - 1);
    }

    dpo::update(father, axis);
}

tch_canvas::tch_canvas(string name, pii pos, pii shape)
    : dpo(name, pos, shape) {
    this->answer = new pii[MAX_MARKER * 2];
    this->font_size = 24;
    this->click = false;
    this->touching = false;
    // this->p = new char[22];
    memcpy(this->pool, this->p, 60);
    this->str = new char[MAX_MARKER * 2];
    this->isVisible = false;
}

void tch_canvas::draw_points() {
    for (int i = 0; i < MAX_POINTS; i++) {
        pii rand_pos =
            randPII({-this->shape.x_p / 2 + 15, this->shape.x_p / 2 - 15},
                    {-this->shape.y_p / 2 + 15, this->shape.y_p / 2 - 15});
        rand_pos = adding(rand_pos, this->my_axis);
        uint16_t rand_color = rand() % 0xffff;
        LCD_Fill(rand_pos.x_p, rand_pos.y_p, rand_pos.x_p + 1, rand_pos.y_p + 1,
                 rand_color);
    }
}

void tch_canvas::draw_lines() {
    for (int i = 0; i < MAX_LINES; i++) {
        pii rand_pos1 =
            randPII({-this->shape.x_p / 2 + 15, this->shape.x_p / 2 - 15},
                    {-this->shape.y_p / 2 + 15, this->shape.y_p / 2 - 15});
        rand_pos1 = adding(rand_pos1, this->my_axis);
        pii rand_pos2 =
            randPII({-this->shape.x_p / 2 + 15, this->shape.x_p / 2 - 15},
                    {-this->shape.y_p / 2 + 15, this->shape.y_p / 2 - 15});
        rand_pos2 = adding(rand_pos2, this->my_axis);
        pii rand_pos3 =
            randPII({-this->shape.x_p / 2 + 15, this->shape.x_p / 2 - 15},
                    {-this->shape.y_p / 2 + 15, this->shape.y_p / 2 - 15});
        rand_pos3 = adding(rand_pos3, this->my_axis);
        uint16_t rand_color = rand() % 0xffff;
        POINT_COLOR = rand_color;
        LCD_DrawLine(rand_pos1.x_p, rand_pos1.y_p, rand_pos2.x_p,
                     rand_pos2.y_p);
        LCD_DrawLine(rand_pos2.x_p, rand_pos2.y_p, rand_pos3.x_p,
                     rand_pos3.y_p);
    }
}

void tch_canvas::reset() {
    printf("[Canvas] reset\n");
    random_shuffle(this->pool, this->pool + 60);
    printf("[Canvas] shuffled\n");
    for (int i = 0; i < MAX_MARKER + 2; i++) {
        this->answer[i] =
            randPII({-this->shape.x_p / 2 + 15, this->shape.x_p / 2 - 15},
                    {-this->shape.y_p / 2 + 15, this->shape.y_p / 2 - 15});
    }
    printf("[Canvas] inited answer\n");
    for (int i = 0; i < MAX_MARKER + 2; i++) {
        this->str[i] = this->pool[i];
    }
    printf("[Canvas] reseted\n");
}

void tch_canvas::update(dpo *father, pii axis) {
    this->my_axis = adding(axis, this->pos);
    pii p1 = {this->my_axis.x_p - this->shape.x_p / 2,
              this->my_axis.y_p - this->shape.y_p / 2};
    pii p2 = {this->my_axis.x_p + this->shape.x_p / 2,
              this->my_axis.y_p + this->shape.y_p / 2};
    if (father != nullptr) {
    }
    if (this->isVisible) {
        this->click = false;
        if (this->touching && fly) this->click = true;
        if (IN(p1, p2, touch)) {
            this->touching = true;
            this->click_pos =
                adding(touch, {-this->my_axis.first, -this->my_axis.second});
        } else
            this->touching = false;
    }

    if (this->click) {
        printf("[clicked] \"%s\"\n", this->name.c_str());
    }
    if (this->need_render && this->isVisible) {
        LCD_Fill(p1.first, p1.second, p2.first, p2.second, WHITE);
        LCD_DrawRectangle(p1.first, p1.second, p2.first, p2.second);
        for (int i = 0; i < MAX_MARKER + 2; i++) {
            pii pos = adding(this->my_axis, this->answer[i]);
            pos = adding(pos, {-this->font_size / 4, -this->font_size / 2});
            BACK_COLOR = WHITE;
            POINT_COLOR = rand() % 0xffff;
            uint16_t rand_angle = rand() % 360;
            LCD_ShowRotateChar(pos.x_p, pos.y_p, this->str[i], this->font_size,
                               rand_angle, 1);
        }
        this->draw_points();
        this->draw_lines();
    }
    dpo::update(father, axis);
}

bool tch_canvas::isClicked() { return this->click; }

tch_scene::tch_scene(string name, pii pos, pii shape) : dpo(name, pos, shape) {
    this->add_son(&this->confirm);
    this->add_son(&this->notice);
    this->add_son(&this->title);
    this->add_son(&this->canvas);
    this->add_son(&this->refresh);
    this->canvas.setVisbility(false);
    this->confirm.setVisbility(false);
    // this->title.setVisbility(false);
    this->markers = new marker[MAX_MARKER]{
        marker("Marker 1", {0, 0}, {16, 16}, '1'),
        marker("Marker 2", {0, 0}, {16, 16}, '2'),
        marker("Marker 3", {0, 0}, {16, 16}, '3'),
        marker("Marker 4", {0, 0}, {16, 16}, '4'),
    };
    for (int i = 0; i < MAX_MARKER; i++) {
        this->add_son(&this->markers[i]);
    }
    this->marker_cnt = 0;
}

void tch_scene::update(display_object *father, pii axis) {
    this->my_axis = adding(axis, this->pos);
    if (father != nullptr) {
    }

    if (this->isVisible) {
        if (this->need_render) {
            this->canvas.setVisbility(true);
            this->title.setVisbility(true);
        }
        if (this->canvas.isClicked()) {
            if (this->marker_cnt < MAX_MARKER) {
                pii pos = this->canvas.click_pos;
                printf("[Canvas] clicked %d, %d\n", pos.x_p, pos.y_p);
                this->markers[this->marker_cnt++].set(pos);
                if (this->marker_cnt == MAX_MARKER) {
                    this->confirm.setVisbility(true);
                    this->notice.clear();
                } else {
                    char *str = new char[30];
                    sprintf(str, "Please click: %c, %c, %c, %c",
                            this->canvas.str[0], this->canvas.str[1],
                            this->canvas.str[2], this->canvas.str[3]);
                    this->notice.update_str(str, 16, BLACK, WHITE);
                }
            }
        }
        if (EVENT[RETURN_BACK]) {
            if (this->marker_cnt > 0) {
                if (this->marker_cnt == MAX_MARKER) {
                    this->confirm.setVisbility(false);
                    this->title.setVisbility(true);
                }
                this->markers[--this->marker_cnt].remove();
            }
            EVENT[RETURN_BACK] = 0;
        }
        if (this->confirm.isClicked()) {
            printf("[Confirm] clicked\n");
            for (int i = 0; i < MAX_MARKER; i++) {
                printf("[Marker] %s %d, %d\n", this->markers[i].name.c_str(),
                       this->markers[i].pos.x_p, this->markers[i].pos.y_p);
                pii ans = this->canvas.answer[i];

                pair<pii, pii> range = this->getRange(ans);

                if (!IN(range.first, range.second, this->markers[i].pos)) {
                    printf("[Marker] %s wrong\n",
                           this->markers[i].name.c_str());
                    printf("range: %d, %d, %d, %d\n", range.first.x_p,
                           range.first.y_p, range.second.x_p, range.second.y_p);
                    printf("marker: %d, %d\n", this->markers[i].pos.x_p,
                           this->markers[i].pos.y_p);
                    this->reset();
                    this->need_render = true;
                    this->confirm.reset();
                    return;
                } else {
                    printf("[Marker] %s correct\n",
                           this->markers[i].name.c_str());
                }
            }
            this->confirm.reset();
            EVENT[FINISH_2] = 1;
        }
        if (this->refresh.isClicked()) {
            this->reset();
            this->need_render = true;
            this->refresh.reset();
        }
    }
    dpo::update(father, axis);
}

void tch_scene::reset() {
    this->confirm.setVisbility(false);
    this->canvas.setVisbility(true);
    this->refresh.setVisbility(true);
    this->canvas.reset();
    for (int i = this->marker_cnt - 1; i >= 0; i--) {
        printf("remove %d\n", i);
        this->markers[i].setVisbility(false);
    }
    printf("clear marks = 0\n");
    this->marker_cnt = 0;
    char *str = new char[30];
    printf("applied memory = 0\n");
    sprintf(str, "Please click: %c, %c, %c, %c", this->canvas.str[0],
            this->canvas.str[1], this->canvas.str[2], this->canvas.str[3]);
    printf("updating str\n");
    this->notice.update_str(str, 16, BLACK, WHITE);
    this->notice.setVisbility(true);
    this->title.setVisbility(true);
    printf("[TCH Scene]reseted\n");
}

finish_scene::finish_scene(string name, pii pos, pii shape)
    : dpo(name, pos, shape) {
    this->add_son(&this->notice);
    this->add_son(&this->title);
}
