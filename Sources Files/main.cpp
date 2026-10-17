#include"Sim.h"
#include"Khachhang.h"
#include"Repository.h"

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<limits>
using namespace std;

template <typename T>
void docFile(string tenFile, Repository<T>& ds){
	ifstream file(tenFile);
	if(!file){
		ofstream taoFile(tenFile);
		taoFile.close();
		return;
	}
	string dong;
	while(getline(file,dong)){
		if(dong.empty()) continue;
		try{
			T x;
			x.fromFile(dong);
			if(ds.timMa(x.getMa())==-1) ds.them(x);
			else cout << "Canh bao: Ma bi trung" << endl;
		} catch(const char* e){
			cout << "Canh bao: " << e << endl;
		}
	}
	file.close();
}
template<typename T>
void ghiFile(string tenFile, Repository<T>& ds){
	ofstream file(tenFile);
	if(!file) throw "Khong mo duoc file";
	for(int i=0; i < ds.kichthuoc();i++) file << ds.lay(i).toFile() << endl;
	file.close();
}
void menuKhachHang(Repository<KhachHang>& ds){
	int chon;
	do{
		cout << "\n===== KHACH HANG =====\n";
		cout << "1.Them" << endl;
		cout << "2.Hien thi" << endl;
		cout << "3.Tim" << endl;
		cout << "4.Sua" << endl;
		cout << "5.Xoa" << endl;
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
				ds.lay(vitri).hienthi();
			} else if(chon==4){
				string ma, ten, tuoi;
				cout << "Nhap ma can sua: ";
				cin >> ma;
				int vitri=ds.timMa(ma);
				if(vitri==-1) throw "Khong tim thay";
				ds.lay(vitri).hienthi();
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
				ds.lay(vitri).hienthi();
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
void menuSIM(Repository<SIM>& ds){
	int chon;
	do{
		cout << "\n===== SIM =====\n";
		cout << "1.Them" << endl;
		cout << "2.Hien thi" << endl;
		cout << "3.Tim" << endl;
		cout << "4.Sua" << endl;
		cout << "5.Xoa" << endl;
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
				SIM x;
				x.nhap();
				if(ds.timMa(x.getMa())!=-1) throw "Ma da ton tai";
				ds.them(x);
				ghiFile("data/sim.txt",ds);
				cout << "Them thanh cong" << endl;
			} else if(chon == 2){
				ds.hienthi();
			} else if(chon==3){
				string ma;
				cout << "Nhap ma can tim: ";
				cin >> ma;
				int vitri=ds.timMa(ma);
				if(vitri==-1) throw "Khong tim thay";
				ds.lay(vitri).hienthi();
			} else if(chon==4){
				string ma, SDT, NhaMang;
				cout << "Nhap ma can sua: ";
				cin >> ma;
				int vitri=ds.timMa(ma);
				if(vitri==-1) throw "Khong tim thay";
				ds.lay(vitri).hienthi();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout << "SDT moi: ";
				getline(cin,SDT);
				cout << "NhaMang moi: ";
				getline(cin,NhaMang);
				if(!SDT.empty()) ds.lay(vitri).setSDT(SDT);
				if(!NhaMang.empty()) ds.lay(vitri).setNhaMang(NhaMang);
				ghiFile("data/sim.txt",ds);
				cout << "Sua thanh cong" << endl;
			} else if(chon==5){
				string ma;
				char xacnhan;
				cout << "Nhap ma can xoa: ";
				cin >> ma;
				int vitri=ds.timMa(ma);
				if(vitri==-1) throw "Khong tim thay";
				ds.lay(vitri).hienthi();
				cout << "Xoa?(Y/N)";
				cin >> xacnhan;
				if(xacnhan=='Y' || xacnhan=='y') {
					ds.xoa(vitri);
					ghiFile("data/sim.txt",ds);
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
int main(){
	Repository<KhachHang> dsKhachHang;
	Repository<SIM> dsSIM;
	docFile("data/khachhang.txt",dsKhachHang);
	docFile("data/sim.txt",dsSIM);
	int chon;
	do{
		cout << "\n===== QUAN LY KHACH HANG VA SIM =====\n";
		cout << "1.KHACH HANG" << endl;
		cout << "2.SIM" << endl;
		cout << "0.THOAT" << endl;
		cout << "Chon: ";
		if(!(cin >> chon)){
		cout << "Nhap sai dinh dang";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		chon=-1;
		continue;
		}if(chon==1) menuKhachHang(dsKhachHang);
		else if(chon==2) menuSIM(dsSIM);
		else if(chon!=0) cout << "Lua chon khong hop le" << endl;
	}while(chon!=0);
	return 0;
}
