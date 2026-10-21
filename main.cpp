#include <iostream>
#include "ThueBao.h"
#include "HopDong.h"
#include "Entity.h"
#include "Sim.h"
#include "Khachhang.h"
#include "PhieuNapTien.h"
#include "PhieuKhieuNai.h"
#include "ThietbiDauCuoi.h"
#include "HoaDon.h"
#include "GoiCuoc.h"
#include "BanGhiCuocGoi.h"
using namespace std;


int main() {
    int choice;

    do {
        cout << "\n========== MENU CHINH ==========\n";
        cout << "1. Quan ly goi cuoc\n";
        cout << "2. Quan ly loai thue bao\n";
        cout << "3. Quan li khach hang\n";
        cout << "4. Quan ly SIM\n";
        cout << "5. Quan ly thiet bi dau cuoi\n";
        cout << "6. Quan ly hop dong dang ki thue bao\n";
        cout << "7. Quan ly phieu nap tien\n";
        cout << "8. Quan ly hop ban ghi cuoc goi\n";
        cout << "9. Quan ly hoa don cuoc\n";
        cout << "10.Quan ly phieu khieu nai\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        while (cin.fail() || choice < 0 || choice > 10) {
            cin.clear();            // 1. Khôi phục trạng thái hoạt động cho cin
            cin.ignore(10000, '\n'); // 2. Xóa sạch chữ/ký tự lỗi còn đệm trong bàn phím
            cout << "Lua chon khong hop le, hay nhap lai (0-5): ";
            cin >> choice;
        }   cin.ignore();

        switch (choice) {
            case 1:
                runGoiCuoc();
                break;
            case 2:
                runThueBao();
                break;
            case 3:
                runKhachHang();
                break;
            case 4:
                runSIM();
                break;
            case 5:
                runThietBiDauCuoi();
                break;
            case 6:
                runHopDong();
                break;
            case 7:
                NapTien();
                break;
            case 8:
                runBanGhiCuocGoi();
                break;
            case 9:
                runHoaDon();
                break;
            case 10:
                KhieuNai();
                break;
            case 0:
                cout << "Ket thuc chuong trinh!\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);

    return 0;
}
