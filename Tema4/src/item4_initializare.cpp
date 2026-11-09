#include "item4_initializare.hpp"
#include <iostream>

Motor::Motor() : putere_propulsie(0) {}
Motor::Motor(int putere) : putere_propulsie(putere) {}
void Motor::afisare() const { std::cout << "Putere motor: " << putere_propulsie; }


NavaSpatiala::NavaSpatiala(const std::string& nume, int viteza, int putere)
    : nume_nava(nume), viteza_maxima(viteza), motor_principal(putere) {
}

void NavaSpatiala::afisare() const {
    std::cout << "Nava: " << nume_nava << " | Viteza: " << viteza_maxima << " | ";
    motor_principal.afisare();
    std::cout << "\n";
}
