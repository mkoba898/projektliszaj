#include "Renderowanie.h"

Renderowanie::Renderowanie(int rozmiarOkna, int rozmiarSiatki)
    : okno(sf::VideoMode(rozmiarOkna, rozmiarOkna), "Symulacja Liszaja", sf::Style::Default),
    rozmiarKom�rki(rozmiarOkna / rozmiarSiatki) {}

void Renderowanie::rysuj(Siatka& siatka) {
    okno.clear(sf::Color::Black); // T�o okna na czarne

    for (int i = 0; i < siatka.pobierzRozmiar(); ++i) {
        for (int j = 0; j < siatka.pobierzRozmiar(); ++j) {
            // Tworzymy kwadrat kom�rki
            sf::RectangleShape kwadrat(sf::Vector2f(
                static_cast<float>(rozmiarKom�rki - 1), // Zmniejszamy o 1 dla linii
                static_cast<float>(rozmiarKom�rki - 1)
            ));

            kwadrat.setPosition(
                static_cast<float>(i * rozmiarKom�rki),
                static_cast<float>(j * rozmiarKom�rki)
            );

            // Ustawiamy kolor kom�rki w zale�no�ci od jej stanu
            if (siatka.pobierzKom�rk�(i, j).pobierzStan() == Stan::Zdrowa) {
                kwadrat.setFillColor(sf::Color::Green);
            }
            else if (siatka.pobierzKom�rk�(i, j).pobierzStan() == Stan::Zara�ona) {
                kwadrat.setFillColor(sf::Color::Red);
            }
            else if (siatka.pobierzKom�rk�(i, j).pobierzStan() == Stan::Odporna) {
                kwadrat.setFillColor(sf::Color::Blue);
            }
            else if (siatka.pobierzKom�rk�(i, j).pobierzStan() == Stan::Martwa) {
                kwadrat.setFillColor(sf::Color::Black);
            }

            // Dodajemy bia�y kontur do ka�dej kom�rki+
            kwadrat.setOutlineColor(sf::Color::White);
            kwadrat.setOutlineThickness(1);

            okno.draw(kwadrat);
        }
    }

    okno.display();
}

sf::RenderWindow& Renderowanie::pobierzOkno() {
    return okno;
}
