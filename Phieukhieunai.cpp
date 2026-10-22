#include "PhieuKhieuNai.h"
#include <sstream>//thư viện giúp cắt chuỗi (stringstream)
#include <vector>
#include <fstream> // cái này là thư viện để đọc và ghi file




PhieuKhieuNai :: PhieuKhieuNai() : Entity(""), SoThueBao(""), NoiDung(""), TrangThai("Chua xu ly"){}//TênLớp() : LớpCha(giá_trị_mặc_định), BiếnSố1(giá_trị), BiếnSố2(giá_trị)

void PhieuKhieuNai :: nhap(){
    while (true){
        while (true){
        cout << " Moi quy khach nhap ma phieu" << endl;
        getline(cin, ma); // cái này chỗ th Nguyên
            if (ma.length() == 0){
                cout << "Khong duoc de trong ma !!" << endl;
            }else{break;}
        }


        while (true){
        cout << " Moi quy khach nhap so thue bao " << endl;
        getline(cin, SoThueBao);
            if (SoThueBao.length() < 10){
                cout << " SDT phai bao gom 10 chu so " << endl;
            }else{break;}
        }


       while (true){
        cout << " Ban gap van de gi ? " << endl;
        getline(cin, NoiDung);
            if ( NoiDung.length() == 0){
                cout << "Noi dung khong duoc de trong " << endl;
            }else{break;}
       }

        cout << " Ban chac chua ?"<< endl;
            char choice;
            cin >> choice;
        if ( choice == 'y' || choice == 'Y' ){
            break;
        }else{
            cout << " Vui long nhap lai " << endl;}

}
}
void PhieuKhieuNai :: display(){
    cout << "Xac Nhan" << ma << "STD" << SoThueBao << "NoiDung" << NoiDung << endl;
}
string PhieuKhieuNai :: toFile(){// gom mấy cái biến đã khai bảo thành 1 dòng chữ năn cách với nhau bằng dấu ,
    return ma + ','  + SoThueBao + ',' + NoiDung + ',' + TrangThai;

}
// sau khi gon thành 1 dòng nhờ to file thì đọc dòng chữ từ  tofile nạp lại vào biến
void PhieuKhieuNai :: fromFile(string line){
    stringstream ss(line);
    getline(ss, ma, ',');
    getline(ss, SoThueBao, ',');
    getline(ss, NoiDung, ',');
    getline(ss, TrangThai, ',');
}
void ghiFileKhieuNai(vector<PhieuKhieuNai>& ds) {
    ofstream fileOut("Phieukhieunai.txt", ios::out);
    if (fileOut.is_open()) {
        for (auto& p : ds) {
        fileOut << p.toFile() << endl; // Đẩy từng dòng dữ liệu vào file
        }
        fileOut.close();
    } else {
        cout << "Loi: Khong the tao hoac mo file Phieukhieunai.txt" << endl;
    }
}

void docFileKhieuNai(vector<PhieuKhieuNai>& ds) {
    ifstream fileIn("Phieukhieunai.txt");
    if (fileIn.is_open()) {
        string line;
        while (getline(fileIn, line)) {
            PhieuKhieuNai p;
            p.fromFile(line);
            ds.push_back(p);
        }
        fileIn.close();
    }
}
void KhieuNai() {
    vector<PhieuKhieuNai> ds;
    docFileKhieuNai(ds);
    int choice;
    while (true) {
        cout << "\n=== QUAN LY PHIEU KHIEU NAI ===\n";
        cout << "1. Them phieu khieu nai" << endl;
        cout << "2. Xem danh sach" << endl ;
        cout << "3. Cap nhat trang thai" << endl;
        cout << "4. Xoa phieu khieu nai" << endl;
        cout << "0. Quay lai Menu chinh" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            PhieuKhieuNai p;
            p.nhap();
            ds.push_back(p);
            ghiFileKhieuNai(ds);// thêm khiếu nại xong là lưu lại luôn
            cout << "Them thanh cong" << endl;
        }
        else if (choice == 2) {
            cout << "Danh sach phieu khieu nai" << endl;
            for (size_t i = 0; i < ds.size(); i++) {
                cout << i + 1 << ". ";
                ds[i].display();
            }
        }
        else if (choice == 3) {
            string maTim;
            cout << "Nhap ma phieu can sua" << endl;
            getline(cin, maTim);
            bool timThay = false;
            for (auto &p : ds) {
                if (p.getma() == maTim) {
                    string ttMoi;
                    cout << "Nhap trang thai moi" << endl;
                    getline(cin, ttMoi);
                    p.setTrangThai(ttMoi);
                    cout << "Cap nhat thanh cong" << endl;
                    timThay = true;
                    break;
                }
                if (timThay) ghiFileKhieuNai(ds);
            }
            if (!timThay) cout << "Khong tim thay ma phieu" << endl;
        }
        else if (choice == 4) {
            string maXoa;
            cout << "Nhap ma phieu can xoa" << endl;
            getline(cin, maXoa);
            bool timThay = false;
        for (auto it = ds.begin(); it != ds.end(); ++it) {
            if (it->getma() == maXoa) {
                if (it->getTrangThai() == "Dang xu ly") {
                    cout << "Loi: Phieu dang o tien trinh 'Dang xu ly', khong duoc xoa";
        } else {
             char xacNhan;
             cout << "Xac nhan xoa (y/n)? ";
             cin >> xacNhan; cin.ignore();
            if (xacNhan == 'y' || xacNhan == 'Y') {
               ds.erase(it);
                cout << " Da xoa thanh cong " << endl;
                }
            }
            timThay = true;
            break;
            }
            }
            if (timThay) {ghiFileKhieuNai(ds);}
            if (!timThay)
            {cout << "Khong tim thay ma phieu" << endl;}
        }
        else if (choice == 0) break;
    }
}
