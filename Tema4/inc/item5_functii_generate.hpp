#ifndef ITEM5_FUNCTII_GENERATE_HPP
#define ITEM5_FUNCTII_GENERATE_HPP
#include <string>

// Item 5: Compilatorul genereaza tacit constructori, destructori si operatori de copiere/asignare.
class BazaSpatiala {
public:
    std::string locatie = "Orbita Terestra";
    int capacitate_nave = 10;

    void afisare() const;
};
#endif // ITEM5_FUNCTII_GENERATE_HPP
