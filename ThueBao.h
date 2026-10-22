/*
Ma use case: CS_02
Ho va ten: Tran Vu Nguyen
MSV B24DCVT283
*/
#ifndef ThueBao_H
#define ThueBao_H

#include "Entity.h"
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

void runThueBao();
bool check_int(string s);

class ThueBao : public Entity {
private:
    // Đóng gói thuộc tính private
    string Loai_Thue_Bao;
    double Han_muc;
    string Uu_dai;

public:
    // Constructors
    ThueBao() : Entity(""), Loai_Thue_Bao(""), Han_muc(0), Uu_dai("") {}

    ThueBao(const string &ma, const string &loai, double no, string uudai)
        : Entity(ma), Loai_Thue_Bao(loai), Han_muc(no), Uu_dai(uudai) {}

    // Hàm Setter với Getter
    string getMa() const { return ma; }
    void setMa(const string &m) {
        if (m.empty()) throw invalid_argument("Ma thue bao khong duoc de trong!");
        ma = m;
    }

    string getLoaiThueBao() const { return Loai_Thue_Bao; }
    void setLoaiThueBao(const string &loai) {
        if (loai.empty()) throw invalid_argument("Loai thue bao khong duoc de trong!");
        Loai_Thue_Bao = loai;
    }

    double getHanMuc() const { return Han_muc; }
    void setHanMuc(double hm) {
        if (hm < 0) throw invalid_argument("Han muc khong duoc nho hon 0!");
        Han_muc = hm;
    }

    string getUuDai() const { return Uu_dai; }
    void setUuDai(const string &ud) {
        Uu_dai = ud;
    }

    //
    void display() override;
    void nhap(const vector<ThueBao>& danhSach);
    static void xuat(const vector<ThueBao>& danhSach);
    static void tim(const vector<ThueBao>& danhSach);
    static void sua(vector<ThueBao>& danhSach);
    static void xoa(vector<ThueBao>& danhSach);

    //
    static void docFile(vector<ThueBao>& danhSach);
    static void luuFile(const vector<ThueBao>& danhSach);
};

#endif
