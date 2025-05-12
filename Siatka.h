#ifndef SIATKA_H
#define SIATKA_H

#include "Komórka.h"
#include <vector>
using namespace std;
class Siatka {
public:
    Siatka(int rozmiar);
    void aktualizuj();
    void zarazS¹siadów(); // iteruje po ca³ej siatce
    Komórka& pobierzKomórkê(int x, int y);
    int pobierzRozmiar() const;

private:
    vector<vector<Komórka>> komórki;
    int rozmiar;
};

#endif // SIATKA_H
