/*
Ma use case: CS_04
Ho va ten: Nguyen Dang Toan
MSV B24DCVT353
*/
#ifndef SIM_H
#define SIM_H

#include<iostream>
#include<string>
#include"Entity.h"
#include"Repository.h"
using namespace std;

class SIM : public Entity{
	private:
		string SDT;
		string NhaMang;
	public:
		SIM();
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
		string getSDT();
		string getNhaMang();
		void setSDT(string SDT);
		void setNhaMang(string NhaMang);
};
void menuSIM(Repository<SIM>& ds);
void runSIM();
#endif
