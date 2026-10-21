#ifndef HopDong_H
#define HopDong_H

#include "Entity.h"
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

void runHopDong();

class HopDong : public Entity
{
  private:
     // ma (Mã hợp đồng, vd: HD01) kế thừa từ Entity
     string maKH;    // Mã khách hàng
     string tenGoi;  // Tên gói cước / tên thuê bao
     double Nocuoc;  // Số tiền nợ cước

  public:
    // Hàm khởi tạo (Constructor)
    HopDong() : Entity(""), maKH(""), tenGoi(""), Nocuoc(0.0) {}

    HopDong(const string &ma, const string &kh, const string &goi, double money)
        : Entity(ma), maKH(kh), tenGoi(goi), Nocuoc(money) {}

    // ==================== GETTERS & SETTERS (VALIDATION) ====================
    // 1. Mã hợp đồng (Kế thừa từ Entity)
    string getMa() const { return ma; }
    void setMa(const string &m) {
        if (m.empty()) throw invalid_argument("Ma hop dong khong duoc de trong!");
        ma = m;
    }

    // 2. Mã khách hàng
    string getMaKH() const { return maKH; }
    void setMaKH(const string &kh) {
        if (kh.empty()) throw invalid_argument("Ma khach hang khong duoc de trong!");
        maKH = kh;
    }

    // 3. Tên gói / Tên thuê bao
    string getTenGoi() const { return tenGoi; }
    void setTenGoi(const string &goi) {
        if (goi.empty()) throw invalid_argument("Ten goi/thue bao khong duoc de trong!");
        tenGoi = goi;
    }

    // 4. Nợ cước
    double getNocuoc() const { return Nocuoc; }
    void setNocuoc(double money) {
        if (money < 0) throw invalid_argument("So tien no cuoc khong duoc nho hon 0!");
        Nocuoc = money;
    }

    // ==================== CÁC HÀM XỬ LÝ NGHỆP VỤ ====================
    void display() override;
    void        nhap(const vector<HopDong>& danhSach);
    static void xuat(const vector<HopDong>& danhSach);
    static void tim (const vector<HopDong>& danhSach);
    static void sua (vector<HopDong>& danhSach);
    static void xoa (vector<HopDong>& danhSach);

    // ==================== CÁC HÀM THAO TÁC FILE ====================
    static void docFile(vector<HopDong>& danhSach);
    static void luuFile(const vector<HopDong>& danhSach);
};

#endif
