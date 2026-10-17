#ifndef REPOSITORY_H
#define REPOSITORY_H

#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include<iomanip>
using namespace std;

template <typename T>
class Repository{
	private:
		vector<T> ds;
	public:
		void them(T x){
			ds.push_back(x);
		}
		void hienthi(){
			for(int i=0; i<ds.size();i++){
				cout << right << setw(2) << i+1 << ". ";
				ds[i].hienthi();
			}
		}
		int kichthuoc(){
			return ds.size();
		}
		int timMa(string ma){
			for(int i=0; i<ds.size();i++){
				if(ds[i].getMa()==ma) return i; 
			}
			return -1;
		}
		void sua(int vitri, T x){
			if(vitri < 0 || vitri >= ds.size()) throw out_of_range("Vi tri khong hop le");
			ds[vitri]=x;
		}
		void xoa(int vitri){
			if(vitri < 0 || vitri >= ds.size()) throw out_of_range("Vi tri khong hop le");
			ds.erase(ds.begin() + vitri);
		}
		T& lay(int vitri){
			if(vitri < 0 || vitri >= ds.size()) throw out_of_range("Vi tri khong hop le");
			return ds[vitri];
		}
};
#endif

