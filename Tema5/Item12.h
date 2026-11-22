#pragma once
// Item 12: Copy all parts of an object.
#include <string>


class Customer {
public:
    explicit Customer(std::string n = "<necunoscut>");
    Customer(const Customer& rhs);
    Customer& operator=(const Customer& rhs);
    virtual ~Customer() = default;

    const std::string& name() const;

private:
    std::string name_;
};


class BadPriorityCustomer : public Customer {
public:
    BadPriorityCustomer(const std::string& n, int p);
    BadPriorityCustomer(const BadPriorityCustomer& rhs);
    BadPriorityCustomer& operator=(const BadPriorityCustomer& rhs);

    int priority() const;

private:
    int priority_;
};


class PriorityCustomer : public Customer {
public:
    PriorityCustomer(const std::string& n, int p, std::string note);
    PriorityCustomer(const PriorityCustomer& rhs);
    PriorityCustomer& operator=(const PriorityCustomer& rhs);

    int priority() const;
    const std::string& note() const;

private:
    int priority_;
    std::string note_;
    
};


class Order {
public:
    Order(int id, std::string desc);
    Order(const Order& rhs);
    Order& operator=(const Order& rhs);

    int id() const;
    const std::string& desc() const;

private:
    void init(int id, std::string desc);
    int id_;
    std::string desc_;
};

void demoItem12();
