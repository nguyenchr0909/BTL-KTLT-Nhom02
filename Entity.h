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

    string getMa(){return ma;}

    void setMa(const string& maMoi) {
    if (maMoi.empty()) {
        throw invalid_argument("Ma khong duoc rong!");
    }
    ma = maMoi; // Gán giá trị khi mã hợp lệ
}

    // Hàm thuần ảo: bắt buộc lớp con phải định nghĩa

    virtual ~Entity() = default;
};

#endif
