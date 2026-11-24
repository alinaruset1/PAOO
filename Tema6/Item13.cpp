#include "Item13.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>

// ---------------- Investment ----------------
int Investment::alive = 0;

Investment::Investment(std::string name) : name_(std::move(name)) { ++alive; }
Investment::~Investment() { --alive; }
const std::string& Investment::name() const { return name_; }

Stock::Stock(std::string name) : Investment(std::move(name)) {}
double Stock::value() const { return 150.5; }

Bond::Bond(std::string name) : Investment(std::move(name)) {}
double Bond::value() const { return 1000.0; }

Investment* createInvestmentRaw(const std::string& kind) {
    if (kind == "bond") return new Bond("Obligatiune");
    return new Stock("Actiune");
}

std::unique_ptr<Investment> createInvestment(const std::string& kind) {
    if (kind == "bond") return std::make_unique<Bond>("Obligatiune");
    return std::make_unique<Stock>("Actiune");
}

double legacyValue(const Investment* pi) { return pi->value(); }


namespace {

void riskyRaw(bool fail, Investment** spy) {
    Investment* p = createInvestmentRaw("stock");
    *spy = p;
    if (fail) throw std::runtime_error("eroare in timpul folosirii");
    delete p;  // nu se mai ajunge aici cand fail == true
}

// CORECT: unique_ptr elibereaza resursa in destructor, orice s-ar intampla.
void safeUnique(bool fail) {
    std::unique_ptr<Investment> p = createInvestment("stock");
    if (fail) throw std::runtime_error("eroare in timpul folosirii");
    // fara delete: destructorul lui p se ocupa
}

}  // namespace

void demoItem13() {
    std::cout << "=== Item 13: obiecte care gestioneaza resurse (RAII) ===\n";

    // 1) Gestionare manuala: scurgere
    Investment* leaked = nullptr;
    try {
        riskyRaw(true, &leaked);
    } catch (const std::exception& e) {
        std::cout << "[raw]    exceptie: " << e.what() << "\n";
    }
    std::cout << "[raw]    obiecte in viata dupa exceptie: " << Investment::alive
              << "   <-- SCURGERE!\n";
    delete leaked;  // curatam manual doar ca sa nu ramana scurgerea reala
    std::cout << "[raw]    dupa curatarea manuala: " << Investment::alive << "\n";

    // 2) unique_ptr: fara scurgere
    try {
        safeUnique(true);
    } catch (const std::exception& e) {
        std::cout << "[unique] exceptie: " << e.what() << "\n";
    }
    std::cout << "[unique] obiecte in viata dupa exceptie: " << Investment::alive
              << "   <-- fara scurgere\n";

    // 3) unique_ptr: proprietate exclusiva => nu se copiaza, doar se muta
    {
        std::unique_ptr<Investment> a = createInvestment("bond");
        // std::unique_ptr<Investment> b = a;   // EROARE DE COMPILARE: copiere interzisa
        std::unique_ptr<Investment> b = std::move(a);  // transfer de proprietate
        std::cout << "[unique] dupa move: a este " << (a ? "valid" : "nullptr")
                  << ", b=" << b->name() << "\n";

        // acces la resursa bruta pentru API-uri vechi
        std::cout << "[unique] legacyValue(b.get()) = " << legacyValue(b.get())
                  << ", (*b).value() = " << (*b).value() << "\n";
    }
    std::cout << "[unique] dupa iesirea din scope: " << Investment::alive << "\n";

    // 4) shared_ptr: numarare de referinte, ultima copie elibereaza resursa
    {
        std::shared_ptr<Investment> s1 = std::make_shared<Stock>("Actiune partajata");
        std::cout << "[shared] use_count dupa creare: " << s1.use_count() << "\n";
        {
            std::shared_ptr<Investment> s2 = s1;  // copiere permisa
            std::cout << "[shared] use_count dupa copiere: " << s1.use_count()
                      << ", in viata: " << Investment::alive << "\n";
        }
        std::cout << "[shared] use_count dupa iesirea lui s2: " << s1.use_count()
                  << ", in viata: " << Investment::alive << "\n";
    }
    std::cout << "[shared] dupa iesirea lui s1: " << Investment::alive << "\n\n";
}
