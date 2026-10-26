#ifndef EXEMPLE_GRESITE_HPP
#define EXEMPLE_GRESITE_HPP

#include <string>
#include <iostream>

namespace cyberpunk {

// Contor global pentru a monitoriza alocarile pe heap
struct ContorHeap {
    static int blocuriActive;
};

// 1. Clasa fara destructor (Demonstreaza Memory Leak)
class ChipFaraDestructor {
private:
    std::string nume_;
    int* conexiuni_;
public:
    ChipFaraDestructor(const std::string& nume, std::size_t capacitate);
    // LUPSESTE DESTRUCTORUL! Nu vom da delete[] niciodata
};

// 2. Clasa fara Copy Constructor (Demonstreaza Shallow Copy)
class ChipFaraCopyCtor {
public:
    std::string nume_;
    int* date_;
    
    ChipFaraCopyCtor(const std::string& nume, std::size_t capacitate);
    ~ChipFaraCopyCtor();
    // LIPSESTE COPY CONSTRUCTORUL!
    
    void modificaData(int index, int valoare);
    void afiseaza(const char* eticheta) const;
};

} // namespace cyberpunk

#endif