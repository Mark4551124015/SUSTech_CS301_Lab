#include <stdint.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iterator>

#include "framework.h"
#include "images.h"
#include "main.h"
#include "scene.h"

extern uint8_t EVENT[32];
const pii mask_size = {30, 30};
const pii good_range = {5, 5};
const pii bad_range = {1, 1};
extern pii touch;
extern bool fly;
bool last_fly;
extern size_t timer;

pair<pii, pii> getRange(pii p, const pii range) {
    return {{p.x_p - range.x_p, p.y_p - range.y_p},
            {p.x_p + range.x_p, p.y_p + range.y_p}};
}

bool valid(pii touch) {
    if (touch.x_p >= 240 or touch.y_p >= 360) return false;
    if (touch.x_p < 0 or touch.y_p < 0) return false;
    return true;
}
mov_img::moving_image(string name, pii pos, pii shape,
                      const unsigned short *img, pii image_shape,
                      pii corp_start)
    : dpo(name, pos, shape) {
    this->corp_start = corp_start;
    this->image_shape = image_shape;
    this->last_pos = this->pos;
    this->last_touch = touch;
    this->backup = new uint16_t[shape.x_p * shape.y_p];
    this->dragging = false;
    last_fly = true;
    this->touching = false;

    this->img = img;
}

