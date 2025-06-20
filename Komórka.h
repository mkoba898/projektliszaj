#ifndef KOMORKA_H
#define KOMORKA_H

enum class Stan {
    Zdrowa,
    Zarażona,
    Odporna,
    Martwa
};

class Komórka {
public:
    Komórka();

    Stan pobierzStan() const;
    void ustawStan(Stan stan);
    void aktualizuj(); // Logika zmiany stanu w czasie

    static void ustawCzasOdporności(int czas); // Ustawia czas odporności globalnie

private:
    Stan stan;
    int licznik; // Licznik dla stanu Zarażona lub Odporna
    static int czasOdporności; // Statyczna zmienna dla czasu odporności
};

#endif // KOMORKA_H
