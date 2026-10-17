#ifndef ThueBao_H
#define ThueBao_H

#include "Entity.h"
#include <string>
#include <vector>
using namespace std;


void runThueBao();
void nhaphanmuc();


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


    //Getter



    //Setter
    void nhap() ;

    // Hàm static để in toàn bộ danh sách thuê bao
    static void xuat(const vector<ThueBao>& danhSach);
    static void tim (const vector<ThueBao>& danhSach);


};

#endif

