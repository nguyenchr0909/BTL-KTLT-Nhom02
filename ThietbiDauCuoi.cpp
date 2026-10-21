#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "ThietbiDauCuoi.h"

using namespace std;

// ==================== LỚP THIETBIDAUCUOI ====================

void ThietBiDauCuoi::nhapThongTin() {
    cout << "Nhap ma thiet bi: ";
    getline(cin >> ws, ma);

    cout << "Nhap loai thiet bi (VD: Modem, Router, TV Box...): ";
    getline(cin, loaiThietBi);

    cout << "Nhap tinh trang (VD: Moi, Cu, Dang cho thue...): ";
    getline(cin, tinhTrang);

    while (true) {
        try {
            cout << "Nhap gia ban/cho thue: ";
            double gia;
            cin >> gia;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw invalid_argument("Loi: Phai nhap kieu so!");
            }
            setGiaBan(gia);
            cin.ignore();
            break;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
}

void ThietBiDauCuoi::display() {
    cout << "| " << setw(10) << left << ma
         << "| " << setw(20) << left << loaiThietBi
         << "| " << setw(18) << left << tinhTrang
         << "| " << setw(12) << right << giaBan << " |\n";
}

string ThietBiDauCuoi::taoChuoiLuuFile() const {
    stringstream ss;
    ss << ma << "|" << loaiThietBi << "|" << tinhTrang << "|" << giaBan;
    return ss.str();
}

void ThietBiDauCuoi::docTuChuoi(const string& dongDuLieu) {
    stringstream ss(dongDuLieu);
    string giaStr;
    getline(ss, ma, '|');
    getline(ss, loaiThietBi, '|');
    getline(ss, tinhTrang, '|');
    getline(ss, giaStr, '|');

    stringstream(giaStr) >> giaBan;
}

// ==================== LỚP QUANLYTHIETBIDAUCUOI ====================

void QuanLyThietBiDauCuoi::docFile() {
    danhSach.clear();
    ifstream file(tenFile);
    if (!file.is_open()) return;

    string dong;
    while (getline(file, dong)) {
        if (dong.empty()) continue;
        ThietBiDauCuoi tb;
        tb.docTuChuoi(dong);
        danhSach.push_back(tb);
    }
    file.close();
}

void QuanLyThietBiDauCuoi::ghiFile() {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cout << "Loi: Khong mo duoc file de ghi (Kiem tra da tao thu muc 'data' chua?)\n";
        return;
    }
    for (size_t i = 0; i < danhSach.size(); i++) {
        file << danhSach[i].taoChuoiLuuFile() << "\n";
    }
    file.close();
}

void QuanLyThietBiDauCuoi::themThietBi() {
    ThietBiDauCuoi tb;
    tb.nhapThongTin();

    for (size_t i = 0; i < danhSach.size(); i++) {
        if (danhSach[i].getMa() == tb.getMa()) {
            cout << "Loi: Ma thiet bi da ton tai!\n";
            return;
        }
    }

    danhSach.push_back(tb);
    ghiFile();
    cout << "=> Them thiet bi thanh cong!\n";
}

void QuanLyThietBiDauCuoi::xemDanhSach() {
    if (danhSach.empty()) {
        cout << "Danh sach trong!\n";
        return;
    }
    cout << string(68, '-') << "\n";
    cout << "| " << setw(10) << left << "Ma TB"
         << "| " << setw(20) << left << "Loai Thiet Bi"
         << "| " << setw(18) << left << "Tinh Trang"
         << "| " << setw(12) << right << "Gia Ban" << " |\n";
    cout << string(68, '-') << "\n";
    for (size_t i = 0; i < danhSach.size(); i++) {
        danhSach[i].display();
    }
    cout << string(68, '-') << "\n";
}

void QuanLyThietBiDauCuoi::timKiemThietBi() {
    string maTim;
    cout << "Nhap ma thiet bi can tim: ";
    getline(cin >> ws, maTim);

    for (size_t i = 0; i < danhSach.size(); i++) {
        if (danhSach[i].getMa() == maTim) {
            cout << "\nThong tin thiet bi tim thay:\n";
            cout << string(68, '-') << "\n";
            danhSach[i].display();
            cout << string(68, '-') << "\n";
            return;
        }
    }
    cout << "Khong tim thay thiet bi!\n";
}

void QuanLyThietBiDauCuoi::suaThietBi() {
    string maTim;
    cout << "Nhap ma thiet bi can sua: ";
    getline(cin >> ws, maTim);

    for (size_t i = 0; i < danhSach.size(); i++) {
        if (danhSach[i].getMa() == maTim) {
            cout << "\nNhap thong tin moi cho thiet bi:\n";
            danhSach[i].nhapThongTin();
            ghiFile();
            cout << "=> Cap nhat thiet bi thanh cong!\n";
            return;
        }
    }
    cout << "Khong tim thay thiet bi!\n";
}

void QuanLyThietBiDauCuoi::xoaThietBi() {
    string maTim;
    cout << "Nhap ma thiet bi can xoa: ";
    getline(cin >> ws, maTim);

    for (size_t i = 0; i < danhSach.size(); i++) {
        if (danhSach[i].getMa() == maTim) {
            danhSach.erase(danhSach.begin() + i);
            ghiFile();
            cout << "=> Xoa thiet bi thanh cong!\n";
            return;
        }
    }
    cout << "Khong tim thay thiet bi!\n";
}

void QuanLyThietBiDauCuoi::menu() {
    docFile();

    int chon = -1;
    while (chon != 0) {
        cout << "\n===== QUAN LY THIET BI DAU CUOI =====\n";
        cout << "1. Them thiet bi\n";
        cout << "2. Xem danh sach thiet bi\n";
        cout << "3. Tim kiem thiet bi\n";
        cout << "4. Sua thiet bi\n";
        cout << "5. Xoa thiet bi\n";
        cout << "0. Thoat\n";
        cout << "Chon chuc nang: ";

        cin >> chon;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            chon = -1;
        }

        switch (chon) {
            case 1: themThietBi(); break;
            case 2: xemDanhSach(); break;
            case 3: timKiemThietBi(); break;
            case 4: suaThietBi(); break;
            case 5: xoaThietBi(); break;
            case 0: cout << "Thoat...\n"; break;
            default: cout << "Chon sai, chon lai!\n";
        }
    }
}

// ==================== HAM LIENT HONG MAIN ====================

void runThietBiDauCuoi() {
    QuanLyThietBiDauCuoi ql;
    ql.menu();
}
