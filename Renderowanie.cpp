#include "Renderowanie.h"

Renderowanie::Renderowanie(int rozmiarOkna, int rozmiarSiatki)
    : okno(sf::VideoMode(rozmiarOkna, rozmiarOkna), "Symulacja Liszaja", sf::Style::Default),
    rozmiarKomórki(rozmiarOkna / rozmiarSiatki) {}

void Renderowanie::rysuj(Siatka& siatka) {
    okno.clear(sf::Color::Black); // Tło okna na czarne

    for (int i = 0; i < siatka.pobierzRozmiar(); ++i) {
        for (int j = 0; j < siatka.pobierzRozmiar(); ++j) {
            // Tworzymy kwadrat komórki
            sf::RectangleShape kwadrat(sf::Vector2f(
                static_cast<float>(rozmiarKomórki - 1), // Zmniejszamy o 1 dla linii
                static_cast<float>(rozmiarKomórki - 1)
            ));

            kwadrat.setPosition(
                static_cast<float>(i * rozmiarKomórki),
                static_cast<float>(j * rozmiarKomórki)
            );

            // Ustawiamy kolor komórki w zależności od jej stanu
            if (siatka.pobierzKomórkę(i, j).pobierzStan() == Stan::Zdrowa) {
                kwadrat.setFillColor(sf::Color::Green);
            }
            else if (siatka.pobierzKomórkę(i, j).pobierzStan() == Stan::Zarażona) {
                kwadrat.setFillColor(sf::Color::Red);
            }
            else if (siatka.pobierzKomórkę(i, j).pobierzStan() == Stan::Odporna) {
                kwadrat.setFillColor(sf::Color::Blue);
            }
            else if (siatka.pobierzKomórkę(i, j).pobierzStan() == Stan::Martwa) {
                kwadrat.setFillColor(sf::Color::Black);
            }

            // Dodajemy biały kontur do każdej komórki+
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
