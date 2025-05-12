#include "Siatka.h"
#include <random> // Do losowania

using namespace std;

Siatka::Siatka(int rozmiarSiatki) : rozmiar(rozmiarSiatki) {
    // Inicjalizacja siatki komórek
    komórki.resize(rozmiar, vector<Komórka>(rozmiar));
}

int Siatka::pobierzRozmiar() const {
    return rozmiar;
}

Komórka& Siatka::pobierzKomórkê(int x, int y) {
    return komórki[x][y];
}

void Siatka::zarazS¹siadów() {
    // Tworzymy kopiê siatki, aby zmiany by³y niezale¿ne od bie¿¹cej iteracji
    auto nowaSiatka = komórki;

    // Generator losowy
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            if (komórki[i][j].pobierzStan() == Stan::Zara¿ona) {
                // Zara¿anie s¹siadów z 50% szans¹
                if (i > 0 && komórki[i - 1][j].pobierzStan() == Stan::Zdrowa && dist(gen) <= 50) {
                    nowaSiatka[i - 1][j].ustawStan(Stan::Zara¿ona);
                }
                if (i < rozmiar - 1 && komórki[i + 1][j].pobierzStan() == Stan::Zdrowa && dist(gen) <= 50) {
                    nowaSiatka[i + 1][j].ustawStan(Stan::Zara¿ona);
                }
                if (j > 0 && komórki[i][j - 1].pobierzStan() == Stan::Zdrowa && dist(gen) <= 50) {
                    nowaSiatka[i][j - 1].ustawStan(Stan::Zara¿ona);
                }
                if (j < rozmiar - 1 && komórki[i][j + 1].pobierzStan() == Stan::Zdrowa && dist(gen) <= 50) {
                    nowaSiatka[i][j + 1].ustawStan(Stan::Zara¿ona);
                }
            }
        }
    }

    // Aktualizujemy siatkê
    komórki = nowaSiatka;
}

void Siatka::aktualizuj() {
    // Aktualizacja stanu ka¿dej komórki w siatce
    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            komórki[i][j].aktualizuj();
        }
    }
}
