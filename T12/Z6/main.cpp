//TP 2022/2023: LV 12, Zadatak 6
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <sstream>
#include <string>

template <typename TipEl>
class Matrica {
    char ime_matrice;
    int br_redova, br_kolona;
    TipEl **elementi;
    static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
    static void DealocirajMemoriju(TipEl **elementi, int br_redova);
    void KopirajElemente(TipEl **elementi);

public:
    Matrica(int br_redova, int br_kolona, char ime = 0);
    Matrica(const std::string &nazivDatoteke, bool odakleSeObnavlja);
    Matrica(const Matrica &m);
    Matrica(Matrica &&m);
    ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
    Matrica &operator=(const Matrica &m);
    Matrica &operator=(Matrica &&m);
    void Unesi();
    void Ispisi(int sirina_ispisa) const;
    Matrica<TipEl> operator+(const Matrica<TipEl> &m) const;
    Matrica<TipEl> operator-(const Matrica<TipEl> &m) const;
    Matrica<TipEl> operator*(const TipEl &broj) const;
    Matrica<TipEl> operator*(const Matrica<TipEl> &m) const;
    Matrica<TipEl> &operator+=(const Matrica<TipEl> &m);
    Matrica<TipEl> &operator-=(const Matrica<TipEl> &m);
    Matrica<TipEl> &operator*=(const TipEl &broj);
    TipEl *operator[](int red) const;
    TipEl &operator()(const int &red, const int &kolona)const;

    // Konverzija matrice u string
    operator std::string() const{
        std::stringstream ss;
        ss << "{";
        for (int i = 0; i < br_redova; i++){
            ss << "{";
            for (int j = 0; j < br_kolona; j++){
                ss << elementi[i][j];
                if (j < br_kolona - 1) ss << ",";
            }
            ss << "}";
            if (i < br_redova - 1) ss << ",";
        }
        ss << "}";
        return ss.str();
    }
    
    template< typename TipElemenata>
    friend std::istream& operator>>(std::istream& stream, Matrica<TipElemenata>& m);

    template< typename TipElemenata>
    friend std::ostream& operator<<(std::ostream& stream, Matrica<TipElemenata>& m);

    template< typename TipElemenata>
    friend Matrica<TipElemenata> operator*(int broj, const Matrica <TipElemenata> &m);

    template< typename TipElemenata>
    friend Matrica<TipElemenata> operator*(const Matrica <TipElemenata> &m, int broj);
};

template<typename TipEl>
Matrica<TipEl> Matrica<TipEl>::operator+(const Matrica<TipEl> &m) const{
    if (br_redova != m.br_redova || br_kolona != m.br_kolona)  throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica<TipEl> rezultat(br_redova, br_kolona);
    for (int i = 0; i < br_redova; i++)
        for (int j = 0; j < br_kolona; j++)
            rezultat.elementi[i][j] = elementi[i][j] + m.elementi[i][j];
    return rezultat;
}

template<typename TipEl>
Matrica<TipEl> Matrica<TipEl>::operator-(const Matrica<TipEl> &m) const{
    if (br_redova != m.br_redova || br_kolona != m.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica<TipEl> rezultat(br_redova, br_kolona);
    for (int i = 0; i < br_redova; i++)
        for (int j = 0; j < br_kolona; j++)
            rezultat.elementi[i][j] = elementi[i][j] - m.elementi[i][j];
    return rezultat;
}

template<typename TipEl>
Matrica<TipEl> Matrica<TipEl>::operator*(const TipEl &broj) const{
    Matrica<TipEl> rezultat(br_redova, br_kolona);
    for (int i = 0; i < br_redova; i++)
        for (int j = 0; j < br_kolona; j++)
            rezultat.elementi[i][j] = elementi[i][j] * broj;
    return rezultat;
}

template<typename TipEl>
Matrica<TipEl> Matrica<TipEl>::operator*(const Matrica<TipEl> &m) const{
    if (br_kolona != m.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Matrica<TipEl> rezultat(br_redova, m.br_kolona);
    for (int i = 0; i < br_redova; i++){
        for (int j = 0; j < m.br_kolona; j++){
            rezultat.elementi[i][j] = 0;
            for (int k = 0; k < br_kolona; k++)
                rezultat.elementi[i][j] += elementi[i][k] * m.elementi[k][j];
        }
    }
    return rezultat;
}

template<typename TipEl>
Matrica<TipEl> & Matrica<TipEl>::operator+=(const Matrica<TipEl> &m){
    *this = *this + m;
    return *this;
}

template<typename TipEl>
Matrica<TipEl> & Matrica<TipEl>::operator-=(const Matrica<TipEl> &m){
    *this = *this - m;
    return *this;
}

template<typename TipEl>
Matrica<TipEl> & Matrica<TipEl>::operator*=(const TipEl &broj){
    *this = *this * broj;
    return *this;
}

template<typename TipEl>
TipEl * Matrica<TipEl>::operator[](int red) const{
    return elementi[red];
}

template<typename TipEl>
TipEl & Matrica<TipEl>::operator()(const int &red, const int &kolona)const{
    if (red < 1 || red > br_redova || kolona < 1 || kolona > br_kolona) throw std::range_error("Neispravan indeks");
    return elementi[red - 1][kolona - 1];
}

template<typename TipEl>
std::istream& operator>>(std::istream& stream, Matrica<TipEl>& m){
    for (int i = 0; i < m.br_redova; i++) {
        for (int j = 0; j < m.br_kolona; j++) {
            std::cout << m.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
            stream >> m.elementi[i][j];
        }
    }
    return stream;
}

template<typename TipEl>
std::ostream& operator<<(std::ostream& stream, Matrica<TipEl>& m){
    auto sirina=stream.width();
    for (int i = 0; i < m.br_redova; i++) {
        for (int j = 0; j < m.br_kolona; j++)
            stream<<std::setw(sirina)<<m.elementi[i][j];
        stream <<std::endl;
    }
    return stream;
}

template <typename TipEl>
TipEl **Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona){
    TipEl **elementi = new TipEl *[br_redova]{};
    try{
        for (int i = 0; i < br_redova; i++)
            elementi[i] = new TipEl[br_kolona];
    }
    catch (...){
        DealocirajMemoriju(elementi, br_redova);
        throw;
    }
    return elementi;
}

template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova){
    for (int i = 0; i < br_redova; i++)
        delete[] elementi[i];
    delete[] elementi;
}

