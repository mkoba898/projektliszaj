#ifndef KOMORKA_H
#define KOMORKA_H

enum class Stan {
    Zdrowa,
    Zara¿ona,
    Odporna,
    Martwa
};

class Komórka {
public:
    Komórka();

    Stan pobierzStan() const;
    void ustawStan(Stan stan);
    void aktualizuj(); // Logika zmiany stanu w czasie

    static void ustawCzasOdpornoœci(int czas); // Ustawia czas odpornoœci globalnie

private:
    Stan stan;
    int licznik; // Licznik dla stanu Zara¿ona lub Odporna
    static int czasOdpornoœci; // Statyczna zmienna dla czasu odpornoœci
};

#endif // KOMORKA_H
