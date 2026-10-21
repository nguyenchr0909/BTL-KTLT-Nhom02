#include "HopDong.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <ctype.h>

using namespace std;

void HopDong::display() {
    cout << "\n";
    cout << "============ QUAN LY HOP DONG DANG KI THUE BAO ============\n";
    cout << "  1. Them hop dong moi\n";
    cout << "  2. Xem danh sach hop dong\n";
    cout << "  3. Tim kiem hop dong\n";
    cout << "  4. Cap nhat thong tin hop dong\n";
    cout << "  5. Xoa hop dong\n";
    cout << "  0. Quay lai\n";
    cout << "==========================================\n";
    cout << "Nhap lua chon: ";
}

void runHopDong() {
    vector<HopDong> danhSach;
    HopDong::docFile(danhSach);
    int choice = -1;
    HopDong x;
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
            HopDong hd;
            hd.nhap(danhSach);
            danhSach.push_back(hd);
            cout << "-> Them hop dong thanh cong!\n\n";
            HopDong::luuFile(danhSach);
        }

        if (choice == 2) {
            HopDong::xuat(danhSach);
        }

        if (choice == 3) {
            HopDong::tim(danhSach);
        }

        if (choice == 4) {
            HopDong::sua(danhSach);
            HopDong::luuFile(danhSach);
        }

        if (choice == 5) {
            HopDong::xoa(danhSach);
            HopDong::luuFile(danhSach);
        }
    }
}

// 1. NHẬP DỮ LIỆU HỢP ĐỒNG
void HopDong::nhap(const vector<HopDong>& danhSach) {
    string maMoi;
    while (true) {
        try {
            cout << "Nhap ma hop dong: ";
            getline(cin, maMoi);

            if (maMoi.empty()) {
                throw invalid_argument("Ma hop dong khong duoc de trong!");
            }

            for (const HopDong& hd : danhSach) {
                if (hd.getMa() == maMoi) {
                    throw invalid_argument("Loi: Ma hop dong '" + maMoi + "' da ton tai!");
                }
            }

            setMa(maMoi); // Kiểm soát qua Setter
            break;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << " Vui long nhap lai.\n";
        }
    }

    string maKHInput;
    while (true) {
        try {
            cout << "Nhap ma khach hang: ";
            getline(cin, maKHInput);

            if (maKHInput.empty()) {
                throw invalid_argument("Ma khach hang khong duoc de trong!");
            }

            setMaKH(maKHInput); // Kiểm soát qua Setter
            break;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << " Vui long nhap lai.\n";
        }
    }

    string tenGoiInput;
    while (true) {
        cout << "Nhap ten thue bao dang ki: ";
        getline(cin, tenGoiInput);
        if (tenGoiInput.empty()) {
            cout << "Ten thue bao khong duoc de trong!\n";
        } else {
            setTenGoi(tenGoiInput); // Kiểm soát qua Setter
            break;
        }
    }

    double moneyInput;
    cout << "Nhap so tien con no (VND): ";
    cin >> moneyInput;
    while (cin.fail() || moneyInput < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "So no phai la so >= 0, vui long nhap lai: ";
        cin >> moneyInput;
    }
    setNocuoc(moneyInput); // Kiểm soát qua Setter
    cin.ignore();
}

// 2. HÀM IN TOÀN BỘ HỢP ĐỒNG
void HopDong::xuat(const vector<HopDong>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach hop dong hien dang rong!\n\n";
        return;
    }

    cout << "\n-------------------------------------------------------------------------\n";
    cout << "| " << left << setw(12) << "Ma hop dong"
         << "| " << left << setw(18) << "Ma khach hang"
         << "| " << left << setw(18) << "Ten thue bao" << " | "
         << left << setw(16) << "Tien no cuoc" << " |\n";
    cout << "-------------------------------------------------------------------------\n";

    for (const HopDong& hd : danhSach) {
        cout << "| " << left << setw(12) << hd.getMa()
             << "| " << left << setw(18) << hd.getMaKH()
             << "| " << left << setw(18) << hd.getTenGoi() << " | "
             << right << setw(16) << hd.getNocuoc() << " |\n";
    }

    cout << "-------------------------------------------------------------------------\n";
    cout << "Tong so hop dong: " << danhSach.size() << "\n\n";
}

// 3. HÀM TÌM KIẾM THEO MÃ
void HopDong::tim(const vector<HopDong>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach hop dong hien dang rong! Khong the tim kiem.\n\n";
        return;
    }

    string TimKiem;
    cout << "\nHay nhap ma hop dong muon tim kiem: ";
    getline(cin, TimKiem);

    bool TimThay = false;

    for (const HopDong& hd : danhSach) {
        if (hd.getMa() == TimKiem) {
            TimThay = true;

            cout << "\n-------------------------------------------------------------------------\n";
            cout << "| " << left << setw(12) << "Ma hop dong"
                 << "| " << left << setw(18) << "Ma khach hang"
                 << "| " << left << setw(18) << "Ten thue bao" << " | "
                 << left << setw(16) << "Tien no cuoc" << " |\n";
            cout << "-------------------------------------------------------------------------\n";

            cout << "| " << left << setw(12) << hd.getMa()
                 << "| " << left << setw(18) << hd.getMaKH()
                 << "| " << left << setw(18) << hd.getTenGoi() << " | "
                 << right << setw(16) << hd.getNocuoc() << " |\n";

            cout << "-------------------------------------------------------------------------\n\n";
            break;
        }
    }

    if (!TimThay) {
        cout << "-> Khong tim thay hop dong co ma: " << TimKiem << "\n\n";
    }
}