template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) : br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime), elementi(AlocirajMemoriju(br_redova, br_kolona)){}

template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi){    
    for (int i = 0; i < br_redova; i++)
        for (int j = 0; j < br_kolona; j++)
            Matrica::elementi[i][j] = elementi[i][j];
}

template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova), br_kolona(m.br_kolona), ime_matrice(m.ime_matrice), elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)){
    KopirajElemente(m.elementi);
}

template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova), br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice){
    m.br_redova = 0;
    m.elementi = nullptr;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(const Matrica<TipEl> &m){
    if (br_redova < m.br_redova || br_kolona < m.br_kolona){
        TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
        DealocirajMemoriju(elementi, br_redova);
        elementi = novi_prostor;
    }
    else if (br_redova > m.br_redova)
        for (int i = m.br_redova; i < br_redova; i++)
            delete elementi[i];
    br_redova = m.br_redova;
    br_kolona = m.br_kolona;
    ime_matrice = m.ime_matrice;
    KopirajElemente(m.elementi);
    return *this;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(Matrica<TipEl> &&m){
    std::swap(br_redova, m.br_redova);
    std::swap(br_kolona, m.br_kolona);
    std::swap(ime_matrice, m.ime_matrice);
    std::swap(elementi, m.elementi);
    return *this;
}

template <typename TipEl>
Matrica<TipEl> ZbirMatrica(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
    if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
    for (int i = 0; i < m1.br_redova; i++)
        for (int j = 0; j < m1.br_kolona; j++)
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return m3;
}

template <typename TipEl>
Matrica<TipEl> operator+(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2){
    return ZbirMatrica(m1, m2);
}

template <typename TipEl>
Matrica<TipEl> operator-(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2){
    if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica<TipEl> rezultat(m1.br_redova, m1.br_kolona);
    for (int i = 0; i < m1.br_redova; i++)
        for (int j = 0; j < m1.br_kolona; j++)
            rezultat.elementi[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
    return rezultat;
}

template <typename TipEl>
Matrica<TipEl> operator*(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2){
    if (m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Matrica<TipEl> rezultat(m1.br_redova, m2.br_kolona);
    for (int i = 0; i < m1.br_redova; i++)
        for (int j = 0; j < m2.br_kolona; j++){
            TipEl suma = 0;
            for (int k = 0; k < m1.br_kolona; k++)
                suma += m1.elementi[i][k] * m2.elementi[k][j];
            rezultat.elementi[i][j] = suma;
        }
    return rezultat;
}

template <typename TipEl>
Matrica<TipEl> &operator+=(Matrica<TipEl> &m1, const Matrica<TipEl> &m2){
    m1 = m1 + m2;
    return m1;
}

template <typename TipEl>
Matrica<TipEl> &operator-=(Matrica<TipEl> &m1, const Matrica<TipEl> &m2){
    m1 = m1 - m2;
    return m1;
}

template <typename TipEl>
Matrica<TipEl> &operator*=(Matrica<TipEl> &m1, const Matrica<TipEl> &m2){
    m1 = m1 * m2;
    return m1;
}

template< typename TipElemenata>
Matrica<TipElemenata> operator*(int broj, const Matrica <TipElemenata> &m){
    auto rezultat=m;
    for(int i=0; i<m.br_redova; i++){
        for(int j=0; j<m.br_kolona; j++)
            rezultat.elementi[i][j]*=broj;
    }
    return rezultat;
}

template< typename TipElemenata>
Matrica<TipElemenata> operator*(const Matrica <TipElemenata> &m, int broj){
    return broj*m;
}

int main(){
        int m, n;
        std::cout << "Unesi broj redova i kolona za matrice:\n";
        std::cin >> m >> n;
    try{
        Matrica<double> a(m, n, 'A'), b(m, n, 'B');
        std::cout << "Unesi matricu A:\n";
        std::cin >> a;
        std::cout << "Unesi matricu B:\n";
        std::cin >> b;
        std::cout << "Zbir ove dvije matrice je:\n";
        auto c=a+b;
        std::cout << std::setw(7) << c;
        return 0;
    }
    catch (std::exception &e){
        std::cerr << "Greska: " << e.what() << std::endl;
        return 1;
    }
}