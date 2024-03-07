#ifndef __SCENE_H
#define __SCENE_H

#include <cstddef>
#include <cstdint>
#include <set>
#include <utility>
#include <vector>

#include "framework.h"

#ifdef __cplusplus  // 使用C语言的方式编译方法名。
extern "C" {
#endif

#define MAX_MARKER 4

typedef class bar : public dpo {
   public:
    bar(string name, pii pos, pii shape);
    button back = button("return", {-60, 0}, {120, 40}, "BACK");
    button home = button("home", {60, 0}, {120, 40}, "HOME");
    void update(display_object *father, pii axis);
    dpo_type type = BAR;
} bar;

typedef class slide_validation : public dpo {
   public:
    slide_validation(string name, pii pos, pii shape);
    void update(display_object *father, pii axis);
    image img = image("Origin", {0, 0}, {231, 130}, NULL, "");
    mov_img small_img =
        mov_img("Corped", {-20, 0}, {30, 30}, NULL, {231, 130}, {100, 30});
    rectangle mask = rectangle("Mask", {0, 0}, {30, 30}, WHITE);
    dpo_type type = SLD;
    pair<pii, pii> answer;
    int rick_roll = 4;
    stext title =
        stext("Title", {0, -100}, {231, 60}, (char *)"Slide to unlock", 24);
    stext never_gonna_give_you_up = stext(
        "Rick 1", {0, 85}, {231, 24}, (char *)"Never gonna give you up", 16);
    stext never_gonna_let_you_down = stext(
        "Rick 2", {0, 115}, {231, 24}, (char *)"Never gonna let you down", 16);
    stext never_gonna_run_around = stext("Rick 3", {0, 85}, {231, 24},
                                         (char *)"Never gonna run around", 16);
    stext and_desert_you =
        stext("Rick 4", {0, 115}, {231, 24}, (char *)"And desert you", 16);
    stext never_gonna_make_you_cry = stext(
        "Rick 5", {0, 85}, {231, 24}, (char *)"Never gonna make you cry", 16);
    stext never_gonna_say_goodbye = stext(
        "Rick 6", {0, 115}, {231, 24}, (char *)"Never gonna say goodbye", 16);
    stext never_gonna_tell_a_lie = stext("Rick 7", {0, 85}, {231, 24},
                                         (char *)"Never gonna tell a lie", 16);
    stext and_hurt_you =
        stext("Rick 8", {0, 115}, {231, 24}, (char *)"And hurt you", 16);
    button confirm = button("Continue", {0, 100}, {120, 60}, "Continue");
    void reset();

} sld;

typedef class main_menu : public dpo {
   public:
    main_menu(string name, pii pos, pii shape);
    stext title = stext("Title", {0, -70}, {231, 60}, (char *)"Main Menu", 24);
    button start = button("start", {0, 100}, {120, 40}, "START");
    void update(display_object *father, pii axis);
    void reset();
} main_menu;

typedef class tch_canvas : public dpo {
   public:
    bool touching;
    bool click;
    bool isClicked();
    tch_canvas(string name, pii pos, pii shape);
    size_t font_size;
    void draw_points();
    void draw_lines();
    void reset();
    void update(display_object *father, pii axis);
    pii *answer;
    char pool[60];
    char *str;
    pii click_pos;
    const char p[60] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                     'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                     'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                     'U', 'V', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e',
                     'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                     'p', 'q', 'r', 's', 't', 'u', 'v', 'x', 'y', 'z'};

    ;
    const dpo_type type = CANVAS;
} tch_canvas;

typedef class tch_scene : public dpo {
   public:
    tch_scene(string name, pii pos, pii shape);
    stext title =
        stext("Title", {0, -100}, {231, 60}, (char *)"Click In Order", 24);
    button confirm = button("Confirm", {0, 100}, {80, 40}, "Confirm");
    button refresh = button("Refresh", {80, -125}, {60, 17}, "Refresh");
    marker *markers;
    int marker_cnt;

    tch_canvas canvas = tch_canvas("Canvas", {0, 0}, {231, 130});
    stext notice =
        stext("Notice", {0, 100}, {231, 60}, (char *)"Finish Task Above", 16);
    void update(display_object *father, pii axis);
    void reset();
    pair<pii, pii> getRange(pii p);
    const pii mask_size = {30, 30};
    const pii good_range = {30, 30};

} tch_scene;

typedef class finish_scene : public dpo {
   public:
    finish_scene(string name, pii pos, pii shape);
    stext title =
        stext("Title", {0, -100}, {231, 60}, (char *)"Congratulations!", 24);
    stext notice =
        stext("Notice", {0, 0}, {231, 60}, (char *)"You have finished all "
                                                      "the tasks. Press "
                                                      "HOME to return to "
                                                      "main menu.",
              16);

} finish_scene;

#ifdef __cplusplus  // 使用C语言的方式编译方法名。
}
#endif
#endif