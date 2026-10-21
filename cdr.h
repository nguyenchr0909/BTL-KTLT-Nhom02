#ifndef CDR_H
#define CDR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <exception>

using namespace std;

class BaseEntity {
public:
    virtual void input() = 0;              
    virtual void display() const = 0;      
    virtual string toString() const = 0;   
    virtual ~BaseEntity() {}
};
class CDR : public BaseEntity {
private:
    string maCDR;
    string soGoi;     
    string soNhan;     
    string thoiDiem;  
    int thoiLuong;    
public:
    CDR();
    CDR(string ma, string goi, string nhan, string thoiDiemGoi, int luong);

    void setMaCDR(string ma);
    void setSoGoi(string goi);
    void setSoNhan(string nhan);
    void setThoiDiem(string td);
    void setThoiLuong(int luong);

    string getMaCDR() const;
    string getSoGoi() const;
    string getSoNhan() const;
    string getThoiDiem() const;
    int getThoiLuong() const;

    void input() override;
    void display() const override;
    string toString() const override;
};
vector<string> split(const string &s, char delimiter);
vector<CDR> loadCDRs();
void saveCDRs(const vector<CDR> &cdrs);

#endif