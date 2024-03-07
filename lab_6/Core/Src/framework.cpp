
#include "framework.h"

using namespace std;

pii* mk_p(pii parent) {
    pii* v = new pii;
    v->first = parent.first;
    v->second = parent.second;
    return v;
}

unsigned int dpo::cnt = 0;

dpo::display_object(string name, pii pos, pii shape) {
    this->id = dpo::cnt;
    dpo::cnt++;
    this->pos = *mk_p(pos);
    this->shape = *mk_p(shape);
    this->isVisible = true;
    this->sub_object.clear();
    printf("Added object \"%s\" \n", this->name.c_str());
}

bool dpo::set_parent(dpo* parent) {
    if (this->get_parent() != nullptr) return false;
    this->parent = parent;
    return true;
}
dpo* dpo::get_parent() { return this->parent; }

bool dpo::add_son(dpo* son) {
    // Unique confirm
    if (son == NULL) return false;
    if (!son->set_parent(this)) return false;
    for (dpo* i : this->sub_object)
        if (i->id == son->id) return false;
    this->sub_object.push_back(son);
    return true;
}
vector<display_object*> dpo::get_son() { return this->sub_object; }

void dpo::setAlpha(float alpha) {
    alpha = alpha > 1.0 ? 1.0 : alpha;
    alpha = alpha < 0.0 ? 0.0 : alpha;
    this->alpha = alpha;
}
float dpo::getAlpha() { return this->alpha; }

void dpo::setVisibility(bool flag) { this->isVisible = flag; }
bool dpo::getVisibility() { return this->isVisible; }

int dpo::get_id() { return this->id; }

void dpo::move(pair<int, int> pos) { this->pos = *mk_p(pos); }

void dpo::update() {
    for (dpo* son : this->get_son()) {
        son->update();
    }
}