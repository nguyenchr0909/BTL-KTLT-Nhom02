#include "HopDong.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <ctype.h>


using namespace std;

void HopDong::display() {
    cout << "\n";
    cout << "============ QUAN LY HOP DONG DANG KI THUE BAO ============\n";
    cout << "  1. Them hop dong moi\n";
    cout << "  2. Xem danh sach hop dong\n";
    cout << "  3. Tim kiem hop dong\n";
    cout << "  4. Cap nhat thong tin hop dong\n";
    cout << "  5. Xoa thue bao\n";
    cout << "  0. Quay lai\n";
    cout << "==========================================\n";
    cout << "Nhap lua chon: ";
}
void runHopDong() {
    vector<HopDong> danhSach; // Danh sách quản lý các hợp đồng
    HopDong::docFile(danhSach);
    int choice = -1;
    HopDong x;
    while (choice != 0) {
        x.display();
        cin >> choice;

        // Xử lý khi nhập lựa chọn không hợp lệ
        while (cin.fail() || choice < 0 || choice > 5) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Lua chon khong hop le, hay nhap lai (0-5): ";
            cin >> choice;
        }
        cin.ignore();

        // Nếu chọn tạo thuê bao mới
        if (choice == 1) {
            HopDong hd;
            hd.nhap(danhSach); // Gọi phương thức nhap() qua đối tượng tb
            danhSach.push_back(hd); // Thêm vào danh sách vector
            cout << "-> Them hop dong thanh cong!\n\n";
            HopDong::luuFile(danhSach);
        }

        // Nếu chọn in danh sách
        if (choice == 2) {
            HopDong::xuat(danhSach);

        }

        // Nếu chọn tìm kiếm thuê bao
        if (choice == 3) {
            HopDong::tim(danhSach);
        }


        // Nếu chọn sửa/đổi thuê bao
        if (choice == 4) {
            HopDong::sua(danhSach);
            HopDong::luuFile(danhSach);
        }

        //Nếu chọn xóa thuê bao

        if (choice == 5) {
            HopDong::xoa(danhSach);
            HopDong::luuFile(danhSach);
        }
}
}

