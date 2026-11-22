#pragma once
// Item 11: Handle assignment to self in operator=.
#include <string>


class Bitmap {
public:
    explicit Bitmap(std::string d = "");
    Bitmap(const Bitmap& o);
    Bitmap& operator=(const Bitmap&) = default;
    ~Bitmap();

    std::string data;
    static int copies;  // numar de copieri efectuate
    static int alive;   // obiecte Bitmap in viata
};


class WidgetIdentity {
public:
    explicit WidgetIdentity(const std::string& s);
    WidgetIdentity(const WidgetIdentity& o);
    ~WidgetIdentity();
    WidgetIdentity& operator=(const WidgetIdentity& rhs);
    const std::string& data() const;

private:
    Bitmap* pb;
};


class WidgetOrdering {
public:
    explicit WidgetOrdering(const std::string& s);
    WidgetOrdering(const WidgetOrdering& o);
    ~WidgetOrdering();
    WidgetOrdering& operator=(const WidgetOrdering& rhs);
    const std::string& data() const;

private:
    Bitmap* pb;
};

class WidgetSwap {
public:
    explicit WidgetSwap(const std::string& s);
    WidgetSwap(const WidgetSwap& o);
    ~WidgetSwap();
    void swap(WidgetSwap& other) noexcept;
    WidgetSwap& operator=(const WidgetSwap& rhs);
    const std::string& data() const;

private:
    Bitmap* pb;
};

void demoItem11();
