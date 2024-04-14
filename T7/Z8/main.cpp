//TP 2022/2023: LV 7, Zadatak 8
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

std::string IzvrniBezRazmaka(const std::string &pocetni){
    std::string izvrnuti(pocetni.length(),' ');
    std::remove_copy(pocetni.rbegin(), pocetni.rend(), izvrnuti.begin(), ' ');
    return izvrnuti;
}

int main (){
    std::cout << IzvrniBezRazmaka("Evo pada kisa") << std::endl;
  	std::cout << IzvrniBezRazmaka("I jogurt ujutru goji ....") << std::endl;
  	std::cout << IzvrniBezRazmaka("  udovica  baci   vodu") << std::endl;
	return 0;
}
