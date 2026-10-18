#ifndef ThueBao_H
#define ThueBao_H

#include "Entity.h"
#include <string>
#include <vector>
using namespace std;


void runThueBao();
bool check_int();

class ThueBao: public Entity
{
  private:
     string Loai_Thue_Bao;
     double Han_muc;
     string Uu_dai;


  public:

    ThueBao() : Entity(""), Loai_Thue_Bao(""),
                Han_muc(0), Uu_dai("") {}

    ThueBao(const string &ma, const string &loai, double no, string uudai)
        : Entity(ma), Loai_Thue_Bao(loai),
          Han_muc(no), Uu_dai(uudai) {}




    void hienThi() override;
    void        nhap(const vector<ThueBao>& danhSach);
    static void xuat(const vector<ThueBao>& danhSach);
    static void tim (const vector<ThueBao>& danhSach);
    static void sua ( vector<ThueBao>& danhSach);



};

#endif

