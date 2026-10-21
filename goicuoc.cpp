#include "goicuoc.h"

const string DATA_FILE = "data/goicuoc.txt";

Package::Package() : giaCuoc(0), dataGb(0), phutNoiMang(0), phutNgoaiMang(0) {}

Package::Package(string ma, string ten, double gia, double data, int noi, int ngoai) {
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

void Package::display() const {
    cout << left << setw(10) << maGoi 
         << setw(15) << tenGoi https://www.onlinegdb.com/online_c++_compiler#_editor_8963153631
         << setw(12) << giaCuoc 
         << setw(12) << dataGb 
         << setw(12) << phutNoiMang 
         << setw(12) << phutNgoaiMang << "\n";
}

string Package::toString() const {
    return maGoi + "|" + tenGoi + "|" + to_string(giaCuoc) + "|" + 
           to_string(dataGb) + "|" + to_string(phutNoiMang) + "|" + to_string(phutNgoaiMang);
}

vector<string> split(const string &s, char delimiter) {
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
    ifstream file(DATA_FILE);
    if (!file.is_open()) return packages; 

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        vector<string> parts = split(line, '|');
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
    ofstream file(DATA_FILE);
    for (const auto &p : packages) {
        file << p.toString() << "\n";
    }
    file.close();
}