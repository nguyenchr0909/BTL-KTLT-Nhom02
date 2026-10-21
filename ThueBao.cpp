#include "ThueBao.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <sstream>
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
    vector<ThueBao> danhSach;
    ThueBao::docFile(danhSach);
    int choice = -1;
    ThueBao x;
    while (choice != 0) {
        x.display();
        cin >> choice;

        while (cin.fail() || choice < 0 || choice > 5) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Lua chon khong hop le, hay nhap lai (0-5): ";
            cin >> choice;
        }
        cin.ignore();

        if (choice == 1) {
            ThueBao tb;
            tb.nhap(danhSach);
            danhSach.push_back(tb);
            cout << "-> Them thue bao thanh cong!\n\n";
            ThueBao::luuFile(danhSach);
        }

        if (choice == 2) {
            ThueBao::xuat(danhSach);
        }

        if (choice == 3) {
            ThueBao::tim(danhSach);
        }

        if (choice == 4) {
            ThueBao::sua(danhSach);
            ThueBao::luuFile(danhSach);
        }

        if (choice == 5) {
            ThueBao::xoa(danhSach);
            ThueBao::luuFile(danhSach);
        }
    }
}

// 1. NHẬP DỮ LIỆU THUÊ BAO
void ThueBao::nhap(const vector<ThueBao>& danhSach) {
    string maMoi;
    while (true) {
        try {
            cout << "Nhap ma thue bao(LH01): ";
            getline(cin, maMoi);

            if (maMoi.empty()) {
                throw invalid_argument("Ma khong duoc rong!");
            }

            for (const auto& tb : danhSach) {
                if (tb.getMa() == maMoi) {
                    throw invalid_argument("Loi: Ma thue bao '" + maMoi + "' da ton tai!");
                }
            }

            setMa(maMoi); // Sử dụng Setter
            break;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << " Vui long nhap lai.\n";
        }
    }

    string loaiInput;
    cout << "Nhap Loai Thue Bao(Tra truoc/Tra sau): ";
    getline(cin, loaiInput);
    setLoaiThueBao(loaiInput); // Sử dụng Setter

    double hanMucInput;
    cout << "Nhap Han muc(VND): ";
    cin >> hanMucInput;
    while (cin.fail() || hanMucInput < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Han muc phai la so >= 0, vui long nhap lai: ";
        cin >> hanMucInput;
    }
    setHanMuc(hanMucInput); // Sử dụng Setter
    cin.ignore();

    string uuDaiInput;
    cout << "Nhap uu dai(Khong co thi ghi 'Khong'): ";
    getline(cin, uuDaiInput);
    setUuDai(uuDaiInput); // Sử dụng Setter
}

// 2. HÀM IN TOÀN BỘ THUÊ BAO
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
        cout << "| " << left << setw(12) << tb.getMa()
             << "| " << left << setw(18) << tb.getLoaiThueBao()
             << "| " << right << setw(12) << tb.getHanMuc() << " | "
             << left << setw(20) << tb.getUuDai() << " |\n";
    }

    cout << "-------------------------------------------------------------------------\n";
    cout << "Tong so ban ghi: " << danhSach.size() << "\n\n";
}

// 3. HÀM TÌM KIẾM THEO MÃ
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
        if (tb.getMa() == TimKiem) {
            TimThay = true;

            cout << "\n-------------------------------------------------------------------------\n";
            cout << "| " << left << setw(12) << "Ma thue bao"
                 << "| " << left << setw(18) << "Loai thue bao"
                 << "| " << right << setw(12) << "Han muc" << " | "
                 << left << setw(20) << "Uu dai" << " |\n";
            cout << "-------------------------------------------------------------------------\n";

            cout << "| " << left << setw(12) << tb.getMa()
                 << "| " << left << setw(18) << tb.getLoaiThueBao()
                 << "| " << right << setw(12) << tb.getHanMuc() << " | "
                 << left << setw(20) << tb.getUuDai() << " |\n";

            cout << "-------------------------------------------------------------------------\n\n";
            break;
        }
    }

    if (!TimThay) {
        cout << "-> Khong tim thay thue bao co ma: " << TimKiem << "\n\n";
    }
}

