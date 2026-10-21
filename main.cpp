#include "Package.h"

const string CONTRACT_FILE = "data/contracts.txt";

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

    for (const auto &p : packages) {
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
        for (const auto &p : packages) {
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
        for (const auto &p : packages) {
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

    bool hasContract = false;
    ifstream contractFile(CONTRACT_FILE);
    if (contractFile.is_open()) {
        string line;
        while (getline(contractFile, line)) {
            if (line.find(maGoi) != string::npos) {
                hasContract = true;
                break;
            }
        }
        contractFile.close();
    }

    if (hasContract) {
        cout << "Loi: Goi cuoc dang co Hop dong dang ky su dung nen KHONG CHO PHEP XOA!\n";
        return;
    }

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

int main() {
    int choice;
    do {
        cout << "\n===== QUAN LY GOI CUOC (OOP) =====\n";
        cout << "1. Them moi goi cuoc (Create)\n";
        cout << "2. Xem va tim kiem goi cuoc (Read)\n";
        cout << "3. Cap nhat goi cuoc (Update)\n";
        cout << "4. Xoa goi cuoc (Delete)\n";
        cout << "0. Thoat\n";
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
            case 0: cout << "Tam biet!\n"; break;
            default: cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);

    return 0;
}