#include <iostream>
#include "Sim.h"
#include "Khachhang.h"
#include "Entity.h"
using namespace std;

int main() {
    int choice;
    do {
        cout << "\n========== MENU CHINH ==========\n";
        cout << "1. Quan ly thue bao\n";
        cout << "2. Quan ly don cuoc\n";
        cout << "3. Nap tien\n";
        cout << "4. Quan ly khach hang\n";
        cout << "5. Quan ly sim\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        while (cin.fail() || choice < 0 || choice > 5) {
            cin.clear();            // 1. Khôi ph?c tr?ng thái ho?t đ?ng cho cin
            cin.ignore(10000, '\n'); // 2. Xóa s?ch ch?/k? t? l?i c?n đ?m trong bàn phím
            cout << "Lua chon khong hop le, hay nhap lai (0-5): ";
            cin >> choice;
        }   cin.ignore();

        switch (choice) {
            case 4:
            	runKhachHang();
            	break;
            case 5:
            	runSIM();
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
