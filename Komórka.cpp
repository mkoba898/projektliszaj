#include "Kom�rka.h"
#include <cstdlib> // Do losowania liczb

int Kom�rka::czasOdporno�ci = 4; // Domy�lny czas odporno�ci (4 jednostki czasu)

Kom�rka::Kom�rka() : stan(Stan::Zdrowa), licznik(0) {}

Stan Kom�rka::pobierzStan() const {
    return stan;
}

void Kom�rka::ustawStan(Stan nowyStan) {
    stan = nowyStan;
    licznik = 0; // Resetujemy licznik przy zmianie stanu
}

void Kom�rka::ustawCzasOdporno�ci(int czas) {
    czasOdporno�ci = czas; // Ustawia globalny czas odporno�ci
}

void Kom�rka::aktualizuj() {
    if (stan == Stan::Zara�ona) {
        licznik++;

        // 5% szans na "�mier�" kom�rki
        if (rand() % 20 == 0) {
            stan = Stan::Martwa;
            licznik = 0;
        }
        else if (licznik >= 6) { // Po 6 jednostkach czasu przechodzi w stan Odporna
            stan = Stan::Odporna;
            licznik = 0;
        }
    }
    else if (stan == Stan::Odporna) {
        licznik++;
        if (licznik >= czasOdporno�ci) { // Czas odporno�ci ustawiony przez u�ytkownika
            stan = Stan::Zdrowa;
            licznik = 0;
        }
    }
}
