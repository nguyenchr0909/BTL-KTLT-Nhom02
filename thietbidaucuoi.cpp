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

    static int getInt(const string& prompt) {
        while (true) {
            cout << prompt;
            string input;
            getline(cin >> ws, input);
            if (input.empty()) return -1; // Ho tro bo trong khi cap nhat
            stringstream ss(input);
            int val;
            if (ss >> val && ss.eof()) {
                return val;
            }
            cout << "[Loi] Vui long nhap so nguyen hop le!\n";
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
// 3. LOP THUC THE: Device (Thiet bi)
// ==========================================
class Device : public Entity {
private:
    string imei;
    string hangSanXuat;
    string model;
    int namSanXuat;

    // Ham kiem tra IMEI (dung 15 chu so)
    bool isValidIMEI(const string& imeiStr) const {
        if (imeiStr.length() != 15) return false;
        for (char c : imeiStr) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

public:
    Device() : Entity(""), imei(""), hangSanXuat(""), model(""), namSanXuat(0) {}
    Device(string id, string imei, string hang, string mod, int nam) 
        : Entity(id), imei(imei), hangSanXuat(hang), model(mod), namSanXuat(nam) {}

    // Getters
    string getImei() const { return imei; }
    string getHangSanXuat() const { return hangSanXuat; }
    string getModel() const { return model; }
    int getNamSanXuat() const { return namSanXuat; }

    // Setters
    void setImei(const string& val) {
        if (!isValidIMEI(val)) throw invalid_argument("IMEI phai chua dung 15 chu so!");
        imei = val;
    }
    void setHangSanXuat(const string& val) {
        if (val.empty()) throw invalid_argument("Hang san xuat khong duoc rong!");
        hangSanXuat = val;
    }
    void setModel(const string& val) {
        if (val.empty()) throw invalid_argument("Ten model khong duoc rong!");
        model = val;
    }
    void setNamSanXuat(int val) {
        if (val < 1900 || val > 2100) throw invalid_argument("Nam san xuat khong hop le (1900-2100)!");
        namSanXuat = val;
    }

    void input(bool isNew = true) {
        if (isNew) {
            setId(InputHelper::getString("Nhap Ma thiet bi (VD: TB01): "));
            
            while (true) {
                try {
                    setImei(InputHelper::getString("Nhap so IMEI (15 chu so): "));
                    break;
                } catch (const exception& e) {
                    cout << "[Loi] " << e.what() << "\n";
                }
            }
            
            while (true) {
                try {
                    setHangSanXuat(InputHelper::getString("Nhap Hang san xuat (Apple, Samsung,...): "));
                    break;
                } catch (const exception& e) {
                    cout << "[Loi] " << e.what() << "\n";
                }
            }
        }

        // Nhap Model (khi cap nhat co the bo trong)
        while (true) {
            try {
                cout << "Nhap Ten model" << (!isNew ? " (bo trong de giu nguyen '" + model + "')" : "") << ": ";
                string modStr;
                getline(cin >> ws, modStr);
                if (!isNew && modStr.empty()) break; // Bo trong -> giu nguyen
                setModel(modStr);
                break;
            } catch (const exception& e) {
                cout << "[Loi] " << e.what() << "\n";
            }
        }

        // Nhap Nam san xuat (khi cap nhat co the bo trong)
        while (true) {
            try {
                cout << "Nhap Nam san xuat" << (!isNew ? " (nhan Enter de giu nguyen '" + to_string(namSanXuat) + "')" : "") << ": ";
                string namStr;
                getline(cin, namStr);
                if (!isNew && namStr.empty()) break; // Bo trong -> giu nguyen
                
                stringstream ss(namStr);
                int nam;
                if (ss >> nam && ss.eof()) {
                    setNamSanXuat(nam);
                    break;
                } else {
                     cout << "[Loi] Vui long nhap so nguyen!\n";
                }
            } catch (const exception& e) {
                cout << "[Loi] " << e.what() << "\n";
            }
        }
    }

    void display() const {
        cout << "| " << setw(8) << left << id 
             << "| " << setw(18) << left << imei 
             << "| " << setw(15) << left << hangSanXuat 
             << "| " << setw(20) << left << model 
             << "| " << setw(10) << right << namSanXuat << " |\n";
    }

    string toFileString() const {
        stringstream ss;
        ss << id << "|" << imei << "|" << hangSanXuat << "|" << model << "|" << namSanXuat;
        return ss.str();
    }

    void fromFileString(const string& line) {
        stringstream ss(line);
        string idStr, imeiStr, hangStr, modStr, namStr;

        if (getline(ss, idStr, '|') &&
            getline(ss, imeiStr, '|') &&
            getline(ss, hangStr, '|') &&
            getline(ss, modStr, '|') &&
            getline(ss, namStr, '|')) {
            
            stringstream ssNam(namStr);
            int nam;
            ssNam >> nam;

            setId(idStr);
            setImei(imeiStr);
            setHangSanXuat(hangStr);
            setModel(modStr);
            setNamSanXuat(nam);
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
    
    ~Repository() {
        clearMemory();
    }

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
                cout << "[Canh bao] Bo qua dong loi: " << line << "\n";
            }
        }
        file.close();
    }

    void saveToFile() const {
        ofstream file(filePath.c_str());
        if (!file.is_open()) {
            throw runtime_error("Khong the mo file de ghi!");
        }
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

    bool update(const string& id) {
        T* item = findById(id);
        if (!item) {
            cout << "[Loi] Khong tim thay ma: " << id << "\n";
            return false;
        }
        cout << "\n--- Thong tin hien tai ---\n";
        item->display();
        cout << "--- Nhap thong tin moi (bo trong de giu nguyen) ---\n";
        item->input(false); 
        saveToFile();
        return true;
    }

    bool remove(const string& id) {
        for (typename vector<T*>::iterator it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getId() == id) {
                cout << "\nThong tin thiet bi:\n";
                (*it)->display();
                
                string confirm = InputHelper::getString("Ban co chac muon xoa thiet bi nay? (y/n): ");
                if (confirm == "y" || confirm == "Y") {
                    delete *it;
                    items.erase(it);
                    saveToFile();
                    cout << "=> Xoa thanh cong!\n";
                    return true;
                } else {
                    cout << "=> Huy thao tac xoa.\n";
                    return false;
                }
            }
        }
        cout << "[Loi] Khong tim thay thiet bi co ma: " << id << "\n";
        return false;
    }

    const vector<T*>& getAll() const {
        return items;
    }
};

// ==========================================
// 5. GIAO DIEN MENU CHO THIET BI
// ==========================================
class DeviceMenu {
private:
    Repository<Device>& repo;

    void printHeader() const {
        cout << string(85, '-') << "\n";
        cout << "| " << setw(8) << left << "Ma TB" 
             << "| " << setw(18) << left << "So IMEI" 
             << "| " << setw(15) << left << "Hang SX" 
             << "| " << setw(20) << left << "Ten Model" 
             << "| " << setw(10) << right << "Nam SX" << " |\n";
        cout << string(85, '-') << "\n";
    }

public:
    DeviceMenu(Repository<Device>& r) : repo(r) {}

    void run() {
        int choice = -1;
        while (choice != 0) {
            cout << "\n============ QUAN LY THIET BI DAU CUOI ============\n";
            cout << "  1. Them thiet bi moi\n";
            cout << "  2. Xem danh sach thiet bi\n";
            cout << "  3. Tim kiem theo IMEI\n";
            cout << "  4. Loc theo hang san xuat\n";
            cout << "  5. Cap nhat thiet bi\n";
            cout << "  6. Xoa thiet bi\n";
            cout << "  0. Quay lai menu chinh\n";
            cout << "=====================================================\n";
            
            cout << "Nhap lua chon: ";
            string choiceStr;
            getline(cin >> ws, choiceStr);
            stringstream ss(choiceStr);
            if (!(ss >> choice)) {
                 choice = -1; 
            }

            switch (choice) {
                case 1: { 
                    Device* dev = new Device();
                    
                    dev->input(true);
                    
                    bool imeiExists = false;
                    const vector<Device*>& list = repo.getAll();
                    for(size_t i=0; i<list.size(); ++i) {
                         if(list[i]->getImei() == dev->getImei()) {
                              imeiExists = true;
                              break;
                         }
                    }
                    
                    if(imeiExists) {
                         cout << "[Loi] So IMEI nay da ton tai trong he thong!\n";
                         delete dev;
                    } else {
                         if (repo.add(dev)) {
                              cout << "=> Them thiet bi thanh cong!\n";
                         }
                    }
                    break;
                }
                case 2: { 
                    const vector<Device*>& list = repo.getAll();
                    if (list.empty()) {
                        cout << "Danh sach thiet bi trong!\n";
                    } else {
                        printHeader();
                        for (size_t i = 0; i < list.size(); ++i) {
                            list[i]->display();
                        }
                        cout << string(85, '-') << "\n";
                        cout << "Tong so thiet bi: " << list.size() << "\n";
                    }
                    break;
                }
                case 3: { 
                    string imei = InputHelper::getString("Nhap so IMEI can tim: ");
                    bool found = false;
                    const vector<Device*>& list = repo.getAll();
                    printHeader();
                    for (size_t i = 0; i < list.size(); ++i) {
                        if (list[i]->getImei() == imei) {
                            list[i]->display();
                            found = true;
                        }
                    }
                    cout << string(85, '-') << "\n";
                    if (!found) cout << "Khong tim thay thiet bi co IMEI: " << imei << "\n";
                    break;
                }
                case 4: { 
                    string hang = InputHelper::getString("Nhap Hang san xuat can loc: ");
                    bool found = false;
                    const vector<Device*>& list = repo.getAll();
                    printHeader();
                    for (size_t i = 0; i < list.size(); ++i) {
                        if (list[i]->getHangSanXuat() == hang) {
                            list[i]->display();
                            found = true;
                        }
                    }
                    cout << string(85, '-') << "\n";
                    if (!found) cout << "Khong tim thay thiet bi cua hang: " << hang << "\n";
                    break;
                }
                case 5: { 
                    string id = InputHelper::getString("Nhap Ma thiet bi can cap nhat: ");
                    repo.update(id);
                    break;
                }
                case 6: { 
                    string id = InputHelper::getString("Nhap Ma thiet bi can xoa: ");
                    repo.remove(id);
                    break;
                }
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le, vui long nhap lai!\n";
            }
        }
    }
};

// ==========================================
// 6. MAIN (Tich hop)
// ==========================================
int main() {
    Repository<Device> repoDevice("data/devices.txt");
    repoDevice.loadFromFile();

    DeviceMenu menu(repoDevice);
    menu.run();

    return 0;
}