#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
using namespace std;

class Entity {
protected:

    string ma;  // Mã định danh chung

public:
    Entity(const string& code) : ma(code) {}




    // Hàm thuần ảo: bắt buộc lớp con phải định nghĩa
    virtual void hienThi() = 0;
    virtual ~Entity() = default;
};

#endif
