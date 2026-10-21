#ifndef PHIEUNAPTIEN_H
#define PHIEUNAPTIEN_H

#include <iostream>
#include <string>
#include "Entity.h"

using namespace std;
using ll = long long;

class PhieuNapTien : public Entity {// để cho cái class phiếu nạp nó kế thừa cái entity
private :
    string SoThueBao;// để trong private chứ ko sẽ lộ thông tin khách hàng
    ll MenhGia;

public :
    PhieuNapTien();
    void nhap();
    void display() override;// override để kiểm tra m ghi đè cái hiển thị có bị sai ko
    string toFile();
    void fromFile(string line);// dùng để nhận dòng chữ của cái tofile
    string getma(){return ma;}// mấy cái này phải trả về (return biến ) để nx hàm trong protected và private có thể dc lấy ra nma chỉ xem và ko thay đổi dc cái trong đó
    string getSoThueBao() {return SoThueBao;}
    ll getMenhGia() {return MenhGia;}
    void setMenhGia(ll mg) { MenhGia = mg;}

};
 void NapTien();// nằm trong cpp nhưng mà là 1 hàm tự do không nằm trong class Phieu nap tien

#endif// để biết code hiểu mình cần bảo về phần code này đến đâu phần  ifndef đã mở ra
