//TP 2022/2023: Zadaća 3, Zadatak 3
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>

template <typename TipElemenata>
struct Matrica {
    char ime_matrice; // Koristi se samo u funkciji "UnesiMatricu"
    int br_redova, br_kolona;
    TipElemenata **elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!!!
};

template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat) {
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi = nullptr;
}

template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona, char ime = 0) {
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova; mat.br_kolona = br_kolona; mat.ime_matrice = ime;
    mat.elementi = new TipElemenata*[br_redova]{};
    try {
        for(int i = 0; i < br_redova; i++) mat.elementi[i] = new TipElemenata[br_kolona];
    }
    catch(...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}

template <typename TipElemenata>
void UnesiMatricu(Matrica<TipElemenata> &mat) {
    for(int i = 0; i < mat.br_redova; i++)
        for(int j = 0; j < mat.br_kolona; j++) {
            if(i!=0 || j!=0) std::cout<<std::endl;
            std::cout<< mat.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
            std::cin >> mat.elementi[i][j];
        }
}

template <typename TipElemenata>
void IspisiMatricu(Matrica<TipElemenata> mat, int sirina_ispisa, int preciznost=6, bool treba_brisati=false) {
    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++){
            std::cout << /*std::fixed<<*/std::setw(sirina_ispisa) <<std::setprecision(preciznost)<< mat.elementi[i][j];
        }
        std::cout << std::endl;
    }
    if(treba_brisati) UnistiMatricu(mat);
}

template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
    const Matrica<TipElemenata> &m2) {
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
    auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return m3;
}

template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &mat1, const Matrica<TipElemenata> &mat2){
    if(mat1.br_kolona!=mat2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    auto mat3=StvoriMatricu<TipElemenata>(mat1.br_redova, mat2.br_kolona);
    for(int i=0; i<mat1.br_redova; i++)
        for(int j=0; j<mat2.br_kolona; j++){
            mat3.elementi[i][j]=0;
            for(int k=0; k<mat1.br_kolona; k++) 
                mat3.elementi[i][j]+=mat1.elementi[i][k]*mat2.elementi[k][j];
        }
    return mat3;
}

template <typename TipElemenata> 
Matrica<TipElemenata> ProduktMatriceISkalara(const Matrica<TipElemenata> &mat, double skalar){
    Matrica<TipElemenata> rezultat=StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
    for(int i=0; i<mat.br_redova; i++)
        for(int j=0; j<mat.br_kolona; j++)
            rezultat.elementi[i][j]=mat.elementi[i][j]*skalar;
    return rezultat;
}

template <typename TipElemenata>
Matrica<TipElemenata> MatricniHarmonijskiPolinom(const Matrica<TipElemenata> &mat, int n){
    if(mat.br_redova!=mat.br_kolona) throw std::domain_error("Matrica nije kvadratna");
    if(n<=0) throw std::domain_error("Pogresan parametar n");
    auto rezultat=StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
    try{
        auto trenutni_stepen=StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
        try{
            auto trenutni_polinom=StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
            //Inicijalizacija matrica
            for(int i=0; i<mat.br_redova; i++){
                for(int j=0; j<mat.br_kolona; j++){
                    trenutni_stepen.elementi[i][j]=mat.elementi[i][j];
                    trenutni_polinom.elementi[i][j]=mat.elementi[i][j];
                    rezultat.elementi[i][j]=mat.elementi[i][j];
                }
            }
            try{
                //Kreiranje polinoma
                for(int i=2; i<=n; i++){
                    auto temp=trenutni_stepen;
                    trenutni_stepen=ProduktMatrica<TipElemenata>(trenutni_stepen, mat);
                    UnistiMatricu(temp); UnistiMatricu(trenutni_polinom);
                    trenutni_polinom=ProduktMatriceISkalara(trenutni_stepen, 1./i);
                    temp=rezultat;
                    rezultat=ZbirMatrica(rezultat, trenutni_polinom);
                    UnistiMatricu(temp);
                }
            UnistiMatricu(trenutni_stepen); UnistiMatricu(trenutni_polinom);
            }
            catch(...){
                UnistiMatricu(trenutni_polinom);
                throw;
            }
        }
        catch(...){
            UnistiMatricu(trenutni_stepen);
            throw;
        }
    }
    catch(...){
        UnistiMatricu(rezultat);
        throw;
    }
    return rezultat;
}

int main() {
    Matrica<double> a; // AUTOMATSKA INICIJALIZACIJA!!!
    int dimenzija=0;
    std::cout << "Unesite dimenziju kvadratne matrice: ";
    std::cin >> dimenzija;
    try {
        a = StvoriMatricu<double>(dimenzija, dimenzija, 'A');
        std::cout << "\nUnesite elemente matrice A:\n";
        UnesiMatricu(a);
        int red_polinoma=0;
        std::cout<<"\nUnesite red polinoma: ";
        std::cin>>red_polinoma;
        std::cout << "\nMatricni harmonijski polinom:\n";
        IspisiMatricu(MatricniHarmonijskiPolinom(a, red_polinoma), 10, 6, true);
        UnistiMatricu(a);
    }
    catch(std::bad_alloc) {
        std::cout << "Nema dovoljno memorije!\n";
        UnistiMatricu(a);
    }
    catch(std::domain_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
        UnistiMatricu(a);
    }
    catch(...){
        std::cout<<"Nema dovoljno memorije!\n";
        UnistiMatricu(a);
    }
    return 0;
}