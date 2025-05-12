#include "Symulacja.h"
#include <iostream>
using namespace std;
Symulacja::Symulacja(int rozmiarSiatki) : siatka(rozmiarSiatki), poprzedniaSiatka(rozmiarSiatki), czas(0) {
    siatka.pobierzKom�rk�(rozmiarSiatki / 2, rozmiarSiatki / 2).ustawStan(Stan::Zara�ona);
}

Siatka& Symulacja::pobierzSiatk�() {
    return siatka;
}

void Symulacja::uruchom() {
    poprzedniaSiatka = siatka; // Zapisujemy stan siatki przed aktualizacj�

    // Zara�anie s�siad�w
    siatka.zarazS�siad�w();

    // Aktualizacja stan�w kom�rek
    siatka.aktualizuj();

    // Inkrementacja czasu
    czas++;
}

bool Symulacja::czyNast�pi�aZmiana() {
    for (int i = 0; i < siatka.pobierzRozmiar(); ++i) {
        for (int j = 0; j < siatka.pobierzRozmiar(); ++j) {
            if (siatka.pobierzKom�rk�(i, j).pobierzStan() != poprzedniaSiatka.pobierzKom�rk�(i, j).pobierzStan()) {
                return true; // Wykryto zmian�
            }
        }
    }
    return false; // Brak zmian
}

map<Stan, int> Symulacja::obliczStatystyki() {
    map<Stan, int> statystyki = {
        {Stan::Zdrowa, 0},
        {Stan::Zara�ona, 0},
        {Stan::Odporna, 0},
        {Stan::Martwa, 0}
    };

    for (int i = 0; i < siatka.pobierzRozmiar(); ++i) {
        for (int j = 0; j < siatka.pobierzRozmiar(); ++j) {
            statystyki[siatka.pobierzKom�rk�(i, j).pobierzStan()]++;
        }
    }

    return statystyki;
}
