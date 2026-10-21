#include "cdr.h"
const string DATA_FILE = "data/cdrs.txt";
CDR::CDR() : thoiLuong(0) {}
CDR::CDR(string ma, string goi, string nhan, string thoiDiemGoi, int luong) {
    setMaCDR(ma);
    setSoGoi(goi);
    setSoNhan(nhan);
    setThoiDiem(thoiDiemGoi);
    setThoiLuong(luong);
}

void CDR::setMaCDR(string ma) {
    if (ma.empty()) throw invalid_argument("Ma CDR khong đuocc đe trong!");
    maCDR = ma;
}

void CDR::setSoGoi(string goi) {
    if (goi.empty()) throw invalid_argument("So goi (Caller) khong đuoc đe trong!");
    soGoi = goi;
}

void CDR::setSoNhan(string nhan) {
    if (nhan.empty()) throw invalid_argument("So nhan (Callee) khong đưoc đe trong!");
    soNhan = nhan;
}

void CDR::setThoiDiem(string td) {
    if (td.empty()) throw invalid_argument("Thoi điem bat đau khong đưoc đe trong!");
    thoiDiem = td;
}

void CDR::setThoiLuong(int luong) {
    if (luong <= 0) throw invalid_argument("Thoi lưong goi phai lon hon 0 giay!");
    thoiLuong = luong;
}

string CDR::getMaCDR() const { return maCDR; }
string CDR::getSoGoi() const { return soGoi; }
string CDR::getSoNhan() const { return soNhan; }
string CDR::getThoiDiem() const { return thoiDiem; }
int CDR::getThoiLuong() const { return thoiLuong; }

void CDR::input() {
    cout << "Nhap ma CDR (VD: CDR001): ";
    string ma; cin >> ma;
    setMaCDR(ma);

    cout << "Nhap so goi (Caller): ";
    cin >> soGoi;
    setSoGoi(soGoi);

    cout << "Nhap so nhan (Callee): ";
    cin >> soNhan;
    if (soGoi == soNhan) {
        throw invalid_argument("So goi và so nhan phai khac nhau!");
    }
    setSoNhan(soNhan);

    cout << "Nhap thoi điem batt đau (VD: 11/03/2026_01:25:20): ";
    cin.ignore();
    getline(cin, thoiDiem);
    setThoiDiem(thoiDiem);

    int luong;
    cout << "Nhap thoi lưong goi (so giay > 0): ";
    if (!(cin >> luong)) throw ios_base::failure("Loi!");
    setThoiLuong(luong);
}

void CDR::display() const {
    cout << left << setw(10) << maCDR 
         << setw(15) << soGoi 
         << setw(15) << soNhan 
         << setw(22) << thoiDiem 
         << setw(12) << thoiLuong << "\n";
}

string CDR::toString() const {
    return maCDR + "|" + soGoi + "|" + soNhan + "|" + thoiDiem + "|" + to_string(thoiLuong);
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

vector<CDR> loadCDRs() {
    vector<CDR> cdrs;
    ifstream file(DATA_FILE);
    if (!file.is_open()) return cdrs; 

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        vector<string> parts = split(line, '|');
        if (parts.size() == 5) {
            try {
                CDR c(parts[0], parts[1], parts[2], parts[3], stoi(parts[4]));
                cdrs.push_back(c);
            } catch (...) {}
        }
    }
    file.close();
    return cdrs;
}

void saveCDRs(const vector<CDR> &cdrs) {
    ofstream file(DATA_FILE);
    for (const auto &c : cdrs) {
        file << c.toString() << "\n";
    }
    file.close();
}