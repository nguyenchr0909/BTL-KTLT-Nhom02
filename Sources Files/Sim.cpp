#include"Sim.h"
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;

SIM :: SIM(){
	ma="";
	SDT="";
	NhaMang="";
}
void SIM :: nhap(){
	cout << "Nhap ma Sim: " << endl;
	cin >> ma;
	cout << "Nhap SDT: " << endl;
	cin >> SDT;
	cout << "Nhap nha mang: " << endl;
	cin >> NhaMang;
	if(ma.empty()) throw "Ma khong duoc rong";
	if(SDT.empty()) throw "SDT khong duoc rong";
	if(NhaMang.empty()) throw "NhaMang khong duoc rong";
}
void SIM :: hienthi(){
	cout << left << setw(10) << ma << setw(15) << SDT << setw(15) << NhaMang << endl;
}
string SIM :: toFile(){
	return ma + "|" + SDT + "|" + NhaMang;
}
void SIM :: fromFile(string DuLieu){
	if(DuLieu.empty()) throw "Du lieu sim rong";
	stringstream ss(DuLieu);
	if(!getline(ss,ma,'|') || !getline(ss,SDT,'|') || !getline(ss,NhaMang)) throw "Du lieu sim sai dinh dang";
	if(ma.empty() || SDT.empty() || NhaMang.empty()) throw "Du lieu sim bi thieu";
}
string SIM :: getSDT(){
	return SDT;
}
string SIM :: getNhaMang(){
	return NhaMang;
}
void SIM :: setSDT(string SDT){
	if(SDT.empty()) throw("SDT khong duoc rong");
		this->SDT = SDT;
}
void SIM :: setNhaMang(string NhaMang){
	if(NhaMang.empty()) throw("NhaMang khong duoc rong");
		this->NhaMang = NhaMang;
}

