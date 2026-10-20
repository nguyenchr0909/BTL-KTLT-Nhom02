#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>

using namespace std;

class Entity {
protected:
    string ma; // Ma dinh danh
public:
    string getMa() const { return ma; }
    
    // Ham thuan ao
    virtual void nhapThongTin() = 0; 
    virtual void hienThi() const = 0;
};

class ThietBi : public Entity {
private:
    string imei;
    string hangSanXuat;
    string model;
    int namSanXuat;

    bool kiemTraIMEI(const string& str) {
        if (str.length() != 15) return false;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] < '0' || str[i] > '9') return false;
        }
        return true;
    }

public:
    ThietBi() {
        ma = ""; imei = ""; hangSanXuat = ""; model = ""; namSanXuat = 0;
    }

    string getImei() const { return imei; }
    string getHangSanXuat() const { return hangSanXuat; }

    void nhapThongTin() override {
        cout << "Nhap ma thiet bi (VD: TB01): ";
        getline(cin >> ws, ma);

        while (true) {
            cout << "Nhap so IMEI (15 chu so): ";
            getline(cin, imei);
            if (kiemTraIMEI(imei)) break;
            cout << "Loi: IMEI phai gom dung 15 chu so!\n";
        }

        cout << "Nhap hang san xuat (Apple, Samsung...): ";
        getline(cin, hangSanXuat);

        cout << "Nhap ten model: ";
        getline(cin, model);

        while (true) {
            cout << "Nhap nam san xuat (1900-2100): ";
            string namStr;
            getline(cin, namStr);
            stringstream ss(namStr);
            if (ss >> namSanXuat && namSanXuat >= 1900 && namSanXuat <= 2100) {
                break;
            }
            cout << "Loi: Nam san xuat khong hop le hoac ban da nhap chu!\n";
        }
    }

    void capNhatThongTin() {
        cout << "--- Nhap thong tin moi (Nhan Enter de giu nguyen) ---\n";
        
        cout << "Nhap ten model (Hien tai: " << model << "): ";
        string modelMoi;
        getline(cin, modelMoi);
        if (!modelMoi.empty()) {
            model = modelMoi; 
        }

        while (true) {
            cout << "Nhap nam san xuat (Hien tai: " << namSanXuat << "): ";
            string namStr;
            getline(cin, namStr);
            if (namStr.empty()) break; 

            stringstream ss(namStr);
            int namMoi;
            if (ss >> namMoi && namMoi >= 1900 && namMoi <= 2100) {
                namSanXuat = namMoi;
                break;
            }
            cout << "Loi: Nam san xuat khong hop le!\n";
        }
    }

    void hienThi() const override {
        cout << "| " << setw(8) << left << ma 
             << "| " << setw(18) << left << imei 
             << "| " << setw(15) << left << hangSanXuat 
             << "| " << setw(20) << left << model 
             << "| " << setw(10) << right << namSanXuat << " |\n";
    }

    string taoChuoiLuuFile() const {
        stringstream ss;
        ss << ma << "|" << imei << "|" << hangSanXuat << "|" << model << "|" << namSanXuat;
        return ss.str();
    }

    void docTuChuoi(string dong) {
        stringstream ss(dong);
        string namStr;
        getline(ss, ma, '|');
        getline(ss, imei, '|');
        getline(ss, hangSanXuat, '|');
        getline(ss, model, '|');
        getline(ss, namStr, '|');
        
        stringstream(namStr) >> namSanXuat; 
    }
};

class QuanLyThietBi {
private:
    vector<ThietBi> danhSach;
    string tenFile = "data/devices.txt";
    void inTieuDe() {
        cout << string(82, '-') << "\n";
        cout << "| " << setw(8) << left << "Ma TB" 
             << "| " << setw(18) << left << "So IMEI" 
             << "| " << setw(15) << left << "Hang SX" 
             << "| " << setw(20) << left << "Ten Model" 
             << "| " << setw(10) << right << "Nam SX" << " |\n";
        cout << string(82, '-') << "\n";
    }

public:
    void docFile() {
        danhSach.clear();
        ifstream file(tenFile);
        if (!file.is_open()) return;
        
        string dong;
        while (getline(file, dong)) {
            if (dong.empty()) continue;
            ThietBi tb;
            tb.docTuChuoi(dong);
            danhSach.push_back(tb);
        }
        file.close();
    }