// 1. NHAP DU LIEU THUE BAO
void HopDong::nhap(const vector<HopDong>& danhSach) {
    string maMoi;
    while (true) {
        try {
            cout << "Nhap ma hop dong: ";
            getline(cin, maMoi);

            // Nếu rỗng quăng lỗi văng xuống khối catch
            if (maMoi.empty()) {
                   throw invalid_argument("Ma khong duoc rong!");
                 }
                  ma = maMoi;

            // Nếu bị trùng, sẽ bị quăng xuống catch
            for (const HopDong& hd : danhSach) {
                if (hd.ma == maMoi) {
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

    string maNew;
    while (true) {
        try {
            cout << "Nhap ma khach hang: ";
            getline(cin, maNew);

            // Nếu rỗng quăng lỗi văng xuống khối catch
            if (maNew.empty()) {
                   throw invalid_argument("Ma khong duoc rong!");
                 }
                  ma = maNew;

            // Nếu bị trùng, sẽ bị quăng xuống catch
            for (const HopDong& hd : danhSach) {
                if (hd.maKH == maNew) {
                    throw invalid_argument("Loi: Ma hop dong '" + maNew + "' da ton tai!");
                }
            }

            // Nếu không có lỗi nào bị throw, thoát khỏi vòng lặp nhập mã
            break;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << " Vui long nhap lai.\n";
        }
    }


    while(1)
    {cout << "Nhap ten thue bao dang ki : ";
     getline(cin, tenGoi);
     if(tenGoi.empty())cout<<"Ten thue bao khong duoc de trong !\n"; else break;
    }




    cout << "Nhap so tien con no (VND): ";
    cin >> Nocuoc;
    // Bổ sung kiểm tra khi nhập Hạn mức không phải số
    while (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << " So no phai la so, vui long nhap lai: ";
        cin >> Nocuoc;
    }
    cin.ignore(); // Xóa ký tự '\n' còn đệm


}

// 2. HAM IN TOAN BO THUE BAO
void HopDong::xuat(const vector<HopDong>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach thue bao hien dang rong!\n\n";
        return;
    }

    cout << "\n-------------------------------------------------------------------------\n";
    cout << "| " << left << setw(12) << "Ma hop dong"
         << "| " << left << setw(18) << "Ma khach hang"
         << "| " << right << setw(12) << "Ten thue bao" << " | "
         << left << setw(20) << "Tien no cuoc" << " |\n";
    cout << "-------------------------------------------------------------------------\n";

    for (const HopDong& hd : danhSach) {
        cout << "| " << left << setw(12) << hd.ma
             << "| " << left << setw(18) << hd.maKH
             << "| " << right << setw(12) << hd.tenGoi << " | "
             << left << setw(20) << hd.Nocuoc << " |\n";
    }

    cout << "-------------------------------------------------------------------------\n";
    cout << "Tong so hop dong: " << danhSach.size() << "\n\n";
}

// 3. HAM TIM KIEM THEO MA (ĐÃ SỬA LỖI LOGIC)
void HopDong::tim(const vector<HopDong>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach hop dong hien dang rong! Khong the tim kiem.\n\n";
        return;
    }

    string TimKiem;
    cout << "\nHay nhap ma muon tim kiem: ";
    getline(cin, TimKiem);

    bool TimThay = false;

    for (const HopDong& hd : danhSach) {
        if (hd.ma == TimKiem) {
            TimThay = true;

            // In bảng khi tìm thấy
           cout << "\n-------------------------------------------------------------------------\n";
           cout << "| " << left << setw(12) << "Ma hop dong"
                << "| " << left << setw(18) << "Ma khach hang"
                << "| " << right << setw(12) << "Ten thue bao" << " | "
                << left << setw(20) << "Gia tien" << " |\n";
           cout << "-------------------------------------------------------------------------\n";

           cout << "| " << left << setw(12) << hd.ma
             << "| " << left << setw(18) << hd.maKH
             << "| " << right << setw(12) << hd.tenGoi << " | "
             << left << setw(20) << hd.tenGoi << " |\n";

            cout << "-------------------------------------------------------------------------\n\n";
            break; // Tìm thấy thì dừng vòng lặp
        }
    }

    if (TimThay==false) {
        cout << "-> Khong tim thay thue bao co ma: " << TimKiem << "\n\n";
    }
}

// 4. HAM CAP NHAT / SUA THONG TIN THUE BAO
void HopDong::sua(vector<HopDong>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach hop dong hien dang rong! Khong the cap nhat.\n\n";
        return;
    }

    string maTim;
    cout << "\nNhap ma hop dong can sua thong tin: ";
    getline(cin, maTim);

    // Tìm thuê bao theo mã trong danh sách
    HopDong* hdFound = nullptr;
    for (HopDong& hd : danhSach) {
        if (hd.ma == maTim) { // Sử dụng getMa() nếu ma là private
            hdFound = &hd;
            break;
        }
    }

    // Nếu không tìm thấy
    if (hdFound == nullptr) {
        cout << "-> Khong tim thay hop dong co ma: " << maTim << "\n\n";
        return;
    }

    // Hiển thị thông tin hiện tại
    cout << "(Notice: Nhan Enter neu muon giu nguyen thong tin cu)\n\n";

    // 1. Cập nhật ma khach hang

    string inputStr;
    int    inputInt;
    cout << "Nhap Ma Khach Hang moi : ";
    getline(cin, inputStr);
    if (!inputStr.empty()) {
        hdFound->maKH = inputStr;
    }



    // 2. Cập nhật tên gói mới
    cout << "Nhap ten goi moi [" << hdFound->tenGoi << "]: ";
    getline(cin, inputStr);
    if (!inputStr.empty()) {
        hdFound->tenGoi = inputStr;
    }

    cout << "\n-> Cap nhat thong tin hop dong thanh cong!\n\n";

    // 2. Cập nhật giá mới

    while(1)
     {  cout << "Nhap tien no cuoc moi(VND) : ";
        getline(cin, inputStr);
        try {
            double GiatienMoi = stod(inputStr); // Chuyển chuỗi sang kiểu số double
            if (GiatienMoi >= 0) {
                {hdFound->Nocuoc = GiatienMoi;break;}
            } else {
                cout << "-> So tien khong hop le (phai >= 0). Vui long nhap lai so tien.\n";
            }
        } catch (...) {
            cout << "-> Du lieu nhap vao khong phai la so. Vui long nhap lai so tien.\n";
        }
    }


}

// 5.HÀM XÓA THUE BAO THEO MA
void HopDong::xoa(vector<HopDong>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach hop dong hien dang rong, khong the xoa!\n\n";
        return;
    }

    string maXoa;
    while (true) {
        cout << "Nhap ma hop dong can xoa (Nhan ENTER de huy): ";
        getline(cin, maXoa);

        // 1. Nếu nhấn Enter (mã rỗng) -> Hủy thao tác xóa
        if (maXoa.empty()) {
            cout << "-> Da huy thao tac xoa hop dong.\n\n";
            return;
        }

        // 2. Tìm mã trong danh sách
        bool timThay = false;
        for (auto ers = danhSach.begin(); ers != danhSach.end();ers ++) {
            if (ers->ma == maXoa) {
                timThay = true;

                // Xác nhận xóa
                char xacNhan;
                cout << "Ban co chac chan muon xoa hop dong '" << maXoa << "'? (Y/N): ";
                cin >> xacNhan;
                cin.ignore(); // Xóa ký tự '\n' đệm

                if (xacNhan == 'Y' || xacNhan == 'y') {
                    danhSach.erase(ers);
                    cout << "-> Xoa hop dong thanh cong!\n\n";
                } else {
                    cout << "-> Da huy thao tac xoa.\n\n";
                }

                return; // Xóa hoặc hủy xong thì thoát hàm luôn
            }
        }

        // 3. Nếu không tìm thấy mã -> Báo lỗi và vòng lặp while sẽ bắt nhập lại
        if (!timThay) {
            cout << "-> Loi: Ma hop dong '" << maXoa << "' khong ton tai trong danh sach! Vui long nhap lai.\n\n";
        }
    }
}

          // Hàm lưu file

