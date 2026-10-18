#include"Khachhang.h"

#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<limits>
using namespace std;

void runKhachHang() {
    Repository<KhachHang> ds;           
    docFile("data/khachhang.txt", ds);
    menuKhachHang(ds);
}
KhachHang::KhachHang() : Entity(""){
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
void KhachHang :: hienThi(){
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
void menuKhachHang(Repository<KhachHang>& ds){
	int chon;
	do{
		cout << "\n===== KHACH HANG =====\n";
		cout << "1.Them khach hang" << endl;
		cout << "2.Hien thi danh sach khach hang" << endl;
		cout << "3.Tim khach hang" << endl;
		cout << "4.Sua khach hang" << endl;
		cout << "5.Xoa khach hang" << endl;
		cout << "0.Quay lai" << endl;
		cout << "Chon: ";
		if(!(cin >> chon)) {
			cout << "Khong co lua chon nay" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			chon=-1;
			continue;
		} try {
			if(chon==1){
				KhachHang x;
				x.nhap();
				if(ds.timMa(x.getMa())!=-1) throw "Ma da ton tai";
				ds.them(x);
				ghiFile("data/khachhang.txt",ds);
				cout << "Them thanh cong" << endl;
			} else if(chon == 2){
				ds.hienthi();
			} else if(chon==3){
				string ma;
				cout << "Nhap ma can tim: ";
				cin >> ma;
				int vitri=ds.timMa(ma);
				if(vitri==-1) throw "Khong tim thay";
				ds.lay(vitri).hienThi();
			} else if(chon==4){
				string ma, ten, tuoi;
				cout << "Nhap ma can sua: ";
				cin >> ma;
				int vitri=ds.timMa(ma);
				if(vitri==-1) throw "Khong tim thay";
				ds.lay(vitri).hienThi();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout << "Ten moi: ";
				getline(cin,ten);
				cout << "Tuoi moi: ";
				getline(cin,tuoi);
				int tuoimoi=0;
				if(!tuoi.empty()){
					tuoimoi=stoi(tuoi);
					if(tuoimoi<0) throw"Tuoi khong hop le";
				}
				if(!ten.empty()) ds.lay(vitri).setTen(ten);
				if(!tuoi.empty()) ds.lay(vitri).setTuoi(tuoimoi);
				ghiFile("data/khachhang.txt",ds);
				cout << "Sua thanh cong" << endl;
			} else if(chon==5){
				string ma;
				char xacnhan;
				cout << "Nhap ma can xoa: ";
				cin >> ma;
				int vitri=ds.timMa(ma);
				if(vitri==-1) throw "Khong tim thay";
				ds.lay(vitri).hienThi();
				cout << "Xoa?(Y/N)";
				cin >> xacnhan;
				if(xacnhan=='Y' || xacnhan=='y') {
					ds.xoa(vitri);
					ghiFile("data/khachhang.txt",ds);
					cout << "Xoa thanh cong" << endl;
				}
			} else if(chon!=0) cout << "Lua chon khong hop le";
		}catch(const char* e) {
            cout << "Loi: " << e << endl;
        }catch(exception& e) {
            cout << "Loi: " << e.what() << endl;
        }
    } while(chon != 0);
}
