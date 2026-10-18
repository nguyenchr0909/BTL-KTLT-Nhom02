#include "ThueBao.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iomanip>
using namespace std;


void ThueBao::hienThi() {
    cout << "============ QUAN LY THUE BAO ============\n";
    cout << "  1. Them thue bao moi\n";
    cout << "  2. Xem danh sach thue bao\n";
    cout << "  3. Tim kiem thue bao\n";
    cout << "  4. Cap nhat thong tin thue bao\n";
    cout << "  5. Xoa thue bao\n";
    cout << "  0. Quay lai\n";
    cout << "==========================================\n";
    cout << "Nhap lua chon: ";
}
void runThueBao() {
    vector<ThueBao> danhSach; // Danh sách quản lý các thuê bao
    int choice = -1;
    ThueBao x;
    while (choice != 0) {
        x.hienThi();
        cin >> choice;

        // Xử lý khi nhập lựa chọn không hợp lệ
        while (cin.fail() || choice < 0 || choice > 5) {
            cin.clear();             // 1. Khôi phục trạng thái hoạt động cho cin
            cin.ignore(10000, '\n'); // 2. Xóa sạch chữ/ký tự lỗi còn đệm trong bàn phím
            cout << "Lua chon khong hop le, hay nhap lai (0-5): ";
            cin >> choice;
        }
        cin.ignore();

        // Nếu chọn tạo thuê bao mới
        if (choice == 1) {
            ThueBao tb;
            tb.nhap(danhSach); // Gọi phương thức nhap() qua đối tượng tb
            danhSach.push_back(tb); // Thêm vào danh sách vector
            cout << "-> Them thue bao thanh cong!\n\n";
        }

        // Nếu chọn in danh sách
        if (choice == 2) {
            ThueBao::xuat(danhSach);
        }

        // Nếu chọn tìm kiếm thuê bao
        if (choice == 3) {
            ThueBao::tim(danhSach);
        }


        // Nếu chọn sua/doi thuê bao
        if (choice == 4) {
            ThueBao::sua(danhSach);


        }

        //Nếu chọn chinh sau thue bao

}
}

// 1. NHAP DU LIEU THUE BAO
void ThueBao::nhap(const vector<ThueBao>& danhSach) {
    string maMoi;
    while (true) {
        try {
            cout << "Nhap ma thue bao: ";
            getline(cin, maMoi);

            // Nếu rỗng, setMa sẽ quăng lỗi văng xuống khối catch
            if (maMoi.empty()) {
                   throw invalid_argument("Ma khong duoc rong!");
                 }
                  ma = maMoi;

            // Nếu bị trùng, sẽ bị quăng xuống catch
            for (const auto& tb : danhSach) {
                if (tb.ma == maMoi) {
                    throw invalid_argument("Loi: Ma thue bao '" + maMoi + "' da ton tai!");
                }
            }

            // Nếu không có lỗi nào bị throw, thoát khỏi vòng lặp nhập mã
            break;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << " Vui long nhap lai.\n";
        }
    }

    cout << "Nhap Loai Thue Bao: ";
    getline(cin, Loai_Thue_Bao);

    cout << "Nhap Han muc: ";
    cin >> Han_muc;
    // Bổ sung kiểm tra khi nhập Hạn mức không phải số
    while (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Han muc phai la so, vui long nhap lai: ";
        cin >> Han_muc;
    }
    cin.ignore(); // Xóa ký tự '\n' còn đệm

    cout << "Nhap uu dai: ";
    getline(cin, Uu_dai);
}

// 2. HAM IN TOAN BO THUE BAO
void ThueBao::xuat(const vector<ThueBao>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach thue bao hien dang rong!\n\n";
        return;
    }

    cout << "\n-------------------------------------------------------------------------\n";
    cout << "| " << left << setw(12) << "Ma thue bao"
         << "| " << left << setw(18) << "Loai thue bao"
         << "| " << right << setw(12) << "Han muc" << " | "
         << left << setw(20) << "Uu dai" << " |\n";
    cout << "-------------------------------------------------------------------------\n";

    for (const ThueBao& tb : danhSach) {
        cout << "| " << left << setw(12) << tb.ma
             << "| " << left << setw(18) << tb.Loai_Thue_Bao
             << "| " << right << setw(12) << tb.Han_muc << " | "
             << left << setw(20) << tb.Uu_dai << " |\n";
    }

    cout << "-------------------------------------------------------------------------\n";
    cout << "Tong so ban ghi: " << danhSach.size() << "\n\n";
}

