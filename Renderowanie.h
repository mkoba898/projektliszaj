#ifndef RENDEROWANIE_H
#define RENDEROWANIE_H

#include "Siatka.h"
#include <SFML/Graphics.hpp>

class Renderowanie {
public:
    Renderowanie(int rozmiarOkna, int rozmiarSiatki);
    void rysuj(Siatka& siatka);
    sf::RenderWindow& pobierzOkno();

private:
    sf::RenderWindow okno;
    int rozmiarKom�rki;
};

#endif // RENDEROWANIE_H
