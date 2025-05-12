#ifndef KOMORKA_H
#define KOMORKA_H

enum class Stan {
    Zdrowa,
    Zara�ona,
    Odporna,
    Martwa
};

class Kom�rka {
public:
    Kom�rka();

    Stan pobierzStan() const;
    void ustawStan(Stan stan);
    void aktualizuj(); // Logika zmiany stanu w czasie

    static void ustawCzasOdporno�ci(int czas); // Ustawia czas odporno�ci globalnie

private:
    Stan stan;
    int licznik; // Licznik dla stanu Zara�ona lub Odporna
    static int czasOdporno�ci; // Statyczna zmienna dla czasu odporno�ci
};

#endif // KOMORKA_H
