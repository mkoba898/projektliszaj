#ifndef SIATKA_H
#define SIATKA_H

#include "Kom�rka.h"
#include <vector>
using namespace std;
class Siatka {
public:
    Siatka(int rozmiar);
    void aktualizuj();
    void zarazS�siad�w(); // iteruje po ca�ej siatce
    Kom�rka& pobierzKom�rk�(int x, int y);
    int pobierzRozmiar() const;

private:
    vector<vector<Kom�rka>> kom�rki;
    int rozmiar;
};

#endif // SIATKA_H
