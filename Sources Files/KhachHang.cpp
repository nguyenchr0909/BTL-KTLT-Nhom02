#include"Khachhang.h"

#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<limits>
using namespace std;

KhachHang::KhachHang(){
    ma = "";
    ten = "";
    tuoi = 0;
}
void KhachHang :: nhap(){
	cout << "Nhap ma khach hang: " << endl;
	cin >> ma;
	cin.ignore();
	cout << "Nhap ten: ";
	getline(cin, ten);
	cout << "Nhap tuoi: ";
	if(!(cin >> tuoi)){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		throw("Tuoi khach hang khong hop le");
	}
	if(ma.empty()) throw("Ma khach hang khong hop le");
	if(ten.empty()) throw("Ten khach hang khong hop le");
	if(tuoi<0) throw("Tuoi khach hang khong hop le");
}
void KhachHang :: hienthi(){
	cout << left << setw(10) << ma << setw(25) << ten << setw(10) << tuoi << endl;
}
string KhachHang :: toFile(){
	return ma + "|" + ten + "|" + to_string(tuoi);
}
void KhachHang :: fromFile(string DuLieu){
	string tuoi2;
	stringstream ss(DuLieu);
	if(!getline(ss,ma,'|') || !getline(ss,ten,'|') || !getline(ss,tuoi2)) throw("Sai dinh dang");
	if(ma.empty() || ten.empty() || tuoi2.empty()) throw("Thieu du lieu khach hang");
	stringstream t(tuoi2);
	if(!(t >> tuoi)) throw("Sai dinh dang tuoi");
	if(tuoi < 0) throw("Tuoi khong hop le");
}
string KhachHang :: getTen(){
	return ten;
}
int KhachHang :: getTuoi(){
	return tuoi;
}
void KhachHang :: setTen(string ten){
	if(ten.empty()) throw("Ten khong hop le");
	this->ten = ten;
}
void KhachHang :: setTuoi(int tuoi){
	if(tuoi<0) throw("Tuoi khong hop le");
	this->tuoi=tuoi;
}

