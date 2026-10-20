#ifndef PHIEUKHIEUNAI_H
#define PHIEUKHIEUNAI_H

#include <iostream>
#include <string>
#include "PhieuKhieuNai.h"
#include "Entity.h"

using namespace std;
using ll = long long;

class PhieuKhieuNai : public Entity {// để cho cái class phiếu nạp nó kế thừa cái entity
private :
    string SoThueBao;// để trong private chứ ko sẽ lộ thông tin khách hàng
    string NoiDung;
    string TrangThai;
    ll MenhGia;

public :
    PhieuKhieuNai();
    void nhap();
    void hienThi() override;
    string toFile();
    void fromFile(string line);// dùng để nhận dòng chữ của cái tofile
    string getma(){return ma;}// mấy cái này phải trả về (return biến ) để nx hàm trong protected và private có thể dc lấy ra nma chỉ xem và ko thay đổi dc cái trong đó
    string getSoThueBao() {return SoThueBao;}
    string getNoiDung() {return NoiDung;}
    string getTrangThai() {return TrangThai;}
    void setTrangThai(string tt) {TrangThai = tt;}
};
void KhieuNai();
#endif