// 4. HÀM CẬP NHẬT / SỬA THÔNG TIN THUÊ BAO
void ThueBao::sua(vector<ThueBao>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach thue bao hien dang rong! Khong the cap nhat.\n\n";
        return;
    }

    string maTim;
    cout << "\nNhap ma thue bao can sua thong tin: ";
    getline(cin, maTim);

    ThueBao* tbFound = nullptr;
    for (ThueBao& tb : danhSach) {
        if (tb.getMa() == maTim) {
            tbFound = &tb;
            break;
        }
    }

    if (tbFound == nullptr) {
        cout << "-> Khong tim thay thue bao co ma: " << maTim << "\n\n";
        return;
    }

    cout << "(Notice: Nhan Enter neu muon giu nguyen thong tin cu)\n\n";

    // 1. Cập nhật Loại thuê bao
    string inputStr;
    cout << "Nhap Loai thue bao moi [" << tbFound->getLoaiThueBao() << "]: ";
    getline(cin, inputStr);
    if (!inputStr.empty()) {
        tbFound->setLoaiThueBao(inputStr);
    }

    // 2. Cập nhật Hạn mức
    while (true) {
        cout << "Nhap Han muc moi [" << tbFound->getHanMuc() << "]: ";
        getline(cin, inputStr);
        if (inputStr.empty()) break; // Giữ nguyên thông tin cũ

        try {
            double hanMucMoi = stod(inputStr);
            if (hanMucMoi >= 0) {
                tbFound->setHanMuc(hanMucMoi);
                break;
            } else {
                cout << "-> Han muc khong hop le (phai >= 0). Vui long nhap lai.\n";
            }
        } catch (...) {
            cout << "-> Du lieu nhap vao khong phai la so. Vui long nhap lai.\n";
        }
    }

    // 3. Cập nhật Ưu đãi
    cout << "Nhap Uu dai moi [" << tbFound->getUuDai() << "]: ";
    getline(cin, inputStr);
    if (!inputStr.empty()) {
        tbFound->setUuDai(inputStr);
    }

    cout << "\n-> Cap nhat thong tin thue bao thanh cong!\n\n";
}

// 5. HÀM XÓA THUÊ BAO THEO MÃ
void ThueBao::xoa(vector<ThueBao>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach hien dang rong, khong the xoa!\n\n";
        return;
    }

    string maXoa;
    while (true) {
        cout << "Nhap ma thue bao can xoa (Nhan ENTER de huy): ";
        getline(cin, maXoa);

        if (maXoa.empty()) {
            cout << "-> Da huy thao tac xoa thue bao.\n\n";
            return;
        }

        bool timThay = false;
        for (auto ers = danhSach.begin(); ers != danhSach.end(); ++ers) {
            if (ers->getMa() == maXoa) {
                timThay = true;

                char xacNhan;
                cout << "Ban co chac chan muon xoa thue bao '" << maXoa << "'? (Y/N): ";
                cin >> xacNhan;
                cin.ignore();

                if (xacNhan == 'Y' || xacNhan == 'y') {
                    danhSach.erase(ers);
                    cout << "-> Xoa thue bao thanh cong!\n\n";
                } else {
                    cout << "-> Da huy thao tac xoa.\n\n";
                }

                return;
            }
        }

        if (!timThay) {
            cout << "-> Loi: Ma thue bao '" << maXoa << "' khong ton tai trong danh sach! Vui long nhap lai.\n\n";
        }
    }
}

// HÀM LƯU FILE
void ThueBao::luuFile(const vector<ThueBao>& danhSach) {
    fstream fs;
    fs.open("data\\Thuebao.txt", ios::out);
    if (!fs.is_open()) {
        cout << "-> Canh bao: Khong the mo file de ghi du lieu! (Kiem tra thu muc 'data')\n";
        return;
    }

    fs << "# MaThueBao|LoaiThueBao|HanMuc|UuDai\n";

    for (const ThueBao& tb : danhSach) {
        fs << tb.getMa() << "|"
           << tb.getLoaiThueBao() << "|"
           << tb.getHanMuc() << "|"
           << tb.getUuDai() << "\n";
    }

    fs.close();
}

// HÀM ĐỌC FILE
void ThueBao::docFile(vector<ThueBao>& danhSach) {
    fstream fs;
    fs.open("data\\Thuebao.txt", ios::in);

    if (!fs.is_open()) {
        ofstream newFs("data\\Thuebao.txt");
        newFs.close();
        return;
    }

    danhSach.clear();

    string line;
    while (getline(fs, line)) {
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

                if (ma.empty() || hanMuc < 0 || loai.empty() || hanMucStr.empty() || uuDai.empty() || pos != hanMucStr.length()) {
                    cout << "Du lieu: " << line << " khong hop le\n";
                    continue;
                }

                danhSach.push_back(ThueBao(ma, loai, hanMuc, uuDai));
            }
            catch (...) {
                cout << "Du lieu: " << line << " khong hop le\n";
            }
        }
        else cout << "Du lieu: " << line << " khong hop le\n";
    }

    fs.close();
}
