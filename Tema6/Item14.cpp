#include "Item14.hpp"

#include <cstring>
#include <iostream>
#include <set>
#include <utility>


void lock(Mutex* pm) {
    pm->locked = true;
    std::cout << "    [lock]   mutex " << pm->id << " blocat\n";
}

void unlock(Mutex* pm) {
    pm->locked = false;
    std::cout << "    [unlock] mutex " << pm->id << " deblocat\n";
}

// ---------------- Optiunea 1: NonCopyableLock ----------------
NonCopyableLock::NonCopyableLock(Mutex* pm) : mutexPtr_(pm) { lock(mutexPtr_); }
NonCopyableLock::~NonCopyableLock() { unlock(mutexPtr_); }

// ---------------- Optiunea 2: SharedLock ----------------
// Al doilea argument al shared_ptr este "deleter": se apeleaza unlock(pm)
// in loc de delete cand contorul ajunge la 0.
SharedLock::SharedLock(Mutex* pm) : mutexPtr_(pm, unlock) { lock(pm); }
long SharedLock::useCount() const { return mutexPtr_.use_count(); }

// ---------------- Optiunea 3: DeepBuffer ----------------
DeepBuffer::DeepBuffer(const char* text)
    : data_(new char[std::strlen(text) + 1]), size_(std::strlen(text) + 1) {
    std::memcpy(data_, text, size_);
}

DeepBuffer::DeepBuffer(const DeepBuffer& rhs)
    : data_(new char[rhs.size_]), size_(rhs.size_) {
    std::memcpy(data_, rhs.data_, size_);  // copie proprie a resursei
}

DeepBuffer& DeepBuffer::operator=(const DeepBuffer& rhs) {
    DeepBuffer temp(rhs);  // copy and swap (Item 11)
    swap(temp);
    return *this;          // Item 10
}

DeepBuffer::~DeepBuffer() { delete[] data_; }

void DeepBuffer::swap(DeepBuffer& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
}

void DeepBuffer::setFirst(char c) { data_[0] = c; }
const char* DeepBuffer::data() const { return data_; }

// ---------------- Optiunea 4: MovableLock ----------------
MovableLock::MovableLock(Mutex* pm) : mutexPtr_(pm) { lock(mutexPtr_); }
MovableLock::~MovableLock() { release(); }

MovableLock::MovableLock(MovableLock&& other) noexcept : mutexPtr_(other.mutexPtr_) {
    other.mutexPtr_ = nullptr;  // sursa nu mai detine resursa
}

MovableLock& MovableLock::operator=(MovableLock&& other) noexcept {
    if (this != &other) {
        release();                      // eliberam ce detineam
        mutexPtr_ = other.mutexPtr_;
        other.mutexPtr_ = nullptr;
    }
    return *this;
}

bool MovableLock::owns() const { return mutexPtr_ != nullptr; }

void MovableLock::release() {
    if (mutexPtr_) {
        unlock(mutexPtr_);
        mutexPtr_ = nullptr;
    }
}

MovableLock acquire(Mutex& m) { return MovableLock(&m); }

// ---------------- BadFile (gresit) ----------------
namespace {
std::set<int>& openFiles() {
    static std::set<int> files;
    return files;
}
}  // namespace

bool openFile(int fd) {
    openFiles().insert(fd);
    std::cout << "    [open]   fd " << fd << " deschis\n";
    return true;
}

bool closeFile(int fd) {
    if (openFiles().erase(fd) == 0) {
        std::cout << "    [close]  EROARE: fd " << fd
                  << " era deja inchis (double close)!\n";
        return false;
    }
    std::cout << "    [close]  fd " << fd << " inchis\n";
    return true;
}

BadFile::BadFile(int fd) : fd_(fd) { openFile(fd_); }
BadFile::~BadFile() { closeFile(fd_); }

// ---------------- Demo ----------------
void demoItem14() {
    std::cout << "=== Item 14: comportamentul la copiere al claselor RAII ===\n";

    std::cout << "\n-- Optiunea 1: copiere interzisa --\n";
    Mutex m1{1, false};
    {
        NonCopyableLock l(&m1);
        // NonCopyableLock l2 = l;   // EROARE DE COMPILARE: copiere stearsa
    }
    std::cout << "  m1 blocat dupa scope? " << std::boolalpha << m1.locked << "\n";

    std::cout << "\n-- Optiunea 2: reference counting (SharedLock) --\n";
    Mutex m2{2, false};
    {
        SharedLock a(&m2);
        {
            SharedLock b = a;  // copiere permisa
            std::cout << "  copii active: " << a.useCount() << "\n";
        }
        std::cout << "  dupa moartea lui b: copii=" << a.useCount()
                  << ", m2 blocat? " << m2.locked << "  (inca blocat)\n";
    }
    std::cout << "  dupa moartea lui a: m2 blocat? " << m2.locked << "\n";

    std::cout << "\n-- Optiunea 3: copiere profunda (DeepBuffer) --\n";
    {
        DeepBuffer x("abc");
        DeepBuffer y = x;  // copie proprie
        y.setFirst('Z');
        std::cout << "  x=" << x.data() << "  y=" << y.data()
                  << "  (independente)\n";
        x = y;
        std::cout << "  dupa x = y: x=" << x.data() << "\n";
    }

    std::cout << "\n-- Optiunea 4: transfer de proprietate (MovableLock) --\n";
    Mutex m3{3, false};
    {
        MovableLock l1 = acquire(m3);
        MovableLock l2 = std::move(l1);
        std::cout << "  l1 detine? " << l1.owns() << ", l2 detine? " << l2.owns() << "\n";
    }
    std::cout << "  m3 blocat dupa scope? " << m3.locked << "\n";

    std::cout << "\n-- GRESIT: copiere implicita intr-o clasa RAII (BadFile) --\n";
    {
        BadFile f1(7);
        BadFile f2 = f1;  // copiaza doar fd_ => ambele vor inchide fd 7
        (void)f2;
    }
    std::cout << "\n";
}
