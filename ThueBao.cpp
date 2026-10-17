#include "ThueBao.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iomanip>
using namespace std;



void runThueBao() {
    vector<ThueBao> danhSach; // Danh sách quản lý các thuê bao
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
        cin >> choice;

        // Xử lý khi nhập lựa chọn không hợp lệ
        while (cin.fail() || choice < 0 || choice > 5) {
            cin.clear();            // 1. Khôi phục trạng thái hoạt động cho cin
            cin.ignore(10000, '\n'); // 2. Xóa sạch chữ/ký tự lỗi còn đệm trong bàn phím
            cout << "Lua chon khong hop le, hay nhap lai (0-5): ";
            cin >> choice;
        }   cin.ignore();

        // Nếu chọn tạo thuê bao mới

        if (choice == 1) {
            ThueBao tb;
            tb.nhap(); // Gọi phương thức nhap() qua đối tượng tb
            danhSach.push_back(tb); // Thêm vào danh sách vector
            cout << "-> Them thue bao thanh cong!\n\n";
        }


        //Nếu chọn in danh sách

        if (choice == 2) {
            // Gọi hàm static xuất toàn bộ danh sách
            ThueBao::xuat(danhSach);
        }


        //Nếu chọn tìm kiếm thuê bao
       if  (choice  == 3){
            ThueBao::tim(danhSach);
       }

    }
}

// Định nghĩa phương thức nhap() của lớp ThueBao
void ThueBao::nhap() {
    string maMoi;
    while (true) {
        try {
            cout << "Nhap ma thue bao: ";
            getline(cin, maMoi);

            setMa(maMoi); // Nếu rỗng, setMa sẽ quăng lỗi văng xuống khối catch
            break;        // Nếu không lỗi, thoát khỏi vòng lặp
        }
        catch (const invalid_argument& e) {
            cout << e.what() << " Vui long nhap lai.\n";
        }
    }


    //setMa(maMoi); // Gọi hàm của Entity để gán và kiểm tra mã

    cout << "Nhap Loai Thue Bao: ";
    getline(cin, Loai_Thue_Bao);

    cout << "Nhap Han muc: ";
    cin>>Han_muc;
    cin.ignore(); // Xóa ký tự '\n' đệm trước khi dùng getline kế tiếp

    cout << "Nhap uu dai: ";
    getline(cin, Uu_dai);

}



// In toàn bộ danh sách thuê bao
void ThueBao::xuat(const vector<ThueBao>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach thue bao hien dang rong!\n\n";
        return;
    }

    // Đường kẻ ngang
    string line = "-------------------------------------------------------------------------";

    cout << "\n" << line << endl;
    // In tiêu đề bảng (dùng left để căn lề trái, setw để cố định độ rộng cột)
    cout << "| " << left << setw(12) << "Ma thue bao"
         << "| " << left << setw(18) << "Loai thue bao"
         << "| " << right << setw(12) << "Han muc" << " | "
         << left << setw(20) << "Uu dai" << " |\n";
    cout << line << endl;

    // In từng dòng dữ liệu trong vector
    for (const auto& tb : danhSach) {
        cout << "| " << left << setw(12) << tb.ma
             << "| " << left << setw(18) << tb.Loai_Thue_Bao
             << "| " << right << setw(12) << tb.Han_muc << " | "
             << left << setw(20) << tb.Uu_dai << " |\n";
    }

    cout << line << endl;
    cout << "Tong so ban ghi: " << danhSach.size() << "\n\n";
}



void ThueBao::tim(const vector<ThueBao>& danhSach)
{
    //Nếu danh sách bị rỗng
    if (danhSach.empty()) {
        cout << "\n-> Danh sach thue bao hien dang rong! Khong the tim kiem.\n\n";
        return;
    }

    //Kiếm theo mã
    string TimKiem;
    cout<<"\nHay nhap ma muon tim kiem: ";
    getline(cin,TimKiem);
    
    bool TimThay=false;
    
    for(const & tb:danhSach)
    {
        
    }
}
