#include "BanGhiCuocGoi.h"

const string DATA_FILE_BANGHI = "data/cdrs.txt";

// ==================== KHỞI TẠO VÀ METHOD CỦA BANGHICUOCGOI ====================

BanGhiCuocGoi::BanGhiCuocGoi() : Entity(""), thoiLuong(0) {}

BanGhiCuocGoi::BanGhiCuocGoi(string ma, string goi, string nhan, string thoiDiemGoi, int luong) : Entity(ma) {
    setMaBanGhi(ma);
    setSoGoi(goi);
    setSoNhan(nhan);
    setThoiDiem(thoiDiemGoi);
    setThoiLuong(luong);
}

void BanGhiCuocGoi::setMaBanGhi(string ma) {
    if (ma.empty()) throw invalid_argument("Ma ban ghi cuoc goi khong duoc de trong!");
    maBanGhi = ma;
    this->ma = ma; // Dong bo voi thuoc tinh ma cua Entity
}

void BanGhiCuocGoi::setSoGoi(string goi) {
    if (goi.empty()) throw invalid_argument("So goi (Caller) khong duoc de trong!");
    soGoi = goi;
}

void BanGhiCuocGoi::setSoNhan(string nhan) {
    if (nhan.empty()) throw invalid_argument("So nhan (Callee) khong duoc de trong!");
    soNhan = nhan;
}

void BanGhiCuocGoi::setThoiDiem(string td) {
    if (td.empty()) throw invalid_argument("Thoi diem bat dau khong duoc de trong!");
    thoiDiem = td;
}

void BanGhiCuocGoi::setThoiLuong(int luong) {
    if (luong <= 0) throw invalid_argument("Thoi luong goi phai lon hon 0 giay!");
    thoiLuong = luong;
}

string BanGhiCuocGoi::getMaBanGhi() const { return maBanGhi; }
string BanGhiCuocGoi::getSoGoi() const { return soGoi; }
string BanGhiCuocGoi::getSoNhan() const { return soNhan; }
string BanGhiCuocGoi::getThoiDiem() const { return thoiDiem; }
int BanGhiCuocGoi::getThoiLuong() const { return thoiLuong; }

void BanGhiCuocGoi::input() {
    cout << "Nhap ma ban ghi cuoc goi (VD: CDR001): ";
    string ma; cin >> ma;
    setMaBanGhi(ma);

    cout << "Nhap so goi (Caller): ";
    cin >> soGoi;
    setSoGoi(soGoi);

    cout << "Nhap so nhan (Callee): ";
    cin >> soNhan;
    if (soGoi == soNhan) {
        throw invalid_argument("So goi va so nhan phai khac nhau!");
    }
    setSoNhan(soNhan);

    cout << "Nhap thoi diem bat dau (VD: 11/03/2026_01:25:20): ";
    cin.ignore();
    getline(cin, thoiDiem);
    setThoiDiem(thoiDiem);

    int luong;
    cout << "Nhap thoi luong goi (so giay > 0): ";
    if (!(cin >> luong)) throw ios_base::failure("Loi dinh dang thoi luong!");
    setThoiLuong(luong);
}

void BanGhiCuocGoi::display() {
    cout << left << setw(12) << maBanGhi
         << setw(15) << soGoi
         << setw(15) << soNhan
         << setw(22) << thoiDiem
         << setw(12) << thoiLuong << "\n";
}

string BanGhiCuocGoi::toString() const {
    return maBanGhi + "|" + soGoi + "|" + soNhan + "|" + thoiDiem + "|" + to_string(thoiLuong);
}

// ==================== CÁC HÀM XỬ LÝ FILE ====================

static vector<string> splitBanGhi(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<BanGhiCuocGoi> loadBanGhiCuocGois() {
    vector<BanGhiCuocGoi> dsBanGhi;
    ifstream file(DATA_FILE_BANGHI);
    if (!file.is_open()) return dsBanGhi;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        vector<string> parts = splitBanGhi(line, '|');
        if (parts.size() == 5) {
            try {
                BanGhiCuocGoi c(parts[0], parts[1], parts[2], parts[3], stoi(parts[4]));
                dsBanGhi.push_back(c);
            } catch (...) {}
        }
    }
    file.close();
    return dsBanGhi;
}

void saveBanGhiCuocGois(const vector<BanGhiCuocGoi> &dsBanGhi) {
    ofstream file(DATA_FILE_BANGHI);
    for (const auto &c : dsBanGhi) {
        file << c.toString() << "\n";
    }
    file.close();
}

// ==================== CÁC HÀM QUẢN LÝ (CRUD) ====================

