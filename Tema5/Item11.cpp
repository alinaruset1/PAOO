#include "Item11.h"

#include <iostream>
#include <utility>

// ---------------- Bitmap ----------------
int Bitmap::copies = 0;
int Bitmap::alive = 0;

Bitmap::Bitmap(std::string d) : data(std::move(d)) { ++alive; }
Bitmap::Bitmap(const Bitmap& o) : data(o.data) { ++alive; ++copies; }
Bitmap::~Bitmap() { --alive; }

// ---------------- WidgetIdentity ----------------
WidgetIdentity::WidgetIdentity(const std::string& s) : pb(new Bitmap(s)) {}
WidgetIdentity::WidgetIdentity(const WidgetIdentity& o) : pb(new Bitmap(*o.pb)) {}
WidgetIdentity::~WidgetIdentity() { delete pb; }

WidgetIdentity& WidgetIdentity::operator=(const WidgetIdentity& rhs) {
    if (this == &rhs) return *this;  // identity test
    delete pb;                       // daca new arunca mai jos, pb ramane invalid
    pb = new Bitmap(*rhs.pb);
    return *this;
}
const std::string& WidgetIdentity::data() const { return pb->data; }

// ---------------- WidgetOrdering ----------------
WidgetOrdering::WidgetOrdering(const std::string& s) : pb(new Bitmap(s)) {}
WidgetOrdering::WidgetOrdering(const WidgetOrdering& o) : pb(new Bitmap(*o.pb)) {}
WidgetOrdering::~WidgetOrdering() { delete pb; }

WidgetOrdering& WidgetOrdering::operator=(const WidgetOrdering& rhs) {
    Bitmap* original = pb;     // retinem pointerul vechi
    pb = new Bitmap(*rhs.pb);  // daca arunca, pb ramane neschimbat
    delete original;           // stergem abia acum
    return *this;
}
const std::string& WidgetOrdering::data() const { return pb->data; }

// ---------------- WidgetSwap ----------------
WidgetSwap::WidgetSwap(const std::string& s) : pb(new Bitmap(s)) {}
WidgetSwap::WidgetSwap(const WidgetSwap& o) : pb(new Bitmap(*o.pb)) {}
WidgetSwap::~WidgetSwap() { delete pb; }

void WidgetSwap::swap(WidgetSwap& other) noexcept { std::swap(pb, other.pb); }

WidgetSwap& WidgetSwap::operator=(const WidgetSwap& rhs) {
    WidgetSwap temp(rhs);  // copie a lui rhs
    swap(temp);            // temp preia vechea resursa si o distruge la final
    return *this;
}
const std::string& WidgetSwap::data() const { return pb->data; }

// ---------------- Demo ----------------
namespace {

template <typename W>
void testSelfAssignment(const char* name) {
    Bitmap::copies = 0;
    {
        W w("imagine-A");
        W& alias = w;  // alias: auto-atribuire mai greu de observat
        w = alias;
        std::cout << "  " << name << ": dupa w = w      -> data=\"" << w.data()
                  << "\", copieri Bitmap=" << Bitmap::copies << "\n";

        W other("imagine-B");
        w = other;
        std::cout << "  " << name << ": dupa w = other  -> data=\"" << w.data() << "\"\n";
    }
    std::cout << "  " << name << ": Bitmap ramase in viata (0 = fara scurgeri): "
              << Bitmap::alive << "\n";
}

}  // namespace

void demoItem11() {
    std::cout << "=== Item 11: auto-atribuirea in operator= ===\n";
    testSelfAssignment<WidgetIdentity>("Identity test ");
    testSelfAssignment<WidgetOrdering>("Ordering      ");
    testSelfAssignment<WidgetSwap>("Copy and swap ");
    std::cout << "(Identity evita copierea la w=w; celelalte fac o copie inutila,\n"
                 " dar sunt exception-safe.)\n\n";
}
