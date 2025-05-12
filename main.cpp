#include "Symulacja.h"
#include "Renderowanie.h"
#include "Kom�rka.h"
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
int wybierzCzasOdporno�ci();

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
    cout << "Zara�one: " << statystyki.at(Stan::Zara�ona) << endl;
    cout << "Odporne: " << statystyki.at(Stan::Odporna) << endl;
    cout << "Martwe: " << statystyki.at(Stan::Martwa) << endl;
    cout << "-----------------------" << endl;
}

int wybierzCzasOdporno�ci() {
    int czas;
    while (true) {
        cout << "Podaj czas trwania odporno�ci (w jednostkach czasu): ";
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

    // Wybor czasu odporno�ci
    int czasOdporno�ci = wybierzCzasOdporno�ci();
    Kom�rka::ustawCzasOdporno�ci(czasOdporno�ci); // Przekazanie warto�ci do klasy Kom�rka

    const int rozmiarOkna = 500;
    const int maksBezZmian = 10; // Liczba jednostek czasu bez zmian, po kt�rej ko�czymy symulacj�

    Symulacja symulacja(rozmiarSiatki);
    Renderowanie renderowanie(rozmiarOkna, rozmiarSiatki);

    renderowanie.rysuj(symulacja.pobierzSiatk�());

    if (!czekajNaStart(renderowanie.pobierzOkno())) {
        return 0; // Zako�czenie programu, je�li okno zostanie zamkni�te
    }

    int bezZmian = 0; // Licznik jednostek czasu bez zmian

    bool symulacjaTrwa = true; // Flaga okre�laj�ca, czy symulacja ma dzia�a�

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
            renderowanie.rysuj(symulacja.pobierzSiatk�());

            // Wy�wietlenie statystyk
            auto statystyki = symulacja.obliczStatystyki();
            wypiszStatystyki(statystyki);

            // Sprawdzenie, czy nast�pi�y zmiany
            if (!symulacja.czyNast�pi�aZmiana()) {
                bezZmian++;
            }
            else {
                bezZmian = 0; // Reset licznika, je�li nast�pi�y zmiany
            }

            // Zatrzymanie symulacji po maksBezZmian jednostkach czasu bez zmian
            if (bezZmian >= maksBezZmian) {
                cout << "Symulacja zosta�a zatrzymana: brak zmian przez " << maksBezZmian << " jednostek czasu." << endl;
                symulacjaTrwa = false; // Zatrzymanie symulacji
            }

            // Op�nienie w milisekundach
            this_thread::sleep_for(chrono::milliseconds(czasJednostki));
        }
        else {
            // Je�li symulacja si� zatrzyma�a, nadal renderujemy siatk� w ostatnim stanie
            renderowanie.rysuj(symulacja.pobierzSiatk�());
        }
    }



    return 0;
}
