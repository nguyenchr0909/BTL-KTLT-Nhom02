#include "GoiCuoc.h"

const string DATA_FILE_PACKAGE = "data/goicuoc.txt";

// ==================== KHỞI TẠO VÀ METHOD CỦA PACKAGE ====================

Package::Package() : Entity(""), giaCuoc(0), dataGb(0), phutNoiMang(0), phutNgoaiMang(0) {}

Package::Package(string ma, string ten, double gia, double data, int noi, int ngoai) : Entity(ma) {
    setMaGoi(ma);
    setTenGoi(ten);
    setGiaCuoc(gia);
    setDataGb(data);
    setPhutNoiMang(noi);
    setPhutNgoaiMang(ngoai);
}

void Package::setMaGoi(string ma) {
    if(ma.empty()) throw invalid_argument("Ma goi khong duoc de trong!");
    maGoi = ma;
    this->ma = ma;
}

void Package::setTenGoi(string ten) {
    if(ten.empty()) throw invalid_argument("Ten goi khong duoc de trong!");
    tenGoi = ten;
}

void Package::setGiaCuoc(double gia) {
    if (gia < 0) throw invalid_argument("Gia cuoc phai lon hon hoac bang 0!");
    giaCuoc = gia;
}

void Package::setDataGb(double data) {
    if (data < 0) throw invalid_argument("Dung luong data phai lon hon hoac bang 0!");
    dataGb = data;
}

void Package::setPhutNoiMang(int noi) {
    if (noi < 0) throw invalid_argument("Phut goi noi mang khong duoc am!");
    phutNoiMang = noi;
}

void Package::setPhutNgoaiMang(int ngoai) {
    if (ngoai < 0) throw invalid_argument("Phut goi ngoai mang khong duoc am!");
    phutNgoaiMang = ngoai;
}

string Package::getMaGoi() const { return maGoi; }
string Package::getTenGoi() const { return tenGoi; }
double Package::getGiaCuoc() const { return giaCuoc; }
double Package::getDataGb() const { return dataGb; }
int Package::getPhutNoiMang() const { return phutNoiMang; }
int Package::getPhutNgoaiMang() const { return phutNgoaiMang; }

void Package::input() {
    cout << "Nhap ma goi (VD: GC01): ";
    string ma; cin >> ma;
    setMaGoi(ma);
    cout << "Nhap ten goi: ";
    cin.ignore();
    string ten; getline(cin, ten);
    setTenGoi(ten);
    double gia, data;
    cout << "Nhap gia cuoc: ";
    if (!(cin >> gia)) throw ios_base::failure("Loi: Gia cuoc nhap vao khong phai la so hop le!");
    setGiaCuoc(gia);
    cout << "Nhap dung luong data (GB): ";
    if (!(cin >> data)) throw ios_base::failure("Loi: Dung luong data khong phai la so hop le!");
    setDataGb(data);
    int noi, ngoai;
    cout << "Nhap phut goi noi mang: ";
    if (!(cin >> noi)) throw ios_base::failure("Loi: So phut noi mang khong hop le!");
    setPhutNoiMang(noi);
    cout << "Nhap phut goi ngoai mang: ";
    if (!(cin >> ngoai)) throw ios_base::failure("Loi: So phut ngoai mang khong hop le!");
    setPhutNgoaiMang(ngoai);
}

void Package::display() {
    cout << left << setw(10) << maGoi
         << setw(15) << tenGoi
         << setw(12) << giaCuoc
         << setw(12) << dataGb
         << setw(12) << phutNoiMang
         << setw(12) << phutNgoaiMang << "\n";
}

string Package::toString() const {
    return maGoi + "|" + tenGoi + "|" + to_string(giaCuoc) + "|" +
           to_string(dataGb) + "|" + to_string(phutNoiMang) + "|" + to_string(phutNgoaiMang);
}

// ==================== CÁC HÀM XỬ LÝ FILE ====================

static vector<string> splitPackage(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<Package> loadPackages() {
    vector<Package> packages;
    ifstream file(DATA_FILE_PACKAGE);
    if (!file.is_open()) return packages;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        vector<string> parts = splitPackage(line, '|');
        if (parts.size() == 6) {
            try {
                Package p(parts[0], parts[1], stod(parts[2]), stod(parts[3]), stoi(parts[4]), stoi(parts[5]));
                packages.push_back(p);
            } catch (...) {}
        }
    }
    file.close();
    return packages;
}

void savePackages(const vector<Package> &packages) {
    ofstream file(DATA_FILE_PACKAGE);
    for (const auto &p : packages) {
        file << p.toString() << "\n";
    }
    file.close();
}

// ==================== CÁC HÀM QL GÓI CƯỚC (CRUD) ====================

