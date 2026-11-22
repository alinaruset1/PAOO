#include "Item12.h"

#include <iostream>
#include <utility>

// ---------------- Customer ----------------
Customer::Customer(std::string n) : name_(std::move(n)) {}
Customer::Customer(const Customer& rhs) : name_(rhs.name_) {}

Customer& Customer::operator=(const Customer& rhs) {
    name_ = rhs.name_;
    return *this;
}
const std::string& Customer::name() const { return name_; }

// ---------------- BadPriorityCustomer ----------------
BadPriorityCustomer::BadPriorityCustomer(const std::string& n, int p)
    : Customer(n), priority_(p) {}

BadPriorityCustomer::BadPriorityCustomer(const BadPriorityCustomer& rhs)
    : priority_(rhs.priority_) {}  // lipseste Customer(rhs) => baza default-construita

BadPriorityCustomer& BadPriorityCustomer::operator=(const BadPriorityCustomer& rhs) {
    priority_ = rhs.priority_;  // lipseste Customer::operator=(rhs)
    return *this;
}
int BadPriorityCustomer::priority() const { return priority_; }

// ---------------- PriorityCustomer ----------------
PriorityCustomer::PriorityCustomer(const std::string& n, int p, std::string note)
    : Customer(n), priority_(p), note_(std::move(note)) {}

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
    : Customer(rhs),  
      priority_(rhs.priority_),
      note_(rhs.note_) {}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs) {
    Customer::operator=(rhs); 
    priority_ = rhs.priority_;
    note_ = rhs.note_;
    return *this;
}
int PriorityCustomer::priority() const { return priority_; }
const std::string& PriorityCustomer::note() const { return note_; }

// ---------------- Order ----------------
Order::Order(int id, std::string desc) { init(id, std::move(desc)); }
Order::Order(const Order& rhs) { init(rhs.id_, rhs.desc_); }

Order& Order::operator=(const Order& rhs) {
    if (this != &rhs) init(rhs.id_, rhs.desc_);
    return *this;
}
int Order::id() const { return id_; }
const std::string& Order::desc() const { return desc_; }
void Order::init(int id, std::string desc) {
    id_ = id;
    desc_ = std::move(desc);
}

// ---------------- Demo ----------------
void demoItem12() {
    std::cout << "=== Item 12: copiaza toate partile obiectului ===\n";

    BadPriorityCustomer bad("Ana", 5);
    BadPriorityCustomer badCopy(bad);
    std::cout << "GRESIT : original   nume=" << bad.name() << " prio=" << bad.priority() << "\n";
    std::cout << "GRESIT : copy ctor  nume=" << badCopy.name()
              << " prio=" << badCopy.priority() << "   <-- numele s-a pierdut!\n";

    BadPriorityCustomer badAssigned("Bogdan", 1);
    badAssigned = bad;
    std::cout << "GRESIT : operator=  nume=" << badAssigned.name()
              << " prio=" << badAssigned.priority() << "   <-- numele a ramas vechi!\n";

    PriorityCustomer good("Ana", 5, "client VIP");
    PriorityCustomer goodCopy(good);
    std::cout << "CORECT : copy ctor  nume=" << goodCopy.name()
              << " prio=" << goodCopy.priority() << " nota=" << goodCopy.note() << "\n";

    PriorityCustomer goodAssigned("Bogdan", 1, "nou");
    goodAssigned = good;
    std::cout << "CORECT : operator=  nume=" << goodAssigned.name()
              << " prio=" << goodAssigned.priority() << " nota=" << goodAssigned.note() << "\n";

    Order o1(1, "laptop"), o2(2, "mouse");
    Order o3(o1);
    o2 = o1;
    std::cout << "Order cu init() comun: o2=" << o2.id() << "/" << o2.desc()
              << " o3=" << o3.id() << "/" << o3.desc() << "\n\n";
}