// 4. HÀM CẬP NHẬT / SỬA THÔNG TIN HỢP ĐỒNG
void HopDong::sua(vector<HopDong>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach hop dong hien dang rong! Khong the cap nhat.\n\n";
        return;
    }

    string maTim;
    cout << "\nNhap ma hop dong can sua thong tin: ";
    getline(cin, maTim);

    HopDong* hdFound = nullptr;
    for (HopDong& hd : danhSach) {
        if (hd.getMa() == maTim) {
            hdFound = &hd;
            break;
        }
    }

    if (hdFound == nullptr) {
        cout << "-> Khong tim thay hop dong co ma: " << maTim << "\n\n";
        return;
    }

    cout << "(Notice: Nhan Enter neu muon giu nguyen thong tin cu)\n\n";

    // 1. Cập nhật Mã khách hàng
    string inputStr;
    cout << "Nhap Ma Khach Hang moi [" << hdFound->getMaKH() << "]: ";
    getline(cin, inputStr);
    if (!inputStr.empty()) {
        hdFound->setMaKH(inputStr);
    }

    // 2. Cập nhật Tên gói / thuê bao
    cout << "Nhap ten goi/thue bao moi [" << hdFound->getTenGoi() << "]: ";
    getline(cin, inputStr);
    if (!inputStr.empty()) {
        hdFound->setTenGoi(inputStr);
    }

    // 3. Cập nhật Tiền nợ cước
    while (true) {
        cout << "Nhap tien no cuoc moi(VND) [" << hdFound->getNocuoc() << "]: ";
        getline(cin, inputStr);
        if (inputStr.empty()) break; // Giữ nguyên giá trị cũ

        try {
            double GiatienMoi = stod(inputStr);
            if (GiatienMoi >= 0) {
                hdFound->setNocuoc(GiatienMoi);
                break;
            } else {
                cout << "-> So tien khong hop le (phai >= 0). Vui long nhap lai.\n";
            }
        } catch (...) {
            cout << "-> Du lieu nhap vao khong phai la so. Vui long nhap lai.\n";
        }
    }

    cout << "\n-> Cap nhat thong tin hop dong thanh cong!\n\n";
}

// 5. HÀM XÓA HỢP ĐỒNG THEO MÃ
void HopDong::xoa(vector<HopDong>& danhSach) {
    if (danhSach.empty()) {
        cout << "\n-> Danh sach hop dong hien dang rong, khong the xoa!\n\n";
        return;
    }

    string maXoa;
    while (true) {
        cout << "Nhap ma hop dong can xoa (Nhan ENTER de huy): ";
        getline(cin, maXoa);

        if (maXoa.empty()) {
            cout << "-> Da huy thao tac xoa hop dong.\n\n";
            return;
        }

        bool timThay = false;
        for (auto ers = danhSach.begin(); ers != danhSach.end(); ++ers) {
            if (ers->getMa() == maXoa) {
                timThay = true;

                char xacNhan;
                cout << "Ban co chac chan muon xoa hop dong '" << maXoa << "'? (Y/N): ";
                cin >> xacNhan;
                cin.ignore();

                if (xacNhan == 'Y' || xacNhan == 'y') {
                    danhSach.erase(ers);
                    cout << "-> Xoa hop dong thanh cong!\n\n";
                } else {
                    cout << "-> Da huy thao tac xoa.\n\n";
                }

                return;
            }
        }

        if (!timThay) {
            cout << "-> Loi: Ma hop dong '" << maXoa << "' khong ton tai trong danh sach! Vui long nhap lai.\n\n";
        }
    }
}

// HÀM LƯU FILE
void HopDong::luuFile(const vector<HopDong>& danhSach) {
    fstream fs;
    fs.open("data\\Hopdong.txt", ios::out);
    if (!fs.is_open()) {
        cout << "-> Canh bao: Khong the mo file de ghi du lieu! (Kiem tra thu muc 'data')\n";
        return;
    }

    fs << "# MaHopDong|MaKhachHang|TenThueBao|GiaNoCuoc\n";

    for (const HopDong& hd : danhSach) {
        fs << hd.getMa() << "|"
           << hd.getMaKH() << "|"
           << hd.getTenGoi() << "|"
           << hd.getNocuoc() << "\n";
    }

    fs.close();
}

// HÀM ĐỌC FILE
void HopDong::docFile(vector<HopDong>& danhSach) {
    fstream fs;
    fs.open("data\\Hopdong.txt", ios::in);

    if (!fs.is_open()) {
        ofstream newFs("data\\Hopdong.txt");
        newFs.close();
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
                double Nocuoc = stod(giastr, &pos);

                if (ma.empty() || Nocuoc < 0 || TB.empty() || KH.empty() || giastr.empty() || pos != giastr.length()) {
                    cout << "\nDu lieu: " << line << " khong hop le\n";
                    continue;
                }

                danhSach.push_back(HopDong(ma, KH, TB, Nocuoc));
            }
            catch (...) {
                cout << "\nDu lieu: " << line << " khong hop le\n";
            }
        }
        else cout << "\nDu lieu: " << line << " khong hop le\n";
    }

    fs.close();
}
