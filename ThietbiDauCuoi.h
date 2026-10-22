/*
Ma use case: CS_05
Ho va ten: Nguyen Van Hai
MSV B24DCVT122
*/
#ifndef THIETBIDAUCUOI_H
#define THIETBIDAUCUOI_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "Entity.h"

using namespace std;

void runThietBiDauCuoi();

class ThietBiDauCuoi : public Entity {
private:
    string loaiThietBi;
    string tinhTrang;
    double giaBan;

public:
    ThietBiDauCuoi()
        : Entity(""), loaiThietBi(""), tinhTrang("Moi"), giaBan(0.0) {}

    ThietBiDauCuoi(const string& ma, const string& loai, const string& tt, double gia)
        : Entity(ma), loaiThietBi(loai), tinhTrang(tt), giaBan(gia) {}

    string getMa() const { return ma; }
    void setMa(const string& _ma) { ma = _ma; }

    string getLoaiThietBi() const { return loaiThietBi; }
    void setLoaiThietBi(const string& loai) { loaiThietBi = loai; }

    string getTinhTrang() const { return tinhTrang; }
    void setTinhTrang(const string& tt) { tinhTrang = tt; }

    double getGiaBan() const { return giaBan; }
    void setGiaBan(double gia) {
        if (gia < 0) throw invalid_argument("Gia ban khong duoc am!");
        giaBan = gia;
    }

    void nhapThongTin();
    void display() override;

    string taoChuoiLuuFile() const;
    void docTuChuoi(const string& dongDuLieu);
};

class QuanLyThietBiDauCuoi {
private:
    vector<ThietBiDauCuoi> danhSach;
    string tenFile = "data/ThietBiDauCuoi.txt";

public:
    void docFile();
    void ghiFile();
    void themThietBi();
    void xemDanhSach();
    void timKiemThietBi();
    void suaThietBi();
    void xoaThietBi();
    void menu();
};

#endif // THIETBIDAUCUOI_H
