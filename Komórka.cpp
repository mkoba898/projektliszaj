#include "Komórka.h"
#include <cstdlib> // Do losowania liczb

int Komórka::czasOdpornoœci = 4; // Domyœlny czas odpornoœci (4 jednostki czasu)

Komórka::Komórka() : stan(Stan::Zdrowa), licznik(0) {}

Stan Komórka::pobierzStan() const {
    return stan;
}

void Komórka::ustawStan(Stan nowyStan) {
    stan = nowyStan;
    licznik = 0; // Resetujemy licznik przy zmianie stanu
}

void Komórka::ustawCzasOdpornoœci(int czas) {
    czasOdpornoœci = czas; // Ustawia globalny czas odpornoœci
}

void Komórka::aktualizuj() {
    if (stan == Stan::Zara¿ona) {
        licznik++;

        // 5% szans na "œmieræ" komórki
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
        if (licznik >= czasOdpornoœci) { // Czas odpornoœci ustawiony przez u¿ytkownika
            stan = Stan::Zdrowa;
            licznik = 0;
        }
    }
}
