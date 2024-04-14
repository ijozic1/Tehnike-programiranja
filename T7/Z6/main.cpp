//TP 2022/2023: LV 7, Zadatak 6
#include <cmath>
#include <iostream>
#include <list>

template <typename Tip>
std::list<Tip> SortirajListu(std::list<Tip> &ulaznaLista) {
  std::list<Tip> sortiranaLista;
  for (auto it1=ulaznaLista.begin(); it1!=ulaznaLista.end(); it1++) {
    bool ubacen = false;
    for (auto it = sortiranaLista.begin(); it != sortiranaLista.end(); it++)
      if (*it1 < *it) {
        sortiranaLista.insert(it, *it1 );
        ubacen = true;
        break;
      }
    if (!ubacen)
      sortiranaLista.push_back(*it1 );
  }
  ulaznaLista=sortiranaLista;
  return sortiranaLista;
}

/*template <typename Tip>
std::list<Tip> SortirajListu(std::list<Tip> &ulaznaLista) {
  std::list<Tip> sortiranaLista;
  for (auto it1=ulaznaLista.begin(); it1!=ulaznaLista.end(); it1++) {
   auto it2 = sortiranaLista.begin();
    while(it2!=sortiranaLista.end() && *it2<*it1){
        it2++;
    }
    sortiranaLista.insert(it2, *it1);
  }
  ulaznaLista=sortiranaLista;
  return sortiranaLista;
}*/


int main() {
  std::cout << "Koliko ima elemenata: ";
  int brElemenata = 0;
  std::cin >> brElemenata;
  std::list<int> lista(brElemenata);
  std::cout << "Unesite elemente: ";
  for (int &x : lista) std::cin >> x;
  lista = SortirajListu(lista);
  std::cout << "Sortirana lista: ";
  for (int x : lista) std::cout << x << " ";

  return 0;
}
