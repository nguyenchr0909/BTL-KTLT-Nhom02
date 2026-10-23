#include"PhieuNapTien.h"
#include <sstream>
#include <vector>
#include <fstream> // cái này là thư viện để đọc và ghi file




 PhieuNapTien :: PhieuNapTien() : Entity(""), SoThueBao(""), MenhGia(0){}//TênLớp() : LớpCha(giá_trị_mặc_định), BiếnSố1(giá_trị), BiếnSố2(giá_trị)

void PhieuNapTien :: nhap(){
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
        cout << " Moi quy khach nhap menh gia " << endl;
        cin >> MenhGia;
        cin.ignore();// dùng cái này để bỏ cái enter mà thằng get line lấy nhập số tiền là nó tự ấy luôn
            if (MenhGia % 10000 != 0){
                    cout << " Menh gia nap phai la boi so cua 10000 " << endl;
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

    void PhieuNapTien :: display() {// override để kiểm tra m ghi đè cái hiển thị có bị sai ko
        cout << " Xac nhan " << ma << " SDT " << SoThueBao << " Gia tien " << endl;

}
string PhieuNapTien :: toFile(){// gom mấy cái biến đã khai bảo thành 1 dòng chữ năn cách với nhau bằng dấu ,
    return ma + ','  +  SoThueBao + ',' +  to_string(MenhGia);// vì Mệnh giá đnag để ll nma chỉ dc + chuỗi nên đổi về chuỗi

}
// sau khi gon thành 1 dòng nhờ to file thì đọc dòng chữ từ  tofile nạp lại vào biến
void PhieuNapTien :: fromFile(string line){
    stringstream ss(line);
    string MenhGiaTamThoi;
    getline(ss, ma, ',');
    getline(ss, SoThueBao, ',');
    getline (ss, MenhGiaTamThoi, ',');

    if(!MenhGiaTamThoi.empty()){
        MenhGia = stoll(MenhGiaTamThoi);// nêu mệnh giá tậm thời có ký tự thì sẽ gán cái mẹnh giá bừng mẹnh giá tam thời vad stoll là string to ll chuyển chuỗi chữ thành chuỗi số
    }
}
void GhiFileNapTien (vector<PhieuNapTien>& ds){
    ofstream fileOut("Phieunaptien.txt", ios::out);
    if (fileOut.is_open()) {
        for (auto& p : ds) {
            fileOut << p.toFile() << endl;
        }
        fileOut.close();
    } else {
        cout << "Loi: Khong the tao hoac mo file Phieunaptien.txt" << endl;
    }
}
  void docFileNapTien(vector<PhieuNapTien>& ds) {
    ifstream fileIn("Phieunaptien.txt");
    if (fileIn.is_open()) {
        string line;
        while (getline(fileIn, line)) {
            PhieuNapTien p;
            p.fromFile(line);
            ds.push_back(p);
        }
        fileIn.close();
    }
}

void NapTien() {
    vector<PhieuNapTien> ds;
    docFileNapTien(ds);// dùng để vừa vào chương trình sẽ gọi dữ liệu cũ vào cái đọc file
    int choice;
    while (true) {
        cout << "\n=== QUAN LY PHIEU NAP TIEN ===\n";
        cout << "1. Them phieu nap tien" << endl;
        cout << "2. Xem danh sach" << endl;
        cout << "3. Cap nhat menh gia" << endl;
        cout << "4. Xoa phieu nap tien" << endl;
        cout << "0. Quay lai Menu chinh" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();
    if ( choice == 1 ){
        PhieuNapTien p;
        p.nhap();
        ds.push_back(p);
        GhiFileNapTien(ds);// thêm xong phải ghi lại file luôn
        cout << "Them thanh cong =))" << endl;
    }else if (choice == 2 ){
        cout << "Danh sach nap tien " << endl;
        for (size_t i = 0; i < ds.size(); i++){
            cout << i+1 << ".";// vì i chạy từ 0
            ds[i].display();
        }
        }else if (choice == 3){
            string maTim;
            cout << "Nhap ma phieu can sua ";
            getline(cin, maTim);
            bool timThay = false;
            for (auto &p : ds) {
                if (p.getma() == maTim) {
                    ll mgMoi;
                    cout << " Nhap menh gia moi " << endl;
                    cin >> mgMoi; cin.ignore();
                    p.setMenhGia(mgMoi);
                    cout << "=> Cap nhat thanh cong" << endl;
                    timThay = true;
                    break;
                }
            if (timThay) {GhiFileNapTien(ds);}
            }
            if (!timThay){
            cout << "Khong tim thay ma phieu"  << endl;}
        } else if (choice == 4){
            string maXoa;
            cout << "Nhap ma phieu can xoa ";
            getline(cin, maXoa);
            bool timThay = false;
            for (auto it = ds.begin(); it != ds.end(); ++it) {
                if (it->getma() == maXoa) {
                    char xacNhan;
                    cout << "Xac nhan xoa (y/n)? ";
                    cin >> xacNhan; cin.ignore();
                    if (xacNhan == 'y' || xacNhan == 'Y') {
                        ds.erase(it);
                        cout << "Da xoa thanh cong " << endl;
                    }
                    timThay = true;
                    break;
                }
                if (timThay) {GhiFileNapTien(ds);}
            }
            if (!timThay) cout << "Khong tim thay ma phieu" << endl;
        }
        else if (choice == 0) break;
    }
}
