#include "item6_interzicere.hpp"
#include <iostream>

ReactorNuclear::ReactorNuclear(const std::string& id) : reactor_id(id) {
    std::cout << "Reactor " << reactor_id << " activat.\n";
}

ReactorNuclear::~ReactorNuclear() {
    std::cout << "Reactor " << reactor_id << " oprit.\n";
}

void ReactorNuclear::afisare() const {
    std::cout << "Status Reactor Unicat: " << reactor_id << " functional.\n";
}