void mov_img::backup_lcd() {
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

void mov_img::restore_lcd() {
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
void mov_img::update(dpo *father, pii axis) {
    this->my_axis = adding(axis, this->pos);
    pii old_axis = adding(axis, this->last_pos);
    static pii last_updated_pos = this->pos;
    if (father != nullptr) {
    }
    pii p1 = {this->my_axis.x_p - this->shape.x_p / 2,
              this->my_axis.y_p - this->shape.y_p / 2};
    pii p2 = {this->my_axis.x_p + this->shape.x_p / 2,
              this->my_axis.y_p + this->shape.y_p / 2};

    if (this->isVisible) {
        if (IN(p1, p2, touch))
            this->touching = true;
        else
            this->touching = false;

        if (this->touching && last_fly) {
            this->dragging = true;
        } else if (fly) {
            this->dragging = false;
        }
        pii father_p1 = {axis.x_p - father->shape.x_p / 2,
                         axis.y_p - father->shape.y_p / 2};

        pii father_p2 = {axis.x_p + father->shape.x_p / 2,
                         axis.y_p + father->shape.y_p / 2};

        if (this->dragging && valid(touch) &&
            IN(adding(father_p1, {this->shape.x_p / 2, this->shape.y_p / 2}),
               adding(father_p2,
                      {-this->shape.x_p / 2 - 1, -this->shape.y_p / 2 - 1}),
               touch)) {
            pii newpos = {touch.x_p - axis.x_p, touch.y_p - axis.y_p};
            if (newpos != this->pos && dist(last_updated_pos, newpos) > 2) {
                last_updated_pos = newpos;
                this->restore_lcd();
                this->pos = newpos;
                this->my_axis = adding(axis, this->pos);
                this->backup_lcd();
                p1 = {this->my_axis.x_p - this->shape.x_p / 2,
                      this->my_axis.y_p - this->shape.y_p / 2};
                p2 = {this->my_axis.x_p + this->shape.x_p / 2,
                      this->my_axis.y_p + this->shape.y_p / 2};

                LCD_ShowPic_Part(p1.x_p, p1.y_p, this->image_shape.x_p,
                                 this->image_shape.y_p, this->corp_start.x_p,
                                 this->corp_start.y_p,
                                 this->corp_start.x_p + this->shape.x_p,
                                 this->corp_start.y_p + this->shape.y_p,
                                 this->img);
            }
        }
        // pii p1 = {this->my_axis.x_p - this->shape.x_p / 2,
        //           this->my_axis.y_p - this->shape.y_p / 2};
        // pii p2 = {this->my_axis.x_p + this->shape.x_p / 2,
        //           this->my_axis.y_p + this->shape.y_p / 2};

        // pii p1_o = {old_axis.x_p - this->shape.x_p / 2,
        //             old_axis.y_p - this->shape.y_p / 2};
        // pii p2_o = {old_axis.x_p + this->shape.x_p / 2,
        //             old_axis.y_p + this->shape.y_p / 2};
    }
    if (this->need_render && this->isVisible) {
        POINT_COLOR = BLACK;
        this->backup_lcd();
        LCD_ShowPic_Part(p1.x_p, p1.y_p, this->image_shape.x_p,
                         this->image_shape.y_p, this->corp_start.x_p,
                         this->corp_start.y_p,
                         this->corp_start.x_p + this->shape.x_p,
                         this->corp_start.y_p + this->shape.y_p, this->img);
    }
    last_touch = {touch.x_p, touch.y_p};
    this->last_pos = {this->pos.x_p, this->pos.y_p};
    last_fly = fly;
    
    dpo::update(father, axis);
}

sld::slide_validation(string name, pii pos, pii shape) : dpo(name, pos, shape) {
    this->img.img = (unsigned short *)IMG_RICK_ROLL;
    this->small_img.img = (unsigned short *)IMG_RICK_ROLL;
    pii goodP1 = {-this->img.shape.x_p / 2 + mask_size.x_p,
                  this->img.shape.x_p / 2 - mask_size.x_p};
    pii goodP2 = {-this->img.shape.y_p / 2 + mask_size.y_p,
                  this->img.shape.y_p / 2 - mask_size.y_p};
    this->mask.pos = randPII(goodP1, goodP2);
    printf("%d %d\n", this->mask.pos.x_p, this->mask.pos.y_p);
    // this->mask.pos = {0, 0};
    this->answer = getRange(this->mask.pos, good_range);

    this->add_son(&this->img);
    this->add_son(&this->title);
    this->img.add_son(&this->mask);
    this->img.add_son(&this->small_img);
    this->add_son(&this->never_gonna_give_you_up);
    this->add_son(&this->never_gonna_let_you_down);
    this->add_son(&this->never_gonna_run_around);
    this->add_son(&this->and_desert_you);
    this->add_son(&this->never_gonna_make_you_cry);
    this->add_son(&this->never_gonna_say_goodbye);
    this->add_son(&this->never_gonna_tell_a_lie);
    this->add_son(&this->and_hurt_you);
    this->add_son(&this->confirm);
    this->never_gonna_give_you_up.setVisbility(false);
    this->never_gonna_let_you_down.setVisbility(false);
    this->never_gonna_run_around.setVisbility(false);
    this->and_desert_you.setVisbility(false);
    this->never_gonna_make_you_cry.setVisbility(false);
    this->never_gonna_say_goodbye.setVisbility(false);
    this->never_gonna_tell_a_lie.setVisbility(false);
    this->and_hurt_you.setVisbility(false);
    this->confirm.setVisbility(false);
}

void sld::update(display_object *father, pii axis) {
    this->my_axis = adding(axis, this->pos);
    pii goodP1 = {-this->img.shape.x_p / 2 + mask_size.x_p,
                  this->img.shape.x_p / 2 - mask_size.x_p};
    pii goodP2 = {-this->img.shape.y_p / 2 + mask_size.y_p,
                  this->img.shape.y_p / 2 - mask_size.y_p};
    if (father != nullptr) {
    }
    if (IN(this->answer.first, this->answer.second, this->small_img.pos) &&
        fly) {
        pair<pii, pii> robot = getRange(this->mask.pos, bad_range);
        if (IN(robot.first, robot.second, this->small_img.pos)) {
            EVENT[RETURN_HOME] = 1;
            return;
        } else if (timer <= 1000) {
            EVENT[RETURN_HOME] = 1;
            return;
        } else if (rick_roll > 0) {
            this->mask.pos = randPII(goodP1, goodP2);
            this->answer = getRange(this->mask.pos, good_range);
            pii start = {this->img.shape.x_p / 2 - this->mask.shape.x_p / 2,
                         this->img.shape.y_p / 2 - this->mask.shape.y_p / 2};
            this->small_img.corp_start = adding(this->mask.pos, start);
            this->img.need_render = true;
            rick_roll--;
            switch (rick_roll) {
                case 3:
                    this->never_gonna_give_you_up.setVisbility(true);
                    this->never_gonna_let_you_down.setVisbility(true);
                    this->never_gonna_give_you_up.need_render = true;
                    this->never_gonna_let_you_down.need_render = true;
                    break;
                case 2:
                    this->never_gonna_give_you_up.clear();
                    this->never_gonna_let_you_down.clear();
                    this->never_gonna_run_around.setVisbility(true);
                    this->and_desert_you.setVisbility(true);
                    this->never_gonna_run_around.need_render = true;
                    this->and_desert_you.need_render = true;
                    break;
                case 1:
                    this->never_gonna_run_around.clear();
                    this->and_desert_you.clear();
                    this->never_gonna_make_you_cry.setVisbility(true);
                    this->never_gonna_say_goodbye.setVisbility(true);
                    this->never_gonna_make_you_cry.need_render = true;
                    this->never_gonna_say_goodbye.need_render = true;
                    break;
                case 0:
                    this->never_gonna_make_you_cry.clear();
                    this->never_gonna_say_goodbye.clear();
                    this->never_gonna_tell_a_lie.setVisbility(true);
                    this->and_hurt_you.setVisbility(true);
                    this->never_gonna_tell_a_lie.need_render = true;
                    this->and_hurt_you.need_render = true;
                    break;
            }
            timer = 0;
        } else if (!this->confirm.getVisbility()) {
            this->never_gonna_tell_a_lie.clear();
            this->and_hurt_you.clear();
            this->mask.isVisible = false;
            this->small_img.isVisible = false;
            this->img.need_render = true;
            this->confirm.setVisbility(true);
        }
    }
    if (EVENT[RETURN_BACK]) {
        this->reset();
        EVENT[RETURN_BACK] = 0;
        return;
    }
    if (confirm.isClicked()) {
        EVENT[FINISH_1] = 1;
        confirm.reset();
    }
    dpo::update(father, axis);
}

void sld::reset() {
    this->never_gonna_give_you_up.clear();
    this->never_gonna_let_you_down.clear();
    this->never_gonna_run_around.clear();
    this->and_desert_you.clear();
    this->never_gonna_make_you_cry.clear();
    this->never_gonna_say_goodbye.clear();
    this->never_gonna_tell_a_lie.clear();
    this->and_hurt_you.clear();
    this->never_gonna_give_you_up.setVisbility(false);
    this->never_gonna_let_you_down.setVisbility(false);
    this->never_gonna_run_around.setVisbility(false);
    this->and_desert_you.setVisbility(false);
    this->never_gonna_make_you_cry.setVisbility(false);
    this->never_gonna_say_goodbye.setVisbility(false);
    this->never_gonna_tell_a_lie.setVisbility(false);
    this->and_hurt_you.setVisbility(false);
    this->confirm.setVisbility(false);
    this->mask.isVisible = true;
    this->small_img.isVisible = true;
    this->rick_roll = 4;
    pii goodP1 = {-this->img.shape.x_p / 2 + mask_size.x_p,
                  this->img.shape.x_p / 2 - mask_size.x_p};
    pii goodP2 = {-this->img.shape.y_p / 2 + mask_size.y_p,
                  this->img.shape.y_p / 2 - mask_size.y_p};
    this->mask.pos = randPII(goodP1, goodP2);
    this->answer = getRange(this->mask.pos, good_range);
    this->small_img.pos = {0, 0};
    pii start = {this->img.shape.x_p / 2 - this->mask.shape.x_p / 2,
                 this->img.shape.y_p / 2 - this->mask.shape.y_p / 2};
    this->small_img.corp_start = adding(this->mask.pos, start);
    this->need_render = true;
    timer = 0;
}
