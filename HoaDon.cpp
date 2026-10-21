#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "HoaDon.h"

// ==================== LỚP HOADON ====================


void HoaDon::setMa(string _ma) {
    ma = _ma;
}

void HoaDon::setTongTien(double _tien) {
    if (_tien < 0) {
        throw invalid_argument("Loi: Tong tien khong duoc am!");
    }
    tongTien = _tien;
}

string HoaDon::getSoThueBao() const {
    return soThueBao;
}

string HoaDon::getTrangThai() const {
    return trangThai;
}

void HoaDon::nhapThongTin() {
    cout << "Nhap ma hoa don: ";
    getline(cin >> ws, ma);

    cout << "Nhap so thue bao: ";
    getline(cin, soThueBao);

    cout << "Nhap ky cuoc (VD: 03/2026): ";
    getline(cin, kyCuoc);

    while (true) {
        try {
            cout << "Nhap tong tien cuoc: ";
            double tien;
            cin >> tien;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw invalid_argument("Loi: Phai nhap kieu so!");
            }
            setTongTien(tien);
            cin.ignore();
            break;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
    trangThai = "Chua thanh toan";
}

void HoaDon::display() {
    cout << "| " << setw(8) << left << ma
         << "| " << setw(15) << left << soThueBao
         << "| " << setw(10) << left << kyCuoc
         << "| " << setw(10) << right << tongTien
         << "| " << setw(18) << left << trangThai << " |\n";
}

string HoaDon::taoChuoiLuuFile() const {
    stringstream ss;
    ss << ma << "|" << soThueBao << "|" << kyCuoc << "|" << tongTien << "|" << trangThai;
    return ss.str();
}

void HoaDon::docTuChuoi(string dongDuLieu) {
    stringstream ss(dongDuLieu);
    string tienStr;
    getline(ss, ma, '|');
    getline(ss, soThueBao, '|');
    getline(ss, kyCuoc, '|');
    getline(ss, tienStr, '|');
    getline(ss, trangThai, '|');

    stringstream(tienStr) >> tongTien;
}

void HoaDon::capNhatDaThanhToan() {
    trangThai = "Da thanh toan";
}

// ==================== LỚP QUANLYHOADON ====================

void QuanLyHoaDon::docFile() {
    danhSach.clear();
    ifstream file(tenFile);
    if (!file.is_open()) return;

    string dong;
    while (getline(file, dong)) {
        if (dong.empty()) continue;
        HoaDon hd;
        hd.docTuChuoi(dong);
        danhSach.push_back(hd);
    }
    file.close();
}

void QuanLyHoaDon::ghiFile() {
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

void QuanLyHoaDon::themHoaDon() {
    HoaDon hd;
    hd.nhapThongTin();

    for (size_t i = 0; i < danhSach.size(); i++) {
        if (danhSach[i].getMa() == hd.getMa()) {
            cout << "Loi: Ma hoa don da ton tai!\n";
            return;
        }
    }

    danhSach.push_back(hd);
    ghiFile();
    cout << "=> Them hoa don thanh cong!\n";
}

void QuanLyHoaDon::xemDanhSach() {
    if (danhSach.empty()) {
        cout << "Danh sach trong!\n";
        return;
    }
    cout << string(70, '-') << "\n";
    for (size_t i = 0; i < danhSach.size(); i++) {
        danhSach[i].display();
    }
    cout << string(70, '-') << "\n";
}

void QuanLyHoaDon::thuTienHoaDon() {
    string maTim;
    cout << "Nhap ma hoa don khach can thanh toan: ";
    getline(cin >> ws, maTim);

    for (size_t i = 0; i < danhSach.size(); i++) {
        if (danhSach[i].getMa() == maTim) {
            danhSach[i].capNhatDaThanhToan();
            ghiFile();
            cout << "=> Da cap nhat trang thai thanh toan!\n";
            return;
        }
    }
    cout << "Khong tim thay hoa don nay!\n";
}

void QuanLyHoaDon::xoaHoaDon() {
    string maTim;
    cout << "Nhap ma hoa don can xoa: ";
    getline(cin >> ws, maTim);

    for (size_t i = 0; i < danhSach.size(); i++) {
        if (danhSach[i].getMa() == maTim) {
            if (danhSach[i].getTrangThai() == "Chua thanh toan") {
                cout << "Tu choi: Hoa don chua thu tien, KHONG DUOC XOA!\n";
                return;
            }
            danhSach.erase(danhSach.begin() + i);
            ghiFile();
            cout << "=> Xoa thanh cong!\n";
            return;
        }
    }
    cout << "Khong tim thay hoa don!\n";
}

void QuanLyHoaDon::menu() {
    docFile();

    int chon = -1;
    while (chon != 0) {
        cout << "\n===== QUAN LY HOA DON =====\n";
        cout << "1. Them hoa don\n";
        cout << "2. Xem danh sach\n";
        cout << "3. Thu tien (Cap nhat trang thai)\n";
        cout << "4. Xoa hoa don (Luu y rang buoc)\n";
        cout << "0. Thoat\n";
        cout << "Chon chuc nang: ";

        cin >> chon;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            chon = -1;
        }

        switch (chon) {
            case 1: themHoaDon(); break;
            case 2: xemDanhSach(); break;
            case 3: thuTienHoaDon(); break;
            case 4: xoaHoaDon(); break;
            case 0: cout << "Thoat...\n"; break;
            default: cout << "Chon sai, chon lai!\n";
        }
    }
}

// ==================== HAM MAIN ====================

void runHoaDon() {
    QuanLyHoaDon ql;
    ql.menu();
    return;
}
