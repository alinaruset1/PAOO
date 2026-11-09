#ifndef ITEM4_INITIALIZARE_HPP
#define ITEM4_INITIALIZARE_HPP
#include <string>

class Motor {
public:
    Motor();
    Motor(int putere);
    void afisare() const;
private:
    int putere_propulsie;
};

class NavaSpatiala {
public:
    // Item 4: Constructori cu lista de initializare
    NavaSpatiala(const std::string& nume, int viteza, int putere);
    void afisare() const;
private:
    std::string nume_nava;
    int viteza_maxima;
    Motor motor_principal;
};
#endif // ITEM4_INITIALIZARE_HPP
