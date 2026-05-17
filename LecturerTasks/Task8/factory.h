#pragma once

#include "expression.h"

#include <unordered_map>
#include <string>
#include <memory>

// В примере лектора использовались встроенные указатели С++. Я же использую
// shared_ptr, т.к. без него мне прихоидлось придумывать костыли, которые нарушали
// RAII. Например, Addition хранит указатели на Expression, но не удаляет их,
// иначе они удалялись в самой фабрике и возникали ошибки, типа двойного вызова
// delete.

class ExpressionFactory {
    std::unordered_map<double, std::shared_ptr<Constant>> constants;
    std::unordered_map<std::string, std::shared_ptr<Variable>> variables;

public:
    ExpressionFactory() {
        for (double c = -5; c <= 256; c++) {
            createConstant(c);
        }
    }

    std::shared_ptr<Constant> createConstant(double value) {
        if (constants.find(value) != constants.end())
            return constants[value];
        auto constant = std::make_shared<Constant>(value);
        constants[value] = constant;
        return constant;
    }

    std::shared_ptr<Variable> createVariable(std::string name) {
        if (variables.find(name) != variables.end())
            return variables[name];
        auto variable = std::make_shared<Variable>(name);
        variables[name] = variable;
        return variable;
    }

    void deleteConstant(double value) {
        for (double c = -5; c <= 256; c++) {
            if (value == c) return;
        }
        auto constant = constants[value];
        constants.erase(value);
    }

    void deleteVariable(std::string name) {
        auto variable = variables[name];
        variables.erase(name);
    }
};