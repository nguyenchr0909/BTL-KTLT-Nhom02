/*
Ma use case: CS_03
Ho va ten: Nguyen Dang Toan
MSV B24DCVT353
*/
#ifndef KHACHHANG_H
#define KHACHHANG_H
#include<iostream>
#include<string>
#include "Entity.h"
#include"Repository.h"
using namespace std;

class KhachHang : public Entity{
	private:
		string ten;
		int tuoi;
	public:
		KhachHang();
		void nhap();
		void display() override;
		string toFile();
		void fromFile(string DuLieu);
		string getMa(){
			return ma;
		}
		void setMa(string ma){
			this->ma=ma;
		}
		string getTen();
		int getTuoi();
		void setTen(string ten);
		void setTuoi(int tuoi);
};
void menuKhachHang(Repository<KhachHang>& ds);
void runKhachHang();
#endif
