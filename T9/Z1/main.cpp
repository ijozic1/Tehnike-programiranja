//TP 2022/2023: LV 9, Zadatak 1
#include <iostream>
#include <cmath>

class Vektor3d {
    double x, y, z;
  public:
    void Postavi(double x, double y, double z) { 
        Vektor3d::x = x; Vektor3d::y = y; Vektor3d::z = z;
    }
    void PostaviX(double x){
        Vektor3d::x=x;
    }
    void PostaviY(double y){
        Vektor3d::y=y;
    }
    void PostaviZ(double z){
        Vektor3d::z=z;
    }
    void Ocitaj(double &x, double &y, double &z) const {
        x = Vektor3d::x; y = Vektor3d::y; z = Vektor3d::z;
    }
    void Ispisi() const {
        std::cout << "{" << x << "," << y << "," << z << "}";
    }
    double DajX() const { return x; }
    double DajY() const { return y; }
    double DajZ() const { return z; }
    double DajDuzinu() const { return std::sqrt(x * x + y * y + z * z); }
    Vektor3d &PomnoziSaSkalarom(double s) { 
        x *= s; y *= s; z *= s;
        return *this; 
    }
    Vektor3d &SaberiSa(const Vektor3d &v) {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
    Vektor3d v3;
    v3.x = v1.x + v2.x; v3.y = v1.y + v2.y; v3.z = v1.z + v2.z;
    return v3;
}

int main (){


	return 0;
}
