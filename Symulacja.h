#ifndef SYMULACJA_H
#define SYMULACJA_H

#include "Siatka.h"
#include <map> // Do przechowywania statystyk

class Symulacja {
public:
    Symulacja(int rozmiarSiatki);
    Siatka& pobierzSiatk�();
    void uruchom();
    bool czyNast�pi�aZmiana(); // Sprawdzenie, czy stan siatki si� zmieni�
    std::map<Stan, int> obliczStatystyki(); // Obliczanie statystyk

private:
    Siatka siatka;
    Siatka poprzedniaSiatka; // Przechowuje stan siatki sprzed ostatniej iteracji
    int czas;
};

#endif // SYMULACJA_H
