//TP 2022/2023: LV 7, Zadatak 1
#include <iostream>
#include <cmath>
#include <cstring>

int UnesiRecenicu(char niz[], int velicina) {
	char znak = getchar();
	if (znak == '\n') znak=getchar();
	int i = 0;
	while (i < velicina-1 && znak != '\n') {
		niz[i] = znak;
		i++;
		znak = getchar();
	}
	niz[i]='\0';
    return i;
}

auto KreirajMatricu(const int &brRecenica){
    char **matrica=new char*[brRecenica]{};
    try{
        char recenica[1000];
        for(int i=0; i<brRecenica; i++){
            int velicina=UnesiRecenicu(recenica, 1000);
            matrica[i]=new char[velicina+1];
            std::strcpy(matrica[i], recenica);
        }
        for(int i=1; i<brRecenica; i++){
            if (std::strcmp(matrica[i - 1], matrica[i]) > 0) {
                char* pomocni = matrica[i - 1];
                matrica[i - 1] = matrica[i];
                matrica[i] = pomocni;
                i = 0;
            }
        }
        return matrica;
    }
    catch(...){
        for(int i=0; i<brRecenica; i++) delete[] matrica[i];
        delete[] matrica;
        throw;
    }
}

void IspisiRecenicu(const char* recenica){
    std::cout<<recenica<<std::endl;
}

int main (){
    std::cout<<"Koliko zelite recenica: ";
    int brRecenica=0;
    std::cin>>brRecenica;
    std::cout<<"Unesite recenice:\n";
    try{
        char **matrica=KreirajMatricu(brRecenica);
        std::cout<<"Sortirane recenice:\n";
        for(int i=0; i<brRecenica; i++) IspisiRecenicu(matrica[i]);
        for(int i=0; i<brRecenica; i++) delete[] matrica[i];
        delete[] matrica;
    }
    catch(...){
        std::cout<<"Problemi s memorijom!\n";
    }
	return 0;
}