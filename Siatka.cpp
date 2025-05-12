#include "Siatka.h"
#include <random> // Do losowania

using namespace std;

Siatka::Siatka(int rozmiarSiatki) : rozmiar(rozmiarSiatki) {
    // Inicjalizacja siatki kom�rek
    kom�rki.resize(rozmiar, vector<Kom�rka>(rozmiar));
}

int Siatka::pobierzRozmiar() const {
    return rozmiar;
}

Kom�rka& Siatka::pobierzKom�rk�(int x, int y) {
    return kom�rki[x][y];
}

void Siatka::zarazS�siad�w() {
    // Tworzymy kopi� siatki, aby zmiany by�y niezale�ne od bie��cej iteracji
    auto nowaSiatka = kom�rki;

    // Generator losowy
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            if (kom�rki[i][j].pobierzStan() == Stan::Zara�ona) {
                // Zara�anie s�siad�w z 50% szans�
                if (i > 0 && kom�rki[i - 1][j].pobierzStan() == Stan::Zdrowa && dist(gen) <= 50) {
                    nowaSiatka[i - 1][j].ustawStan(Stan::Zara�ona);
                }
                if (i < rozmiar - 1 && kom�rki[i + 1][j].pobierzStan() == Stan::Zdrowa && dist(gen) <= 50) {
                    nowaSiatka[i + 1][j].ustawStan(Stan::Zara�ona);
                }
                if (j > 0 && kom�rki[i][j - 1].pobierzStan() == Stan::Zdrowa && dist(gen) <= 50) {
                    nowaSiatka[i][j - 1].ustawStan(Stan::Zara�ona);
                }
                if (j < rozmiar - 1 && kom�rki[i][j + 1].pobierzStan() == Stan::Zdrowa && dist(gen) <= 50) {
                    nowaSiatka[i][j + 1].ustawStan(Stan::Zara�ona);
                }
            }
        }
    }

    // Aktualizujemy siatk�
    kom�rki = nowaSiatka;
}

void Siatka::aktualizuj() {
    // Aktualizacja stanu ka�dej kom�rki w siatce
    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            kom�rki[i][j].aktualizuj();
        }
    }
}
