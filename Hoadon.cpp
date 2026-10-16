#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

using namespace std;

// ==========================================
// 1. TIEN ICH NHAP LIEU
// ==========================================
class InputHelper {
public:
    static string getString(const string& prompt) {
        cout << prompt;
        string val;
        getline(cin >> ws, val);
        return val;
    }

    static double getDouble(const string& prompt) {
        while (true) {
            cout << prompt;
            string input;
            getline(cin >> ws, input);
            if (input.empty()) return -1;
            stringstream ss(input);
            double val;
            if (ss >> val && ss.eof()) {
                return val;
            }
            cout << "[Loi] Vui long nhap so hop le!\n";
        }
    }
};

// ==========================================
// 2. LOP CO SO TRUU TUONG (Entity)
// ==========================================
class Entity {
protected:
    string id;

public:
    Entity(const string& id = "") : id(id) {}
    virtual ~Entity() {}

    string getId() const { return id; }
    void setId(const string& newId) {
        if (newId.empty()) throw invalid_argument("Ma khong duoc de trong!");
        id = newId;
    }

    virtual void input(bool isNew = true) = 0;
    virtual void display() const = 0;
    virtual string toFileString() const = 0;
    virtual void fromFileString(const string& line) = 0;
};

// ==========================================
// 3. LOP THUC THE: HoaDon
// ==========================================
class HoaDon : public Entity {
private:
    string soThueBao;
    string kyCuoc;
    double tongTien;
    string trangThai;

public:
    HoaDon() : Entity(""), soThueBao(""), kyCuoc(""), tongTien(0), trangThai("Chua thanh toan") {}

    // Getters
    string getSoThueBao() const { return soThueBao; }
    string getKyCuoc() const { return kyCuoc; }
    double getTongTien() const { return tongTien; }
    string getTrangThai() const { return trangThai; }

    // Setters
    void setSoThueBao(const string& val) {
        if (val.empty()) throw invalid_argument("So thue bao khong duoc rong!");
        soThueBao = val;
    }
    void setKyCuoc(const string& val) {
        if (val.empty()) throw invalid_argument("Ky cuoc khong duoc rong!");
        kyCuoc = val;
    }
    void setTongTien(double val) {
        if (val < 0) throw invalid_argument("Tong tien phai >= 0!");
        tongTien = val;
    }
    void setTrangThai(const string& val) {
        trangThai = val;
    }

    void input(bool isNew = true) {
        if (isNew) {
            setId(InputHelper::getString("Nhap Ma hoa don (VD: HDN01): "));
            setSoThueBao(InputHelper::getString("Nhap So thue bao: "));
            setKyCuoc(InputHelper::getString("Nhap Ky cuoc (VD: 03/2026): "));
            
            while (true) {
                try {
                    setTongTien(InputHelper::getDouble("Nhap Tong tien cuoc phat sinh (VND): "));
                    break;
                } catch (const exception& e) {
                    cout << "[Loi] " << e.what() << "\n";
                }
            }

            while (true) {
                string statusChoice = InputHelper::getString("Nhap Trang thai (1: Chua thanh toan, 2: Da thanh toan): ");
                if (statusChoice == "1") {
                    setTrangThai("Chua thanh toan");
                    break;
                } else if (statusChoice == "2") {
                    setTrangThai("Da thanh toan");
                    break;
                } else {
                    cout << "[Loi] Lua chon khong hop le!\n";
                }
            }
        }
    }

    void display() const {
        cout << "| " << setw(8) << left << id 
             << "| " << setw(15) << left << soThueBao 
             << "| " << setw(10) << left << kyCuoc 
             << "| " << setw(15) << right << fixed << setprecision(0) << tongTien 
             << "| " << setw(18) << left << trangThai << " |\n";
    }

    string toFileString() const {
        stringstream ss;
        // HDN01|0981234567|03/2026|150000|Chua thanh toan
        ss << id << "|" << soThueBao << "|" << kyCuoc << "|" << fixed << setprecision(0) << tongTien << "|" << trangThai;
        return ss.str();
    }

