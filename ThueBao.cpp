#include "ThueBao.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <ctype.h>


using namespace std;

void ThueBao::display() {
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
    ThueBao::docFile(danhSach);
    int choice = -1;
    ThueBao x;
    while (choice != 0) {
        x.display();
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
            ThueBao::luuFile(danhSach);
        }

        // Nếu chọn in danh sách
        if (choice == 2) {
            ThueBao::xuat(danhSach);

        }

        // Nếu chọn tìm kiếm thuê bao
        if (choice == 3) {
            ThueBao::tim(danhSach);
        }


        // Nếu chọn sửa/đổi thuê bao
        if (choice == 4) {
            ThueBao::sua(danhSach);
            ThueBao::luuFile(danhSach);
        }

        //Nếu chọn xóa thuê bao
        // Nếu chọn sua/doi thuê bao
        if (choice == 5) {
            ThueBao::xoa(danhSach);
            ThueBao::luuFile(danhSach);
        }
}
}

// 1. NHAP DU LIEU THUE BAO
void ThueBao::nhap(const vector<ThueBao>& danhSach) {
    string maMoi;
    while (true) {
        try {
            cout << "Nhap ma thue bao(LH01): ";
            getline(cin, maMoi);

            // Nếu rỗng quăng lỗi văng xuống khối catch
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

    cout << "Nhap Loai Thue Bao(Tra truoc/Tra sau): ";
    getline(cin, Loai_Thue_Bao);

    cout << "Nhap Han muc(VND): ";
    cin >> Han_muc;
    // Bổ sung kiểm tra khi nhập Hạn mức không phải số
    while (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Han muc phai la so, vui long nhap lai: ";
        cin >> Han_muc;
    }
    cin.ignore(); // Xóa ký tự '\n' còn đệm

    cout << "Nhap uu dai(Khong co thi ghi'Khong'): ";
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
    for (ThueBao& tb : danhSach) {
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
    cout << "(Notice: Nhan Enter neu muon giu nguyen thong tin cu)\n\n";

    // 1. Cập nhật Loại thuê bao
    string inputStr;
    int    inputInt;
    cout << "Nhap Loai thue bao moi : ";
    getline(cin, inputStr);
    if (!inputStr.empty()) {
        tbFound->Loai_Thue_Bao = inputStr;
    }

    // 2. Cập nhật Hạn mức

    while(1)
     {  cout << "Nhap Han muc moi : ";
        getline(cin, inputStr);
        try {
            double hanMucMoi = stod(inputStr); // Chuyển chuỗi sang kiểu số double
            if (hanMucMoi >= 0) {
                {tbFound->Han_muc = hanMucMoi;break;}
            } else {
                cout << "-> Han muc khong hop le (phai >= 0). Vui long nhap lai han muc.\n";
            }
        } catch (...) {
            cout << "-> Du lieu nhap vao khong phai la so. Vui long nhap lai han muc.\n";
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

// 5.HÀM XÓA THUE BAO THEO MA
void ThueBao::xoa(vector<ThueBao>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach hien dang rong, khong the xoa!\n\n";
        return;
    }

    string maXoa;
    while (true) {
        cout << "Nhap ma thue bao can xoa (Nhan ENTER de huy): ";
        getline(cin, maXoa);

        // 1. Nếu nhấn Enter (mã rỗng) -> Hủy thao tác xóa
        if (maXoa.empty()) {
            cout << "-> Da huy thao tac xoa thue bao.\n\n";
            return;
        }

        // 2. Tìm mã trong danh sách
        bool timThay = false;
        for (auto ers = danhSach.begin(); ers != danhSach.end(); ++ers) {
            if (ers->ma == maXoa) {
                timThay = true;

                // Xác nhận xóa
                char xacNhan;
                cout << "Ban co chac chan muon xoa thue bao '" << maXoa << "'? (Y/N): ";
                cin >> xacNhan;
                cin.ignore(); // Xóa ký tự '\n' đệm

                if (xacNhan == 'Y' || xacNhan == 'y') {
                    danhSach.erase(ers);
                    cout << "-> Xoa thue bao thanh cong!\n\n";
                } else {
                    cout << "-> Da huy thao tac xoa.\n\n";
                }

                return; // Xóa hoặc hủy xong thì thoát hàm luôn
            }
        }

        // 3. Nếu không tìm thấy mã -> Báo lỗi và vòng lặp while sẽ bắt nhập lại
        if (!timThay) {
            cout << "-> Loi: Ma thue bao '" << maXoa << "' khong ton tai trong danh sach! Vui long nhap lai.\n\n";
        }
    }
}

          // Hàm lưu file

void ThueBao::luuFile(const vector<ThueBao>& danhSach) {
    fstream fs;
    // Mở file
    fs.open("data\\Thuebao.txt");
    //Kiểm tra file có lỗi khi mở không
    if (!fs.is_open()) {
        cout << "-> Canh bao: Khong the mo file de ghi du lieu! (Kiểm tra thu muc 'data')\n";
        return ;
    }

    fs << "# MaThueBao|LoaiThueBao|HanMuc|UuDai\n";

    for (const ThueBao& tb : danhSach) {
        fs << tb.ma << "|"
                << tb.Loai_Thue_Bao << "|"
                << tb.Han_muc << "|"
                << tb.Uu_dai << "\n";
    }

    fs.close();
}

// Hàm đọc file

void ThueBao::docFile(vector<ThueBao>& danhSach) {
    fstream fs;
    fs.open("data\\Thuebao.txt", ios::in);

    // Nếu file chưa tồn tại thì tạo file rỗng
    if (!fs.is_open()) {
        ofstream fs("data\\Thuebao.txt");
        fs.close();
        return;
    }

    danhSach.clear();

    int Dong=1;
    string line;
    while (getline(fs, line)) {
        Dong++;
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);
        string ma, loai, hanMucStr, uuDai;

        if (getline(ss, ma, '|') &&
            getline(ss, loai, '|') &&
            getline(ss, hanMucStr, '|') &&
            getline(ss, uuDai)) {

            try {
                size_t pos;
                double hanMuc = stod(hanMucStr, &pos);

                if (ma.empty()||hanMuc <0||loai.empty()||hanMucStr.empty()||uuDai.empty()||pos!=hanMucStr.length())
                    {cout << "Du lieu: " << line <<" khong hop le\n";continue;}

                danhSach.push_back(
                    ThueBao(ma, loai, hanMuc, uuDai)
                );
            }
            catch (...) {
                cout << "Du lieu: " << line <<" khong hop le\n";
            }
        }
       else cout << "Du lieu: " << line <<" khong hop le\n";
}


    fs.close();
}
