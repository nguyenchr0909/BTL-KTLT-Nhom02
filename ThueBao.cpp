#include "ThueBao.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Entity
{
    protected:
       string id;





};

void runThueBao() {

        int choice = -1;
        while (choice != 0) {

            cout << "============ QUAN LY THUE BAO ============\n";
            cout << "  1. Them thue bao moi\n";
            cout << "  2. Xem danh sach thue bao\n";
            cout << "  3. Tim kiem thue bao\n";
            cout << "  4. Cap nhat thong tin thue bao\n";
            cout << "  5. Xoa thue bao\n";
            cout << "  0. Quay lai\n";
            cout << "==========================================\n";
            cout << "Nhap lua chon: ";
            cin  >> choice;

            while(choice<0||choice>5) {cout<< "Lua chon khong hop le, hay lua chon lai: ";cin>>choice;}
        





        }

}
