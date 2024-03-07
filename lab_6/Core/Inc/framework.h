#ifndef __FRAMWORK_H
#define __FRAMWORK_H

#ifndef pii
#define pii pair<int, int>
#endif
#include <stdio.h>

#include <algorithm>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

#include "lcd.h"
#include "stm32f1xx.h"

using namespace std;

#ifdef __cplusplus  // 使用C语言的方式编译方法名。
extern "C" {
#endif

pii *mk_p(pii parent);

typedef class display_object {
   private:
    int id;
    display_object *parent;
    pii pos;
    pii shape;
    vector<display_object *> sub_object;
    float alpha;
    bool isVisible;
    bool touching;
   public:
    string name;
    static unsigned int cnt;
    static UART_HandleTypeDef uart;

   public:
    bool isClicked();
    display_object(string name, pii pos, pii shape);

    bool set_parent(display_object *parent);
    display_object *get_parent();

    bool add_son(display_object *son);
    vector<display_object* > get_son();

    void setAlpha(float alpha);
    float getAlpha();

    void setVisibility(bool flag);
    bool getVisibility();

    int get_id();
    void move(pair<int, int> pos);
    void update();
} dpo;

typedef class var_text : public dpo {
    private:
    
} vtext;


#ifdef __cplusplus  // 使用C语言的方式编译方法名。

}
#endif

#endif