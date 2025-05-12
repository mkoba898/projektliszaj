#include "Symulacja.h"
#include <iostream>
using namespace std;
Symulacja::Symulacja(int rozmiarSiatki) : siatka(rozmiarSiatki), poprzedniaSiatka(rozmiarSiatki), czas(0) {
    siatka.pobierzKomórkê(rozmiarSiatki / 2, rozmiarSiatki / 2).ustawStan(Stan::Zara¿ona);
}

Siatka& Symulacja::pobierzSiatkê() {
    return siatka;
}

void Symulacja::uruchom() {
    poprzedniaSiatka = siatka; // Zapisujemy stan siatki przed aktualizacj¹

    // Zara¿anie s¹siadów
    siatka.zarazS¹siadów();

    // Aktualizacja stanów komórek
    siatka.aktualizuj();

    // Inkrementacja czasu
    czas++;
}

bool Symulacja::czyNast¹pi³aZmiana() {
    for (int i = 0; i < siatka.pobierzRozmiar(); ++i) {
        for (int j = 0; j < siatka.pobierzRozmiar(); ++j) {
            if (siatka.pobierzKomórkê(i, j).pobierzStan() != poprzedniaSiatka.pobierzKomórkê(i, j).pobierzStan()) {
                return true; // Wykryto zmianê
            }
        }
    }
    return false; // Brak zmian
}

map<Stan, int> Symulacja::obliczStatystyki() {
    map<Stan, int> statystyki = {
        {Stan::Zdrowa, 0},
        {Stan::Zara¿ona, 0},
        {Stan::Odporna, 0},
        {Stan::Martwa, 0}
    };

    for (int i = 0; i < siatka.pobierzRozmiar(); ++i) {
        for (int j = 0; j < siatka.pobierzRozmiar(); ++j) {
            statystyki[siatka.pobierzKomórkê(i, j).pobierzStan()]++;
        }
    }

    return statystyki;
}
