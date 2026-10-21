#include <iostream>
#include "ThueBao.h"
#include "HopDong.h"
#include "Entity.h"

using namespace std;


int main() {
    int choice;

    do {
        cout << "\n========== MENU CHINH ==========\n";
        cout << "1. Quan ly thue bao\n";
        cout << "2. Quan ly hop dong\n";
        cout << "3. Nap tien\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        while (cin.fail() || choice < 0 || choice > 5) {
            cin.clear();            // 1. Khôi phục trạng thái hoạt động cho cin
            cin.ignore(10000, '\n'); // 2. Xóa sạch chữ/ký tự lỗi còn đệm trong bàn phím
            cout << "Lua chon khong hop le, hay nhap lai (0-5): ";
            cin >> choice;
        }   cin.ignore();

        switch (choice) {
            case 1:
                runThueBao();
                break;
            case 2:
                runHopDong();
                break;
            case 3:
                runThueBao();
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
