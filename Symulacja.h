#ifndef SYMULACJA_H
#define SYMULACJA_H

#include "Siatka.h"
#include <map> // Do przechowywania statystyk

class Symulacja {
public:
    Symulacja(int rozmiarSiatki);
    Siatka& pobierzSiatkê();
    void uruchom();
    bool czyNast¹pi³aZmiana(); // Sprawdzenie, czy stan siatki siê zmieni³
    std::map<Stan, int> obliczStatystyki(); // Obliczanie statystyk

private:
    Siatka siatka;
    Siatka poprzedniaSiatka; // Przechowuje stan siatki sprzed ostatniej iteracji
    int czas;
};

#endif // SYMULACJA_H
