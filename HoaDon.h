#ifndef HOADON_H
#define HOADON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "Entity.h"
using namespace std;

void runHoaDon();
// Lop HoaDon ke thua tu Entity
class HoaDon : public Entity {
private:
    string soThueBao;
    string kyCuoc;
    double tongTien;
    string trangThai;

public:
    // Hàm khởi tạo mặc định (sử dụng initializer list)
    HoaDon()
        : Entity(""), soThueBao(""), kyCuoc(""), tongTien(0.0), trangThai("Chua thanh toan") {}

    // Hàm khởi tạo đầy đủ tham số (nếu cần)
    HoaDon(const string &ma, const string &stb, const string &kc, double tien, const string &tt = "Chua thanh toan")
        : Entity(ma), soThueBao(stb), kyCuoc(kc), tongTien(tien), trangThai(tt) {}
    string getMa() const { return ma; }
    void setMa(string _ma);
    void setTongTien(double _tien);
    string getSoThueBao() const;
    string getTrangThai() const;

    void nhapThongTin() ;
    void display() override;

    string taoChuoiLuuFile() const;
    void docTuChuoi(string dongDuLieu);
    void capNhatDaThanhToan();
};

// Lop QuanLyHoaDon
class QuanLyHoaDon {
private:
    vector<HoaDon> danhSach;
    string tenFile = "data/HoaDon.txt";

public:
    void docFile();
    void ghiFile();
    void themHoaDon();
    void xemDanhSach();
    void thuTienHoaDon();
    void xoaHoaDon();
    void menu();
};

#endif // HOADON_H
