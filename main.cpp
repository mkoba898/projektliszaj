#include "Symulacja.h"
#include "Renderowanie.h"
#include "Komórka.h"
#include <SFML/Window.hpp>
#include <iostream>
#include <thread>
#include <map>

using namespace std;

// Prototypy funkcji
int wybierzRozmiarTablicy();
int wybierzCzasJednostki();
bool czekajNaStart(sf::RenderWindow& okno);
void wypiszStatystyki(const map<Stan, int>& statystyki);
int wybierzCzasOdporności();

int wybierzRozmiarTablicy() {
    int rozmiar;
    while (true) {
        cout << "Podaj rozmiar tablicy nxn (tylko liczby nieparzyste): ";
        cin >> rozmiar;

        if (rozmiar > 0 && rozmiar % 2 == 1) {
            return rozmiar;
        }

        cout << "Nieprawidlowy rozmiar. Wprowadz liczbe nieparzysta wieksza od zera." << endl;
    }
}

int wybierzCzasJednostki() {
    int czas;
    while (true) {
        cout << "Podaj czas trwania jednej jednostki czasu (w milisekundach): ";
        cin >> czas;

        if (czas > 0) {
            return czas;
        }

        cout << "Nieprawidlowy czas. Wprowadz liczbe wieksza od zera." << endl;
    }
}

bool czekajNaStart(sf::RenderWindow& okno) {
    cout << "Aby wystartowac symulacje, nacisnij dowolny klawisz..." << endl;

    while (okno.isOpen()) {
        sf::Event wydarzenie;
        while (okno.pollEvent(wydarzenie)) {
            if (wydarzenie.type == sf::Event::Closed)
                okno.close();
            if (wydarzenie.type == sf::Event::KeyPressed)
                return true;
        }
    }
    return false;
}

void wypiszStatystyki(const map<Stan, int>& statystyki) {
    cout << "Statystyki:" << endl;
    cout << "Zdrowe: " << statystyki.at(Stan::Zdrowa) << endl;
    cout << "Zarażone: " << statystyki.at(Stan::Zarażona) << endl;
    cout << "Odporne: " << statystyki.at(Stan::Odporna) << endl;
    cout << "Martwe: " << statystyki.at(Stan::Martwa) << endl;
    cout << "-----------------------" << endl;
}

int wybierzCzasOdporności() {
    int czas;
    while (true) {
        cout << "Podaj czas trwania odporności (w jednostkach czasu): ";
        cin >> czas;

        if (czas > 0) {
            return czas;
        }

        cout << "Nieprawidlowy czas. Wprowadz liczbe wieksza od zera." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Polish");
    // Wybor rozmiaru tablicy
    int rozmiarSiatki = wybierzRozmiarTablicy();

    // Wybor czasu jednostki czasu
    int czasJednostki = wybierzCzasJednostki();

    // Wybor czasu odporności
    int czasOdporności = wybierzCzasOdporności();
    Komórka::ustawCzasOdporności(czasOdporności); // Przekazanie wartości do klasy Komórka

    const int rozmiarOkna = 500;
    const int maksBezZmian = 10; // Liczba jednostek czasu bez zmian, po której kończymy symulację

    Symulacja symulacja(rozmiarSiatki);
    Renderowanie renderowanie(rozmiarOkna, rozmiarSiatki);

    renderowanie.rysuj(symulacja.pobierzSiatkę());

    if (!czekajNaStart(renderowanie.pobierzOkno())) {
        return 0; // Zakończenie programu, jeśli okno zostanie zamknięte
    }

    int bezZmian = 0; // Licznik jednostek czasu bez zmian

    bool symulacjaTrwa = true; // Flaga określająca, czy symulacja ma działać

    while (renderowanie.pobierzOkno().isOpen()) {
        sf::Event wydarzenie;
        while (renderowanie.pobierzOkno().pollEvent(wydarzenie)) {
            if (wydarzenie.type == sf::Event::Closed) {
                renderowanie.pobierzOkno().close();
                return 0;
            }
        }

        if (symulacjaTrwa) {
            // Symulacja i renderowanie
            symulacja.uruchom();
            renderowanie.rysuj(symulacja.pobierzSiatkę());

            // Wyświetlenie statystyk
            auto statystyki = symulacja.obliczStatystyki();
            wypiszStatystyki(statystyki);

            // Sprawdzenie, czy nastąpiły zmiany
            if (!symulacja.czyNastąpiłaZmiana()) {
                bezZmian++;
            }
            else {
                bezZmian = 0; // Reset licznika, jeśli nastąpiły zmiany
            }

            // Zatrzymanie symulacji po maksBezZmian jednostkach czasu bez zmian
            if (bezZmian >= maksBezZmian) {
                cout << "Symulacja została zatrzymana: brak zmian przez " << maksBezZmian << " jednostek czasu." << endl;
                symulacjaTrwa = false; // Zatrzymanie symulacji
            }

            // Opóźnienie w milisekundach
            this_thread::sleep_for(chrono::milliseconds(czasJednostki));
        }
        else {
            // Jeśli symulacja się zatrzymała, nadal renderujemy siatkę w ostatnim stanie
            renderowanie.rysuj(symulacja.pobierzSiatkę());
        }
    }



    return 0;
}