// 3. HAM TIM KIEM THEO MA (ĐÃ SỬA LỖI LOGIC)
void ThueBao::tim(const vector<ThueBao>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach thue bao hien dang rong! Khong the tim kiem.\n\n";
        return;
    }

    string TimKiem;
    cout << "\nHay nhap ma muon tim kiem: ";
    getline(cin, TimKiem);

    bool TimThay = false;

    for (const ThueBao& tb : danhSach) {
        if (tb.ma == TimKiem) {
            TimThay = true;

            // In bảng khi tìm thấy
            cout << "\n-------------------------------------------------------------------------\n";
            cout << "| " << left << setw(12) << "Ma thue bao"
                 << "| " << left << setw(18) << "Loai thue bao"
                 << "| " << right << setw(12) << "Han muc" << " | "
                 << left << setw(20) << "Uu dai" << " |\n";
            cout << "-------------------------------------------------------------------------\n";

            cout << "| " << left << setw(12) << tb.ma
                 << "| " << left << setw(18) << tb.Loai_Thue_Bao
                 << "| " << right << setw(12) << tb.Han_muc << " | "
                 << left << setw(20) << tb.Uu_dai << " |\n";

            cout << "-------------------------------------------------------------------------\n\n";
            break; // Tìm thấy thì dừng vòng lặp
        }
    }

    if (!TimThay) {
        cout << "-> Khong tim thay thue bao co ma: " << TimKiem << "\n\n";
    }
}

// 4. HAM CAP NHAT / SUA THONG TIN THUE BAO
void ThueBao::sua(vector<ThueBao>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach thue bao hien dang rong! Khong the cap nhat.\n\n";
        return;
    }

    string maTim;
    cout << "\nNhap ma thue bao can sua thong tin: ";
    getline(cin, maTim);

    // Tìm thuê bao theo mã trong danh sách
    ThueBao* tbFound = nullptr;
    for (auto& tb : danhSach) {
        if (tb.ma == maTim) { // Sử dụng getMa() nếu ma là private
            tbFound = &tb;
            break;
        }
    }

    // Nếu không tìm thấy
    if (tbFound == nullptr) {
        cout << "-> Khong tim thay thue bao co ma: " << maTim << "\n\n";
        return;
    }

    // Hiển thị thông tin hiện tại
    cout << "\n--- THONG TIN HIEN TAI ---";
    cout << "\nMa thue bao: " << tbFound->ma;
    cout << "\nLoai thue bao: " << tbFound->Loai_Thue_Bao;
    cout << "\nHan muc: " << tbFound->Han_muc;
    cout << "\nUu dai: " << tbFound->Uu_dai << "\n";
    cout << "---------------------------\n";
    cout << "(Notice: Nhan Enter neu muon giu nguyen thong tin cu)\n\n";

    // 1. Cập nhật Loại thuê bao
    string inputStr;
    cout << "Nhap Loai thue bao moi [" << tbFound->Loai_Thue_Bao << "]: ";
    getline(cin, inputStr);
    if (!inputStr.empty()) {
        tbFound->Loai_Thue_Bao = inputStr;
    }

    // 2. Cập nhật Hạn mức
    cout << "Nhap Han muc moi [" << tbFound->Han_muc << "]: ";
    getline(cin, inputStr);
    if (!inputStr.empty()) {
        try {
            double hanMucMoi = stod(inputStr); // Chuyển chuỗi sang kiểu số double
            if (hanMucMoi >= 0) {
                tbFound->Han_muc = hanMucMoi;
            } else {
                cout << "-> Han muc khong hop le (phai >= 0). Giu nguyen han muc cu.\n";
            }
        } catch (...) {
            cout << "-> Du lieu nhap vao khong phai la so. Giu nguyen han muc cu.\n";
        }
    }

    // 3. Cập nhật Ưu đãi
    cout << "Nhap Uu dai moi [" << tbFound->Uu_dai << "]: ";
    getline(cin, inputStr);
    if (!inputStr.empty()) {
        tbFound->Uu_dai = inputStr;
    }

    cout << "\n-> Cap nhat thong tin thue bao thành cong!\n\n";
}