void HopDong::luuFile(const vector<HopDong>& danhSach) {
    fstream fs;
    // Mở file
    fs.open("data\\HopDong.txt");
    //Kiểm tra file có lỗi khi mở không
    if (!fs.is_open()) {
        cout << "-> Canh bao: Khong the mo file de ghi du lieu! (Kiểm tra thu muc 'data')\n";
        return ;
    }

    fs << "# MaHopDong|MaKhachHang|TenThueBao|GiaNoCuoc\n";

    for (const HopDong& hd : danhSach) {
             fs << hd.ma << "|"
                << hd.maKH << "|"
                << hd.tenGoi << "|"
                << hd.Nocuoc << "\n";
    }

    fs.close();
}

// Hàm đọc file
void HopDong::docFile(vector<HopDong>& danhSach) {
    fstream fs;
    fs.open("data\\Hopdong.txt", ios::in);

    // Nếu file chưa tồn tại thì tạo file rỗng
    if (!fs.is_open()) {
        ofstream fs("data\\HopDong.txt");
        fs.close();
        return;
    }

    danhSach.clear();

    string line;
    while (getline(fs, line)) {
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);
        string ma, KH, TB, giastr;

        if (getline(ss, ma, '|') &&
            getline(ss, KH, '|') &&
            getline(ss, TB, '|') &&
            getline(ss, giastr)) {

            try {
                size_t pos;
                double  Nocuoc= stod(giastr, &pos);

                if (ma.empty()||Nocuoc <0||TB.empty()||KH.empty()||giastr.empty()||pos!=giastr.length())
                    {cout << "\nDu lieu: " << line <<" khong hop le\n";continue;}

                danhSach.push_back(
                    HopDong(ma, KH, TB, Nocuoc)
                );
            }
            catch (...) {
                cout << "\nDu lieu: " << line <<" khong hop le\n";
            }
        }
       else cout << "\nDu lieu: " << line <<" khong hop le\n";
}


    fs.close();
}

