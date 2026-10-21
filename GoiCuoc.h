#ifndef GOICUOC_H
#define GOICUOC_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <exception>
#include <stdexcept>
#include "Entity.h"

using namespace std;

// Lop Package ke thua tu Entity
class Package : public Entity {
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

    void input();
    void display() override;
    string toString() const;
};


vector<Package> loadPackages();
void savePackages(const vector<Package> &packages);


void createPackage();
void readPackages();
void updatePackage();
void deletePackage();

// Ham chay menu chinh
void runGoiCuoc();
void RunGoiCuoc(); // Alias cho ten viet hoa

#endif // GOICUOC_H
