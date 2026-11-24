#ifndef ITEM14_HPP
#define ITEM14_HPP
// Item 14: Think carefully about copying behavior in resource-managing classes.

#include <cstddef>
#include <memory>

// Resursa simulata: un mutex cu API de tip C (lock/unlock).
struct Mutex {
    int id;
    bool locked;
};

void lock(Mutex* pm);
void unlock(Mutex* pm);


// Optiunea 1: interzicem copierea (cel mai des folosit).

class NonCopyableLock {
public:
    explicit NonCopyableLock(Mutex* pm);
    ~NonCopyableLock();

    NonCopyableLock(const NonCopyableLock&) = delete;
    NonCopyableLock& operator=(const NonCopyableLock&) = delete;

private:
    Mutex* mutexPtr_;
};


// Optiunea 2: reference counting (shared_ptr cu "deleter" personalizat).
class SharedLock {
public:
    explicit SharedLock(Mutex* pm);
    long useCount() const;

private:
    std::shared_ptr<Mutex> mutexPtr_;
};


// Optiunea 3: copiem resursa din interior (deep copy).
class DeepBuffer {
public:
    explicit DeepBuffer(const char* text);
    DeepBuffer(const DeepBuffer& rhs);
    DeepBuffer& operator=(const DeepBuffer& rhs);
    ~DeepBuffer();

    void setFirst(char c);
    const char* data() const;

private:
    void swap(DeepBuffer& other) noexcept;
    char* data_;
    std::size_t size_;
};


// Optiunea 4: transferam proprietatea (move; sursa ramane fara resursa).

class MovableLock {
public:
    explicit MovableLock(Mutex* pm);
    ~MovableLock();

    MovableLock(const MovableLock&) = delete;
    MovableLock& operator=(const MovableLock&) = delete;

    MovableLock(MovableLock&& other) noexcept;
    MovableLock& operator=(MovableLock&& other) noexcept;

    bool owns() const;

private:
    void release();
    Mutex* mutexPtr_;
};

MovableLock acquire(Mutex& m);


// GRESIT: clasa RAII cu copiere implicita => doua obiecte inchid acelasi
bool openFile(int fd);
bool closeFile(int fd);

class BadFile {
public:
    explicit BadFile(int fd);
    ~BadFile();
    // copy ctor / operator= generate implicit: copiaza doar int-ul fd_
private:
    int fd_;
};

void demoItem14();

#endif  // ITEM14_HPP
