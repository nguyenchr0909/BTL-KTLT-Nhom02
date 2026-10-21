#ifndef goicuoc_H_H
#define goicuoc_H

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

class Package : public BaseEntity {
private:
    string maGoi;
    string tenGoi;
    double giaCuoc;
    double dataGb;
    int phutNoiMang;
    int phutNgoaiMang;

public:
    Package();
    Package(string ma, string ten, double gia, double data, int noi, int ngoai);

    void setMaGoi(string ma);
    void setTenGoi(string ten);
    void setGiaCuoc(double gia);
    void setDataGb(double data);
    void setPhutNoiMang(int noi);
    void setPhutNgoaiMang(int ngoai);

    string getMaGoi() const;
    string getTenGoi() const;
    double getGiaCuoc() const;
    double getDataGb() const;
    int getPhutNoiMang() const;
    int getPhutNgoaiMang() const;

    void input() override;
    void display() const override;
    string toString() const override;
};


vector<string> split(const string &s, char delimiter);
vector<Package> loadPackages();
void savePackages(const vector<Package> &packages);

#endif