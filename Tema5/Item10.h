#pragma once
// Item 10: Have assignment operators return a reference to *this.

class Counter {
public:
    explicit Counter(int v = 0);

    Counter& operator=(const Counter& rhs);
    Counter& operator+=(const Counter& rhs);  
    Counter& operator=(int v);               

    int value() const;

private:
    int value_;
};

// operator= care NU respecta conventia (intoarce void): lantuirea nu compileaza
class BadCounter {
public:
    explicit BadCounter(int v = 0);
    void operator=(const BadCounter& rhs);  // GRESIT
    int value() const;

private:
    int value_;
};

void demoItem10();
