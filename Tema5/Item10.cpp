#include "Item10.h"

#include <iostream>


Counter::Counter(int v) : value_(v) {}

Counter& Counter::operator=(const Counter& rhs) {
    value_ = rhs.value_;
    return *this;
}

Counter& Counter::operator+=(const Counter& rhs) {
    value_ += rhs.value_;
    return *this;
}

Counter& Counter::operator=(int v) {
    value_ = v;
    return *this;
}

int Counter::value() const { return value_; }


BadCounter::BadCounter(int v) : value_(v) {}
void BadCounter::operator=(const BadCounter& rhs) { value_ = rhs.value_; }
int BadCounter::value() const { return value_; }


void demoItem10() {
    std::cout << "=== Item 10: operator= intoarce *this ===\n";

    Counter a(1), b(2), c(3);
    a = b = c;  
    std::cout << "dupa a = b = c       -> a=" << a.value()
              << " b=" << b.value() << " c=" << c.value() << "\n";

    (a = 10) += Counter(5); 
    std::cout << "dupa (a = 10) += 5   -> a=" << a.value() << "\n";

    a += b += c;  
    std::cout << "dupa a += b += c     -> a=" << a.value()
              << " b=" << b.value() << "\n";

    Counter& ref = (a = b);  
    std::cout << "(a = b) este chiar a? " << std::boolalpha << (&ref == &a) << "\n";

    BadCounter x(1), y(2), z(3);
    x = y;  
    (void)z;
    std::cout << "BadCounter: x = y merge, dar 'x = y = z' nu s-ar compila\n\n";
}
