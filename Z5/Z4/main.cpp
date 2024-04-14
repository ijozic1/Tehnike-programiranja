//TP 2022/2023: Zadaća 5, Zadatak 4
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <sstream>
#include <string>
#include <vector>

template <typename TipEl>
class Matrica {
    char ime_matrice;
    int br_redova, br_kolona;
    TipEl **elementi;
    static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
    static void DealocirajMemoriju(TipEl **elementi, int br_redova);
    void KopirajElemente(TipEl **elementi);
    bool PretvoriStringUElement(const std::string &s, TipEl &element) const;
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

    void SacuvajUTekstualnuDatoteku(const std::string &nazivDatoteke)const;
    void SacuvajUBinarnuDatoteku(const std::string &nazivDatoteke)const;
    Matrica<TipEl> ObnoviIzTekstualneDatoteke(const std::string &nazivDatoteke);
    Matrica<TipEl> ObnoviIzBinarneDatoteke(const std::string &nazivDatoteke);
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
Matrica<TipEl>::Matrica(const std::string &nazivDatoteke, bool odakleSeObnavlja){
    if(odakleSeObnavlja) ObnoviIzBinarneDatoteke(nazivDatoteke);
    else ObnoviIzTekstualneDatoteke(nazivDatoteke);
}

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

template<typename TipEl>
bool Matrica<TipEl>::PretvoriStringUElement(const std::string &s, TipEl &element) const{
    std::istringstream linija(s);
    if(linija>>element){
        char neprocitaniZnak;
        if(!(linija>>neprocitaniZnak)) return true;
    }
    return false;
}

template<typename TipEl>
void Matrica<TipEl>::SacuvajUTekstualnuDatoteku(const std::string &nazivDatoteke)const{
    std::ofstream izlazni_tok(nazivDatoteke);
    if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
    for(int i=0; i<br_redova; i++){
        for(int j=0; j<br_kolona; j++){
            izlazni_tok<<elementi[i][j];
            if(j!=br_kolona-1) izlazni_tok<<",";
        }
        izlazni_tok<<std::endl;
    }
    izlazni_tok.close();
}

template<typename TipEl>
void Matrica<TipEl>::SacuvajUBinarnuDatoteku(const std::string &nazivDatoteke)const{
    std::ofstream izlazni_tok(nazivDatoteke, std::ios::binary);
    if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
    
    izlazni_tok.write(reinterpret_cast<const char*>(&br_redova), sizeof(br_redova));
    izlazni_tok.write(reinterpret_cast<const char*>(&br_kolona), sizeof(br_kolona));

    for(int i=0; i<br_redova; i++) izlazni_tok.write(reinterpret_cast<char*>(elementi[i]), br_kolona*sizeof(TipEl));
    if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
    izlazni_tok.close();
}

template<typename TipEl>
Matrica<TipEl> Matrica<TipEl>::ObnoviIzTekstualneDatoteke(const std::string &nazivDatoteke){
    std::ifstream ulazni_tok(nazivDatoteke);
    if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");

    std::vector<std::vector<TipEl>> novaMatrica;
    std::string redDatoteke;
    br_redova=0; br_kolona=0;
    while(std::getline(ulazni_tok, redDatoteke)){
        br_redova++;
        int trenutni_br_kolona=1;
        std::string element;
        for(char znak : redDatoteke){
            if(znak==','){
                trenutni_br_kolona++;
                TipEl vrijednost;
                if(!PretvoriStringUElement(element, vrijednost)){
                    ulazni_tok.close();
                    throw std::logic_error("Datoteka sadrzi besmislene podatke");
                }
                element="";
            }
            else element+=znak;
        }
        if(br_kolona==0) br_kolona=trenutni_br_kolona;
        else if(trenutni_br_kolona!=br_kolona){
            ulazni_tok.close();
            throw std::logic_error("Datoteka sadrzi besmislene podatke");
        }
    }

    if(br_redova==0 || br_kolona==0){
        ulazni_tok.close();
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
    }

    TipEl ** noviPok=AlocirajMemoriju(br_redova, br_kolona);
    ulazni_tok.close();
    ulazni_tok.open(nazivDatoteke);
    int i=0;
    while(std::getline(ulazni_tok, redDatoteke)){
        int j=0;
        std::string element;
        for(char znak : redDatoteke){
            if(znak==','){
                TipEl vrijednost;
                if(!PretvoriStringUElement(element, vrijednost)){
                    DealocirajMemoriju(noviPok, br_redova);
                    ulazni_tok.close();
                    throw std::logic_error("Datoteka sadrzi besmislene podatke");
                }
                noviPok[i][j]=vrijednost;
                j++;
                element="";
            }
            else element+=znak;
        }
        if(element.size()!=0){
            TipEl vrijednost;
            if(!PretvoriStringUElement(element, vrijednost)){
                DealocirajMemoriju(noviPok, br_redova);
                ulazni_tok.close();
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            }
            noviPok[i][j]=vrijednost;
        }
        i++;
    }
    ulazni_tok.close();
    elementi=noviPok;
    return *this;
}

template<typename TipEl>
Matrica<TipEl> Matrica<TipEl>::ObnoviIzBinarneDatoteke(const std::string &nazivDatoteke){
    std::ifstream ulazni_tok (nazivDatoteke, std::ios::binary);
    if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");

    int brojRedova=0, brojKolona=0;
    ulazni_tok.read(reinterpret_cast<char*>(&brojRedova), sizeof(brojRedova));
    ulazni_tok.read(reinterpret_cast<char*>(&brojKolona), sizeof(brojKolona));
    if(brojRedova<=0 || brojKolona<=0) throw std::logic_error("Datoteka sadrzi besmislene podatke");

    br_redova=brojRedova; br_kolona=brojKolona;
    elementi=AlocirajMemoriju(br_redova, br_kolona);  

    for(int i=0; i<br_redova; i++)
        for(int j=0; j<br_kolona; j++)
            ulazni_tok.read(reinterpret_cast<char*>(&elementi[i][j]), sizeof(TipEl));
    
    if(!ulazni_tok) throw std::logic_error("Problemi pri citanju datoteke");
    ulazni_tok.close();
    return *this;
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
        a.SacuvajUTekstualnuDatoteku("matrica.txt");
        std::cout<<"Matrica je snimljena u tekstualnu datoteku."<<std::endl;
        b.SacuvajUBinarnuDatoteku("matrica.bin");
        std::cout<<"Matrica je snimljena u binarnu datoteku."<<std::endl;
        Matrica<double> obnovljenaIzTxt("matrica.txt", false);
        std::cout<<"Matrica je obnovljena iz tekstualne datoteke."<<std::endl;
        std::cout << std::setw(7) << obnovljenaIzTxt;
        Matrica<double> obnovljenaIzBin("matrica.bin", true);
        std::cout<<"Matrica je obnovljena iz binarne datoteke."<<std::endl;
        std::cout << std::setw(7) << obnovljenaIzBin;
        return 0;
    }
    catch (std::exception &e){
        std::cerr << "Greska: " << e.what() << std::endl;
        return 1;
    }
}