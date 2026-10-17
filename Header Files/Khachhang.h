#ifndef KHACHHANG_H
#define KHACHHANG_H

#include<iostream>
#include<string>
#include "Doituong.h"
using namespace std;

class KhachHang : public Doituong{
	private:
		string ten;
		int tuoi;
	public:
		KhachHang();
		void nhap() override;
		void hienthi() override;
		string toFile() override;
		void fromFile(string DuLieu) override;
		string getTen();
		int getTuoi();
		void setTen(string ten);
		void setTuoi(int tuoi);
};
#endif