void createBanGhiCuocGoi() {
    cout << "\n--- THEM MOI BAN GHI CUOC GOI ---\n";
    try {
        vector<BanGhiCuocGoi> dsBanGhi = loadBanGhiCuocGois();
        BanGhiCuocGoi newBanGhi;
        newBanGhi.input();

        for (const auto &c : dsBanGhi) {
            if (c.getMaBanGhi() == newBanGhi.getMaBanGhi()) {
                throw runtime_error("Ma ban ghi cuoc goi da ton tai trong he thong!");
            }
        }

        dsBanGhi.push_back(newBanGhi);
        saveBanGhiCuocGois(dsBanGhi);
        cout << "Them ban ghi cuoc goi thanh cong!\n";
    } catch (const exception &e) {
        cout << "[Ngoai le] " << e.what() << "\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void readBanGhiCuocGois() {
    vector<BanGhiCuocGoi> dsBanGhi = loadBanGhiCuocGois();
    if (dsBanGhi.empty()) {
        cout << "\nDanh sach ban ghi cuoc goi trong!\n";
        return;
    }
    cout << "\n--- DANH SACH LICH SU CUOC GOI ---\n";
    cout << left << setw(12) << "Ma Ban Ghi"
         << setw(15) << "So goi"
         << setw(15) << "So nhan"
         << setw(22) << "Thoi diem"
         << setw(12) << "Thoi luong(s)" << "\n";
    cout << string(76, '-') << "\n";

    for (auto &c : dsBanGhi) {
        c.display();
    }

    int choice;
    cout << "\nChon chuc nang tim kiem:\n1. Tim cuoc goi di cua mot so thue bao\n2. Tim cuoc goi co thoi luong lon hon X phut\n3. Thoat\nLua chon: ";
    cin >> choice;

    if (choice == 1) {
        string sdt;
        cout << "Nhap so thue bao can tra cuu cuoc goi di: ";
        cin >> sdt;
        bool found = false;
        cout << "\nCac cuoc goi di tu so " << sdt << ":\n";
        for (auto &c : dsBanGhi) {
            if (c.getSoGoi() == sdt) {
                c.display();
                found = true;
            }
        }
        if (!found) cout << "Khong tim thay cuoc goi di nao tu so nay!\n";
    } else if (choice == 2) {
        double xPhut;
        cout << "Nhap so phut toi thieu (X): ";
        cin >> xPhut;
        int xGiay = xPhut * 60;
        bool found = false;
        cout << "\nCac cuoc goi co thoi luong lon hon " << xPhut << " phut:\n";
        for (auto &c : dsBanGhi) {
            if (c.getThoiLuong() > xGiay) {
                c.display();
                found = true;
            }
        }
        if (!found) cout << "Khong co cuoc goi nao dai hon " << xPhut << " phut!\n";
    }
}

void updateBanGhiCuocGoi() {
    cout << "\n--- CAP NHAT BAN GHI CUOC GOI ---\n";
    vector<BanGhiCuocGoi> dsBanGhi = loadBanGhiCuocGois();
    string ma;
    cout << "Nhap ma ban ghi cuoc goi can sua: ";
    cin >> ma;

    int index = -1;
    for (size_t i = 0; i < dsBanGhi.size(); i++) {
        if (dsBanGhi[i].getMaBanGhi() == ma) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Khong tim thay ma ban ghi cuoc goi nay!\n";
        return;
    }

    try {
        int newLuong;
        cout << "Thoi luong moi (giay) [Hien tai: " << dsBanGhi[index].getThoiLuong() << "] (Nhap -1 de giu nguyen): ";
        cin >> newLuong;
        if (newLuong > 0) {
            dsBanGhi[index].setThoiLuong(newLuong);
        }

        saveBanGhiCuocGois(dsBanGhi);
        cout << "Cap nhat ban ghi cuoc goi thanh cong!\n";
    } catch (const exception &e) {
        cout << "[Ngoai le] " << e.what() << "\n";
    }
}

void deleteBanGhiCuocGoi() {
    cout << "\n--- XOA BAN GHI CUOC GOI ---\n";
    vector<BanGhiCuocGoi> dsBanGhi = loadBanGhiCuocGois();
    string ma;
    cout << "Nhap ma ban ghi cuoc goi can xoa: ";
    cin >> ma;

    int index = -1;
    for (size_t i = 0; i < dsBanGhi.size(); i++) {
        if (dsBanGhi[i].getMaBanGhi() == ma) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Khong tim thay ma ban ghi cuoc goi nay!\n";
        return;
    }

    cout << "Thong tin ban ghi can xoa: ";
    dsBanGhi[index].display();

    char confirm;
    cout << "Ban co chac chan muon xoa ban ghi nay khong? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        dsBanGhi.erase(dsBanGhi.begin() + index);
        saveBanGhiCuocGois(dsBanGhi);
        cout << "Da xoa thanh cong!\n";
    } else {
        cout << "Da huy thao tac.\n";
    }
}

// ==================== HÀM THI CÔNG MENU CHÍNH ====================

void runBanGhiCuocGoi() {
    int choice;
    do {
        cout << "\n===== QUAN LY BAN GHI CUOC GOI =====\n";
        cout << "1. Them moi ban ghi (Create)\n";
        cout << "2. Xem lich su va tim kiem (Read)\n";
        cout << "3. Cap nhat ban ghi (Update)\n";
        cout << "4. Xoa ban ghi (Delete)\n";
        cout << "0. Quay lai / Thoat\n";
        cout << "Nhap: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: createBanGhiCuocGoi(); break;
            case 2: readBanGhiCuocGois(); break;
            case 3: updateBanGhiCuocGoi(); break;
            case 4: deleteBanGhiCuocGoi(); break;
            case 0: cout << "Quay lai menu chinh...\n"; break;
            default: cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

void RunBanGhiCuocGoi() {
    runBanGhiCuocGoi();
}
