#ifndef ITEM13_HPP
#define ITEM13_HPP
// Item 13: Use objects to manage resources.  (RAII)

#include <memory>
#include <string>

// Resursa gestionata: o ierarhie de investitii create dinamic (heap).
class Investment {
public:
    explicit Investment(std::string name);
    virtual ~Investment();  // virtual: stergem prin pointer la baza

    const std::string& name() const;
    virtual double value() const = 0;

    static int alive;

private:
    std::string name_;
};

class Stock : public Investment {
public:
    explicit Stock(std::string name);
    double value() const override;
};

class Bond : public Investment {
public:
    explicit Bond(std::string name);
    double value() const override;
};

// Factory care intoarce pointer BRUT: apelantul trebuie sa-si aminteasca delete.
Investment* createInvestmentRaw(const std::string& kind);

// Factory moderna: intoarce direct un obiect care gestioneaza resursa.
std::unique_ptr<Investment> createInvestment(const std::string& kind);

// API vechi, care vrea pointer brut (folosim .get()).
double legacyValue(const Investment* pi);

void demoItem13();

#endif  // ITEM13_HPP
