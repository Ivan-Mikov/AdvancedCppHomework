#pragma once

#include <map>
#include <string>
#include <iostream>
#include <memory>

using Context = std::map<std::string, double>;

class Expression {
public:
    virtual ~Expression() = default;
    virtual double calculate(const Context& context) = 0;
    virtual void print() = 0;
};

class Constant : public Expression {
    double value;
public:
    Constant(double value) : value(value) { ; }    

    double calculate(const Context&) {
        return value;
    }

    void print() {
        std::cout << value;
    }
};

// Здесь использую .at вместо [], т.к. [] модифицирует map, создавая
// новый элемент со значением по умолчанию при отстутствии ключа.
// .at же выбрасывает исключение, что здесь уместно
class Variable : public Expression {
    std::string name;
public:
    Variable(std::string name) : name(name) { ; }  

    double calculate(const Context& context) {
        return context.at(name);
    }

    void print() {
        std::cout << name;
    }
};

class Addition : public Expression {
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    Addition(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) : left(left), right(right) { ; }

    double calculate(const Context& context) {
        return left->calculate(context) + right->calculate(context);
    }

    void print() {
        std::cout << "(";
        left->print();
        std::cout << " + ";
        right->print();
        std::cout << ")";
    }
};

class Subtraction : public Expression {
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    Subtraction(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) : left(left), right(right) { ; }

    double calculate(const Context& context) {
        return left->calculate(context) - right->calculate(context);
    }

    void print() {
        std::cout << "(";
        left->print();
        std::cout << " - ";
        right->print();
        std::cout << ")";
    }
};

class Multiplication : public Expression {
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    Multiplication(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) : left(left), right(right) { ; }

    double calculate(const Context& context) {
        return left->calculate(context) * right->calculate(context);
    }

    void print() {
        std::cout << "(";
        left->print();
        std::cout << " * ";
        right->print();
        std::cout << ")";
    }
};

class Division : public Expression {
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    Division(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) : left(left), right(right) { ; }

    double calculate(const Context& context) {
        return left->calculate(context) / right->calculate(context);
    }

    void print() {
        std::cout << "(";
        left->print();
        std::cout << " / ";
        right->print();
        std::cout << ")";
    }
};

