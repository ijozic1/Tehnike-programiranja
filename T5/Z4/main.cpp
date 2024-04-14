//TP 2022/2023: LV 5, Zadatak 4
#include <algorithm>
#include <cmath>
#include <iostream>
#include <deque>

int main() {
    std::cout << "Unesite broj elemenata: ";
    int velicina=0;
    std::cin>>velicina;
    std::deque<int>elementi;
    elementi.resize(velicina);
    std::cout << "Unesite elemente: ";
    std::for_each(elementi.begin(), elementi.end(), [](int &clan){ std::cin >> clan;});
    std::cout << "Najveci element deka je "<< *(std::max_element(elementi.begin(), elementi.end())) <<" "<<std::endl;
    std::cout << "Najmanji element deka se pojavljuje "<< std::count(elementi.begin(), elementi.end(),*(std::min_element(elementi.begin(), elementi.end())))<< " puta u deku" << std::endl;
    std::cout << "U deku ima "<< std::count_if(elementi.begin(), elementi.end(), [](int clan) {
                    if (std::sqrt(clan) == static_cast<int>(std::sqrt(clan))) return true;
                    return false;})<< " brojeva koji su potpuni kvadrati" << std::endl;
    std::deque<int> cifre;
    cifre.resize(velicina);
    std::transform(elementi.begin(), elementi.end(), cifre.begin(), [](int clan){
            if (clan < 0) clan *= (-1);
            if (clan == 0) return 1;
            return int(std::floor(log10(clan)) + 1);});
    int p=std::min_element(cifre.begin(), cifre.end())-cifre.begin();
    std::cout << "Prvi element sa najmanjim brojem cifara je "<< elementi[p]<< std::endl;
    std::deque<int>::iterator kraj=std::remove_if(elementi.begin(), elementi.end(), [](int broj) {
            if (!(broj <= -100 && broj >= -999 || broj >= 100 && broj <= 999)) return false;
            return true;});
    std::cout << "Elementi koji nisu trocifreni su: ";
    std::for_each(elementi.begin(), kraj, [](int m){std::cout<<m<<" ";});
    std::cout<<std::endl; 
    return 0;
}