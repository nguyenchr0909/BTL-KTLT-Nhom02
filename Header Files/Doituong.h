#ifndef DOITUONG_H
#define DOITUONG_H

#include<iostream>
#include<string>
using namespace std;

class Doituong{
	protected:
		string ma;
	public:
		virtual ~Doituong(){}
		virtual void nhap()=0;
		virtual void hienthi()=0;
		virtual string toFile()=0;
		virtual void fromFile(string Dulieu)=0;
		string getMa(){
			return ma;
		}
		void setMa(string ma){
			this->ma = ma;
		}
};
#endif

