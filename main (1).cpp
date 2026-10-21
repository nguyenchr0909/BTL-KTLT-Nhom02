#include "cdr.h"

void createCDR() {
    cout << "\n--- THEM MOI BAN GHI ---\n";
    try {
        vector<CDR> cdrs = loadCDRs();
        CDR newCdr;
        newCdr.input();

        for (const auto &c : cdrs) {
            if (c.getMaCDR() == newCdr.getMaCDR()) {
                throw runtime_error("Ma CDR đa ton tai trong he thong!");
            }
        }

        cdrs.push_back(newCdr);
        saveCDRs(cdrs);
        cout << "Them ban ghi CDR thanh cong!\n";
    } catch (const exception &e) {
        cout << "[Ngoai le] " << e.what() << "\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void readCDRs() {
    vector<CDR> cdrs = loadCDRs();
    if (cdrs.empty()) {
        cout << "\nDanh sach ban ghi CDR trốog!\n";
        return;
    }
    cout << "\n--- DANH SÁCH LiCH Su CUoC goi ---\n";
    cout << left << setw(10) << "Ma CDR" 
         << setw(15) << "So goi" 
         << setw(15) << "So nhan" 
         << setw(22) << "Thoi điem" 
         << setw(12) << "Thoi luong(s)" << "\n";
    cout << string(74, '-') << "\n";

    for (const auto &c : cdrs) {
        c.display();
    }

    int choice;
    cout << "\nChon chuc nang tim kiem:\n1. Tim cuoc goi di cua mot so thue bao\n2. Tim cuoc goi co thoi lưong lon hon X phut\n3. Thoat\nLựa chọn: ";
    cin >> choice;

    if (choice == 1) {
        string sdt;
        cout << "Nhap so thue bao can tra cuu cuộc goi di: ";
        cin >> sdt;
        bool found = false;
        cout << "\nCac cuoc goi di tu so " << sdt << ":\n";
        for (const auto &c : cdrs) {
            if (c.getSoGoi() == sdt) {
                c.display();
                found = true;
            }
        }
        if (!found) cout << "Khong tim thay cuoc goi di nAo tu so nay!\n";
    } else if (choice == 2) {
        double xPhut;
        cout << "Nhap so phut toi thieu (X): ";
        cin >> xPhut;
        int xGiay = xPhut * 60;
        bool found = false;
        cout << "\nCac cuoc goi co thoi lưong lon hơn " << xPhut << " phut:\n";
        for (const auto &c : cdrs) {
            if (c.getThoiLuong() > xGiay) {
                c.display();
                found = true;
            }
        }
        if (!found) cout << "Khong co cuoc goi nao dai hon " << xPhut << " phut!\n";
    }
}

void updateCDR() {
    cout << "\n--- CAP NHAT BAN GHI ---\n";
    vector<CDR> cdrs = loadCDRs();
    string ma;
    cout << "Nhap ma CDR can sua: ";
    cin >> ma;

    int index = -1;
    for (size_t i = 0; i < cdrs.size(); i++) {
        if (cdrs[i].getMaCDR() == ma) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Khong tim thay ma CDR nay!\n";
        return;
    }

    try {
        int newLuong;
        cout << "Thoi lưong moi (giay) [Hien tai: " << cdrs[index].getThoiLuong() << "] (Nhap -1 de giu nguyen): ";
        cin >> newLuong;
        if (newLuong > 0) {
            cdrs[index].setThoiLuong(newLuong);
        }

        saveCDRs(cdrs);
        cout << "Cap nhat ban ghi thanh cong!\n";
    } catch (const exception &e) {
        cout << "[Ngoai le] " << e.what() << "\n";
    }
}

void deleteCDR() {
    cout << "\n--- XOA BAN GHI CDR ---\n";
    vector<CDR> cdrs = loadCDRs();
    string ma;
    cout << "NhAp mA CDR cAn xoa: ";
    cin >> ma;

    int index = -1;
    for (size_t i = 0; i < cdrs.size(); i++) {
        if (cdrs[i].getMaCDR() == ma) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Khong tim thay ma CDR nay!\n";
        return;
    }

    cout << "Thong tin ban ghi can xoa: ";
    cdrs[index].display();

    char confirm;
    cout << "Ban co chac chan muon xoa ban ghi nay khong? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        cdrs.erase(cdrs.begin() + index);
        saveCDRs(cdrs);
        cout << "da xoa thanh cong!\n";
    } else {
        cout << "da huy thao tac.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n===== QUAN LY BAN GHI CUOC GOI - CDR =====\n";
        cout << "1. Them moi ban ghi (Create)\n";
        cout << "2. Xem lich su va tim kiem (Read)\n";
        cout << "3. Cap nhat ban ghi (Update)\n";
        cout << "4. Xoa ban ghi (Delete)\n";
        cout << "0. Thoat\n";
        cout << "Nhap: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: createCDR(); break;
            case 2: readCDRs(); break;
            case 3: updateCDR(); break;
            case 4: deleteCDR(); break;
            case 0: cout << "Tam biet!\n"; break;
            default: cout << " khong hop le!\n";
        }
    } while (choice != 0);

    return 0;
}