void createPackage() {
    cout << "\n--- THEM MOI GOI CUOC ---\n";
    try {
        vector<Package> packages = loadPackages();
        Package newPkg;
        newPkg.input();
        for (const auto &p : packages) {
            if (p.getMaGoi() == newPkg.getMaGoi()) {
                throw runtime_error("Loi: Ma goi cuoc da ton tai trong he thong!");
            }
        }
        packages.push_back(newPkg);
        savePackages(packages);
        cout << "Them goi cuoc thanh cong!\n";
    } catch (const exception &e) {
        cout << "[Ngoai le] " << e.what() << "\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void readPackages() {
    vector<Package> packages = loadPackages();
    if (packages.empty()) {
        cout << "\nDanh sach goi cuoc trong!\n";
        return;
    }

    cout << "\n--- DANH SACH GOI CUOC ---\n";
    cout << left << setw(10) << "Ma goi"
         << setw(15) << "Ten goi"
         << setw(12) << "Gia cuoc"
         << setw(12) << "Data(GB)"
         << setw(12) << "Noi mang"
         << setw(12) << "Ngoai mang" << "\n";
    cout << string(73, '-') << "\n";

    for (auto &p : packages) {
        p.display();
    }

    int choice;
    cout << "\nChon che do:\n1. Tim kiem theo ma goi\n2. Loc cac goi cuoc co gia <= X dong\n3. Thoat\nLua chon: ";
    cin >> choice;

    if (choice == 1) {
        string keyword;
        cout << "Nhap ma goi can tim: ";
        cin >> keyword;
        bool found = false;
        for (auto &p : packages) {
            if (p.getMaGoi().find(keyword) != string::npos) {
                p.display();
                found = true;
            }
        }
        if (!found) cout << "Khong tim thay goi cuoc phu hop!\n";
    } else if (choice == 2) {
        double x;
        cout << "Nhap muc gia toi da (X): ";
        cin >> x;
        bool found = false;
        for (auto &p : packages) {
            if (p.getGiaCuoc() <= x) {
                p.display();
                found = true;
            }
        }
        if (!found) cout << "Khong co goi cuoc nao co gia <= " << x << "!\n";
    }
}

void updatePackage() {
    cout << "\n--- CAP NHAT GOI CUOC ---\n";
    vector<Package> packages = loadPackages();
    string maGoi;
    cout << "Nhap ma goi can sua: ";
    cin >> maGoi;

    int index = -1;
    for (size_t i = 0; i < packages.size(); i++) {
        if (packages[i].getMaGoi() == maGoi) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Khong tim thay ma goi cuoc nay!\n";
        return;
    }

    try {
        string inputStr;
        cout << "Ten goi moi (hien tai: " << packages[index].getTenGoi() << ") [Nhap '-' de giu nguyen]: ";
        cin.ignore();
        getline(cin, inputStr);
        if (inputStr != "-" && !inputStr.empty()) {
            packages[index].setTenGoi(inputStr);
        }

        cout << "Gia cuoc moi (hien tai: " << packages[index].getGiaCuoc() << ") [-1 de giu nguyen]: ";
        double newGia;
        cin >> newGia;
        if (newGia >= 0) {
            packages[index].setGiaCuoc(newGia);
        }

        savePackages(packages);
        cout << "Cap nhat goi cuoc thanh cong!\n";
    } catch (const exception &e) {
        cout << "[Ngoai le] " << e.what() << "\n";
    }
}

void deletePackage() {
    cout << "\n--- XOA GOI CUOC ---\n";
    vector<Package> packages = loadPackages();
    string maGoi;
    cout << "Nhap ma goi can xoa: ";
    cin >> maGoi;

    int index = -1;
    for (size_t i = 0; i < packages.size(); i++) {
        if (packages[i].getMaGoi() == maGoi) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Khong tim thay ma goi cuoc nay!\n";
        return;
    }

    cout << "Thong tin goi: ";
    packages[index].display();

    char confirm;
    cout << "Co chac chan muon xoa goi cuoc nay khong? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        packages.erase(packages.begin() + index);
        savePackages(packages);
        cout << "Da xoa goi cuoc thanh cong!\n";
    } else {
        cout << "Da huy thao tac xoa.\n";
    }
}

// ==================== HÀM THI CÔNG MENU CHÍNH ====================

void runGoiCuoc() {
    int choice;
    do {
        cout << "\n===== QUAN LY GOI CUOC =====\n";
        cout << "1. Them moi goi cuoc (Create)\n";
        cout << "2. Xem va tim kiem goi cuoc (Read)\n";
        cout << "3. Cap nhat goi cuoc (Update)\n";
        cout << "4. Xoa goi cuoc (Delete)\n";
        cout << "0. Quay lai / Thoat\n";
        cout << "Nhap: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: createPackage(); break;
            case 2: readPackages(); break;
            case 3: updatePackage(); break;
            case 4: deletePackage(); break;
            case 0: cout << "Quay lai menu chinh...\n"; break;
            default: cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

void RunGoiCuoc() {
    runGoiCuoc();
}
