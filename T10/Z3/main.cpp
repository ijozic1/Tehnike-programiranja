//TP 2022/2023: LV 10, Zadatak 3
#include <iostream>
#include <cmath>

class Vektor3d {
    double koordinate[3];
    mutable int brojac_ispisa=0;
  public:
    Vektor3d(){Postavi(0,0,0);}
    Vektor3d(double x, double y, double z){Postavi(x,y,z);}
    Vektor3d(const Vektor3d &v):brojac_ispisa(0){koordinate[0]=v.koordinate[0]; koordinate[1]=v.koordinate[1]; koordinate[2]=v.koordinate[2]; }
    void Postavi(double x, double y, double z) { 
        Vektor3d::koordinate[0] = x; Vektor3d::koordinate[1] = y; Vektor3d::koordinate[2] = z;
    }
    void PostaviX(double x){
        Vektor3d::koordinate[0] = x;
    }
    void PostaviY(double y){
        Vektor3d::koordinate[1] =y;
    }
    void PostaviZ(double z){
        Vektor3d::koordinate[2] = z;
    }
    void Ocitaj(double &x, double &y, double &z) const {
        x = Vektor3d::koordinate[0]; y = Vektor3d::koordinate[1]; z = Vektor3d::koordinate[2];
    }
    int DajBrojIspisa() const{
        return brojac_ispisa;
    }
    void Ispisi() const {
        std::cout << "{" << koordinate[0] << "," << koordinate[1] << "," << koordinate[2] << "}";
        brojac_ispisa++;
    }
    double DajX() const { return koordinate[0]; }
    double DajY() const { return koordinate[1]; }
    double DajZ() const { return koordinate[2]; }
    double DajDuzinu() const { return std::sqrt(koordinate[0] * koordinate[0] + koordinate[1] * koordinate[1] + koordinate[2] * koordinate[2]); }
    Vektor3d &PomnoziSaSkalarom(double s) { 
        koordinate[0] *= s; koordinate[1] *= s; koordinate[2] *= s;
        return *this; 
    }
    Vektor3d &SaberiSa(const Vektor3d &v) {
        koordinate[0] += v.koordinate[0]; koordinate[1] += v.koordinate[1]; koordinate[2] += v.koordinate[2];
        return *this;
    }
    friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
    Vektor3d v3;
    v3.koordinate[0] = v1.koordinate[0] + v2.koordinate[0]; v3.koordinate[1] = v1.koordinate[1] + v2.koordinate[1]; v3.koordinate[2] = v1.koordinate[2] + v2.koordinate[2];
    return v3;
}

int main (){
    Vektor3d v1(1, 1, 1);
    for(int i=0;i<3;i++) {v1.Ispisi();std::cout<<" ";}
    std::cout<<std::endl;
    const Vektor3d v2(v1);
    v2.Ispisi(); std::cout << std::endl;
    std::cout << v2.DajBrojIspisa() << std::endl;
    const Vektor3d v3(v2);
    std::cout << v3.DajBrojIspisa();
	return 0;
}