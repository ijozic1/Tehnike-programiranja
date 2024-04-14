//TP 2022/2023: LV 7, Zadatak 2
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>

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
        std::sort(matrica, matrica+brRecenica,[](char*a, char*b){return(std::strcmp(a,b)<0);});
        /*[](char *a, char *b){
            while (*a != '\n' && *b != '\n' && *a == *b) {
                a++; b++;
            }
            if (*a != '\n' && *b != '\n') return *a < *b;
            if (*a == '\n' && *b != '\n') return true;
            if (*a != '\n' && *b == '\n') return false;
            return false;
        });*/
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