    void fromFileString(const string& line) {
        stringstream ss(line);
        string idStr, thueBaoStr, kyStr, tienStr, trangThaiStr;

        if (getline(ss, idStr, '|') &&
            getline(ss, thueBaoStr, '|') &&
            getline(ss, kyStr, '|') &&
            getline(ss, tienStr, '|') &&
            getline(ss, trangThaiStr, '|')) {
            
            stringstream ssTien(tienStr);
            double tien;
            ssTien >> tien;

            setId(idStr);
            setSoThueBao(thueBaoStr);
            setKyCuoc(kyStr);
            setTongTien(tien);
            setTrangThai(trangThaiStr);
        } else {
            throw runtime_error("Dong du lieu sai dinh dang!");
        }
    }
};

// ==========================================
// 4. LOP KHUON MAU: Repository<T>
// ==========================================
template <typename T>
class Repository {
private:
    vector<T*> items;
    string filePath;

    void clearMemory() {
        for (size_t i = 0; i < items.size(); ++i) {
            delete items[i];
        }
        items.clear();
    }

public:
    Repository(const string& path) : filePath(path) {}
    
    ~Repository() { clearMemory(); }

    void loadFromFile() {
        clearMemory();
        ifstream file(filePath.c_str());
        if (!file.is_open()) {
            ofstream newFile(filePath.c_str());
            newFile.close();
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
            try {
                T* obj = new T();
                obj->fromFileString(line);
                items.push_back(obj);
            } catch (...) {
                // Bo qua dong loi
            }
        }
        file.close();
    }

    void saveToFile() const {
        ofstream file(filePath.c_str());
        if (!file.is_open()) throw runtime_error("Khong the mo file de ghi!");
        for (size_t i = 0; i < items.size(); ++i) {
            file << items[i]->toFileString() << "\n";
        }
        file.close();
    }

    T* findById(const string& id) {
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i]->getId() == id) return items[i];
        }
        return NULL;
    }

    bool add(T* item) {
        if (findById(item->getId()) != NULL) {
            cout << "[Loi] Ma dinh danh da ton tai!\n";
            delete item;
            return false;
        }
        items.push_back(item);
        saveToFile();
        return true;
    }

    bool remove(const string& id) {
        for (typename vector<T*>::iterator it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getId() == id) {
                delete *it;
                items.erase(it);
                saveToFile();
                return true;
            }
        }
        return false;
    }

    const vector<T*>& getAll() const { return items; }
};

// ==========================================
// 5. GIAO DIEN MENU HOA DON
// ==========================================
class HoaDonMenu {
private:
    Repository<HoaDon>& repo;

    void printHeader() const {
        cout << string(78, '-') << "\n";
        cout << "| " << setw(8) << left << "Ma HD" 
             << "| " << setw(15) << left << "So thue bao" 
             << "| " << setw(10) << left << "Ky cuoc" 
             << "| " << setw(15) << right << "Tong tien" 
             << "| " << setw(18) << left << " Trang thai" << " |\n";
        cout << string(78, '-') << "\n";
    }

public:
    HoaDonMenu(Repository<HoaDon>& r) : repo(r) {}

