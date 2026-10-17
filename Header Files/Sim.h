#ifndef SIM_H
#define SIM_H

#include<iostream>
#include<string>
#include"Doituong.h"
using namespace std;

class SIM : public Doituong{
	private:
		string SDT;
		string NhaMang;
	public:
		SIM();
		void nhap() override;
		void hienthi() override;
		string toFile() override;
		void fromFile(string DuLieu) override;
		string getSDT();
		string getNhaMang();
		void setSDT(string SDT);
		void setNhaMang(string NhaMang);
};
#endif
