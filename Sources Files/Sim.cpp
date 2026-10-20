#include"Sim.h"
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<limits>
using namespace std;

void runSIM(){
	Repository<SIM> ds;
	docFile("data/sim.txt",ds);
	menuSIM(ds);
}
SIM :: SIM() : Entity(""){
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
void SIM :: display(){
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
void menuSIM(Repository<SIM>& ds){
	int chon;
	do{
		cout << "\n===== SIM =====\n";
		cout << "1.Them sim" << endl;
		cout << "2.Hien thi danh sach sim" << endl;
		cout << "3.Tim sim" << endl;
		cout << "4.Sua sim" << endl;
		cout << "5.Xoa sim" << endl;
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
				ds.lay(vitri).display();
			} else if(chon==4){
				string ma, SDT, NhaMang;
				cout << "Nhap ma can sua: ";
				cin >> ma;
				int vitri=ds.timMa(ma);
				if(vitri==-1) throw "Khong tim thay";
				ds.lay(vitri).display();
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
				ds.lay(vitri).display();
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