    void ghiFile() {
        ofstream file(tenFile);
        if (!file.is_open()) {
            cout << "Loi: Khong mo duoc file. Hay kiem tra da tao thu muc 'data' chua!\n";
            return;
        }
        for (int i = 0; i < danhSach.size(); i++) {
            file << danhSach[i].taoChuoiLuuFile() << "\n";
        }
        file.close();
    }
    void themThietBi() {
        ThietBi tb;
        tb.nhapThongTin();
        for (int i = 0; i < danhSach.size(); i++) {
            if (danhSach[i].getMa() == tb.getMa()) {
                cout << "Loi: Ma thiet bi da ton tai!\n";
                return;
            }
            if (danhSach[i].getImei() == tb.getImei()) {
                cout << "Loi: So IMEI nay da ton tai trong he thong!\n";
                return;
            }
        }
        
        danhSach.push_back(tb);
        ghiFile();
        cout << "=> Them thiet bi moi thanh cong!\n";
    }

    void xemDanhSach() {
        if (danhSach.empty()) {
            cout << "Danh sach thiet bi trong!\n";
            return;
        }
        inTieuDe();
        for (int i = 0; i < danhSach.size(); i++) {
            danhSach[i].hienThi();
        }
        cout << string(82, '-') << "\n";
    }

    void timKiemIMEI() {
        string imeiTim;
        cout << "Nhap so IMEI can tim: ";
        getline(cin >> ws, imeiTim);
        
        bool thay = false;
        for (int i = 0; i < danhSach.size(); i++) {
            if (danhSach[i].getImei() == imeiTim) {
                if (!thay) inTieuDe(); 
                danhSach[i].hienThi();
                thay = true;
            }
        }
        if (!thay) cout << "Khong tim thay thiet bi nao!\n";
        else cout << string(82, '-') << "\n";
    }

    void locTheoHang() {
        string hangTim;
        cout << "Nhap Hang san xuat can loc: ";
        getline(cin >> ws, hangTim);
        
        bool thay = false;
        for (int i = 0; i < danhSach.size(); i++) {
            if (danhSach[i].getHangSanXuat() == hangTim) {
                if (!thay) inTieuDe();
                danhSach[i].hienThi();
                thay = true;
            }
        }
        if (!thay) cout << "Khong co thiet bi nao cua hang nay!\n";
        else cout << string(82, '-') << "\n";
    }

    void capNhatThietBi() {
        string maTim;
        cout << "Nhap ma thiet bi can cap nhat: ";
        getline(cin >> ws, maTim);
        
        for (int i = 0; i < danhSach.size(); i++) {
            if (danhSach[i].getMa() == maTim) {
                cout << "\nThong tin hien tai:\n";
                inTieuDe();
                danhSach[i].hienThi();
                cout << "\n";
                
                danhSach[i].capNhatThongTin();
                ghiFile();
                cout << "=> Cap nhat thanh cong!\n";
                return;
            }
        }
        cout << "Khong tim thay ma thiet bi!\n";
    }

    void xoaThietBi() {
        string maTim;
        cout << "Nhap ma thiet bi can xoa: ";
        getline(cin >> ws, maTim);
        
        for (int i = 0; i < danhSach.size(); i++) {
            if (danhSach[i].getMa() == maTim) {
                cout << "\nThong tin thiet bi sap xoa:\n";
                inTieuDe();
                danhSach[i].hienThi();
                cout << "\n";
                cout << "Ban co chac chan muon xoa thiet bi nay? (y/n): ";
                string xacNhan;
                getline(cin, xacNhan);
                
                if (xacNhan == "y" || xacNhan == "Y") {
                    danhSach.erase(danhSach.begin() + i);
                    ghiFile();
                    cout << "=> Xoa thanh cong!\n";
                } else {
                    cout << "=> Da huy thao tac xoa.\n";
                }
                return;
            }
        }
        cout << "Khong tim thay thiet bi!\n";
    }

    void menu() {
        docFile(); 
        
        int chon = -1;
        while (chon != 0) {
            cout << "\n============= QUAN LY THIET BI =============\n";
            cout << "1. Them thiet bi moi\n";
            cout << "2. Xem danh sach thiet bi\n";
            cout << "3. Tim kiem theo so IMEI\n";
            cout << "4. Loc theo Hang san xuat\n";
            cout << "5. Cap nhat thiet bi\n";
            cout << "6. Xoa thiet bi\n";
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
                case 3: timKiemIMEI(); break;
                case 4: locTheoHang(); break;
                case 5: capNhatThietBi(); break;
                case 6: xoaThietBi(); break;
                case 0: cout << "Dang thoat...\n"; break;
                default: cout << "Lua chon khong dung, moi chon lai!\n";
            }
        }
    }
};

int main() {
    QuanLyThietBi ql;
    ql.menu();
    return 0;
}
