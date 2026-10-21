#ifndef HopDong_H
#define HopDong_H

#include "Entity.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void runHopDong();

class HopDong : public Entity
{
  private:
     // ma (Ma HD, vd: HD01) ke thua tu Entity
     string maKH;         // Ma khach hang (dung de tra ra ten khach hang)
     string tenGoi;        // Ma goi cuoc
     double Nocuoc;   // Dinh dang dd/mm/yyyy

  public:

    // Ham khoi tao
    HopDong() : Entity(""), maKH(""), tenGoi(""), Nocuoc() {}

    HopDong(const string &ma, const string &kh,
            const string &goi, double money )
        : Entity(ma), maKH(kh), tenGoi(goi), Nocuoc(money) {}

    // Cac ham thuc hien voi du lieu
    void hienThi() override;
    void        nhap(const vector<HopDong>& danhSach);
    static void xuat(const vector<HopDong>& danhSach);
    static void tim (const vector<HopDong>& danhSach);        // tim theo ma HD hoac theo khach hang
    static void sua (vector<HopDong>& danhSach);
    static void xoa (vector<HopDong>& danhSach);

    // Cac ham thao tac voi file
    static void docFile(vector<HopDong>& danhSach);
    static void luuFile(const vector<HopDong>& danhSach);
};

#endif
