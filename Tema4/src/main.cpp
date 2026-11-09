#include <iostream>
#include "item4_initializare.hpp"
#include "item5_functii_generate.hpp"
#include "item6_interzicere.hpp"

int main() {
    std::cout << "--- Item 4: Make sure that objects are initialized before they're used ---\n";
    NavaSpatiala nava("Milano", 15000, 850);
    nava.afisare();

    std::cout << "\n--- Item 5: Know what functions C++ silently writes and calls ---\n";
    BazaSpatiala baza1;
    baza1.locatie = "Jupiter";
    baza1.capacitate_nave = 50;

    BazaSpatiala baza2 = baza1; // Apeleaza copy constructorul generat automat de C++
    std::cout << "Baza 1: "; baza1.afisare();
    std::cout << "Baza 2 (copiata din Baza 1): "; baza2.afisare();

    std::cout << "\n--- Item 6: Explicitly disallow compiler-generated functions ---\n";
    ReactorNuclear reactor("R-001");
    reactor.afisare();
    
    // Decomentarea liniilor urmatoare va da eroare de compilare, exact comportamentul 
    // dorit conform Item 6 pentru a preveni copierea resurselor unice:
    // ReactorNuclear copie_reactor = reactor;
    // ReactorNuclear alt_reactor("R-002");
    // alt_reactor = reactor;

    std::cout << "\nToate testele au trecut cu succes.\n";
    return 0;
}
