#ifndef ITEM6_INTERZICERE_HPP
#define ITEM6_INTERZICERE_HPP
#include <string>

class ReactorNuclear {
public:
    ReactorNuclear(const std::string& id);
    ~ReactorNuclear();

    void afisare() const;

    // Item 6: Interzicem explicit functiile de care nu avem nevoie
    // (un reactor nu trebuie niciodata copiat).
    ReactorNuclear(const ReactorNuclear&) = delete;
    ReactorNuclear& operator=(const ReactorNuclear&) = delete;

private:
    std::string reactor_id;
};
#endif // ITEM6_INTERZICERE_HPP
