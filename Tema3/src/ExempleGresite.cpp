#include "ExempleGresite.hpp"

namespace cyberpunk {

int ContorHeap::blocuriActive = 0;

// --- ChipFaraDestructor ---
ChipFaraDestructor::ChipFaraDestructor(const std::string& nume, std::size_t capacitate)
    : nume_(nume), conexiuni_(new int[capacitate]) 
{
    ++ContorHeap::blocuriActive;
    std::cout << "  [!] ALOCARE GRESITA : " << nume_ << " la " << conexiuni_ 
              << "\n      -> ATENTIE: Fara Destructor, memoria ramane blocata!\n";
}

// --- ChipFaraCopyCtor ---
ChipFaraCopyCtor::ChipFaraCopyCtor(const std::string& nume, std::size_t capacitate)
    : nume_(nume), date_(new int[capacitate]{0}) 
{
    ++ContorHeap::blocuriActive;
    std::cout << "  [!] ALOCARE GRESITA : " << nume_ << " la " << date_ << "\n";
}

ChipFaraCopyCtor::~ChipFaraCopyCtor() 
{
    std::cout << "  [X] ELIBERARE       : " << nume_ << " (stergem " << date_ << ")\n";
    delete[] date_;
    --ContorHeap::blocuriActive;
}

void ChipFaraCopyCtor::modificaData(int index, int valoare) {
    date_[index] = valoare;
}

void ChipFaraCopyCtor::afiseaza(const char* eticheta) const {
    std::cout << "      " << eticheta << " [" << nume_ << "] Valoare: " << date_[0] << " | Memorie: " << date_ << "\n";
}

} // namespace cyberpunk