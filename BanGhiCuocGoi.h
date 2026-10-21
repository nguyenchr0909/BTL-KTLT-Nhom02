#ifndef CDR_H
#define CDR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <exception>
#include <stdexcept>
#include "Entity.h"

using namespace std;

// Lop BanGhiCuocGoi ke thua tu Entity
class BanGhiCuocGoi : public Entity {
private:
    string maBanGhi;
    string soGoi;
    string soNhan;
    string thoiDiem;
    int thoiLuong;

public:
    BanGhiCuocGoi();
    BanGhiCuocGoi(string ma, string goi, string nhan, string thoiDiemGoi, int luong);

    void setMaBanGhi(string ma);
    void setSoGoi(string goi);
    void setSoNhan(string nhan);
    void setThoiDiem(string td);
    void setThoiLuong(int luong);

    string getMaBanGhi() const;
    string getSoGoi() const;
    string getSoNhan() const;
    string getThoiDiem() const;
    int getThoiLuong() const;

    void input();
    void display() override;
    string toString() const;
};

// Cac ham ho tro doc/ghi file
vector<BanGhiCuocGoi> loadBanGhiCuocGois();
void saveBanGhiCuocGois(const vector<BanGhiCuocGoi> &dsBanGhi);

// Cac ham chuc nang quan ly
void createBanGhiCuocGoi();
void readBanGhiCuocGois();
void updateBanGhiCuocGoi();
void deleteBanGhiCuocGoi();

// Ham chay menu chinh
void runBanGhiCuocGoi();
void RunBanGhiCuocGoi();

#endif // CDR_H
