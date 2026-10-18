#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
using namespace std;

class Entity {
protected:
    string ma;
public:
    Entity(const string& code) : ma(code) {}
    virtual void hienThi() = 0;
    virtual ~Entity() = default;
};
#endif