    void run() {
        int choice = -1;
        while (choice != 0) {
            cout << "\n============= QUAN LY HOA DON CUOC =============\n";
            cout << "  1. Them hoa don moi\n";
            cout << "  2. Xem danh sach hoa don\n";
            cout << "  3. Tim kiem theo so thue bao\n";
            cout << "  4. Loc thue bao dang no cuoc (Chua thanh toan)\n";
            cout << "  5. Cap nhat trang thai (Khach da nop tien)\n";
            cout << "  6. Xoa hoa don (Luu y rang buoc)\n";
            cout << "  0. Quay lai menu chinh\n";
            cout << "================================================\n";
            
            cout << "Nhap lua chon: ";
            string choiceStr;
            getline(cin >> ws, choiceStr);
            stringstream ss(choiceStr);
            if (!(ss >> choice)) choice = -1; 

            switch (choice) {
                case 1: { // C - Create
                    HoaDon* hd = new HoaDon();
                    hd->input(true);
                    
                    // TODO (Ghi chu khi gop nhom): 
                    // Neu ban co repoThueBao, hay kiem tra su ton tai cua so thue bao o day!
                    // Vi du: if (repoThueBao.findBySo(hd->getSoThueBao()) == NULL) { cout << "Loi..."; }
                    
                    if (repo.add(hd)) {
                        cout << "=> Them hoa don moi thanh cong!\n";
                    }
                    break;
                }
                case 2: { // R - Read all
                    const vector<HoaDon*>& list = repo.getAll();
                    if (list.empty()) cout << "Danh sach hoa don trong!\n";
                    else {
                        printHeader();
                        for (size_t i = 0; i < list.size(); ++i) list[i]->display();
                        cout << string(78, '-') << "\n";
                    }
                    break;
                }
                case 3: { // R - Search by Phone Number
                    string sdt = InputHelper::getString("Nhap so thue bao can tim: ");
                    bool found = false;
                    const vector<HoaDon*>& list = repo.getAll();
                    printHeader();
                    for (size_t i = 0; i < list.size(); ++i) {
                        if (list[i]->getSoThueBao() == sdt) {
                            list[i]->display();
                            found = true;
                        }
                    }
                    cout << string(78, '-') << "\n";
                    if (!found) cout << "Khong co hoa don nao cua so thue bao: " << sdt << "\n";
                    break;
                }
                case 4: { // R - Filter unpaid
                    bool found = false;
                    const vector<HoaDon*>& list = repo.getAll();
                    cout << "\n--- DANH SACH THUE BAO DANG NO CUOC ---\n";
                    printHeader();
                    for (size_t i = 0; i < list.size(); ++i) {
                        if (list[i]->getTrangThai() == "Chua thanh toan") {
                            list[i]->display();
                            found = true;
                        }
                    }
                    cout << string(78, '-') << "\n";
                    if (!found) cout << "Khong co khach hang nao dang no cuoc!\n";
                    break;
                }
                case 5: { // U - Update status specifically
                    string id = InputHelper::getString("Nhap Ma hoa don khach hang vua nop tien: ");
                    HoaDon* hd = repo.findById(id);
                    if (hd) {
                        if (hd->getTrangThai() == "Da thanh toan") {
                            cout << "=> Hoa don nay DA DUOC THANH TOAN tu truoc!\n";
                        } else {
                            hd->setTrangThai("Da thanh toan");
                            repo.saveToFile();
                            cout << "=> Cap nhat trang thai thanh Da thanh toan THANH CONG!\n";
                        }
                    } else {
                        cout << "[Loi] Khong tim thay hoa don ma: " << id << "\n";
                    }
                    break;
                }
                case 6: { // D - Delete with strict constraints
                    string id = InputHelper::getString("Nhap Ma hoa don can xoa: ");
                    HoaDon* hd = repo.findById(id);
                    
                    if (!hd) {
                        cout << "[Loi] Khong tim thay hoa don ma: " << id << "\n";
                        break;
                    }

                    // KIEM TRA RANG BUOC XOA
                    if (hd->getTrangThai() == "Chua thanh toan") {
                        cout << "[Tu choi] KHONG DUOC XOA hoa don Chua thanh toan! Vui long thu tien truoc.\n";
                    } else {
                        cout << "\nThong tin hoa don:\n";
                        hd->display();
                        string confirm = InputHelper::getString("Day la hoa don cu da quyet toan. Ban chac chan muon xoa/luu tru? (y/n): ");
                        if (confirm == "y" || confirm == "Y") {
                            repo.remove(id);
                            cout << "=> Xoa thanh cong!\n";
                        } else {
                            cout << "=> Huy xoa.\n";
                        }
                    }
                    break;
                }
                case 0: break;
                default: cout << "Lua chon khong hop le, vui long nhap lai!\n";
            }
        }
    }
};

// ==========================================
// 6. MAIN
// ==========================================
int main() {
    // Tao san thu muc 'data' o noi luu file chay nhe
    Repository<HoaDon> repoHoaDon("data/HoaDon.txt");
    repoHoaDon.loadFromFile();

    HoaDonMenu menu(repoHoaDon);
    menu.run();

    return 0;
}