#include "factory.h"

int main() {
    ExpressionFactory factory;
    std::shared_ptr<Constant> c = factory.createConstant(2);
    std::shared_ptr<Variable> v = factory.createVariable("x");
    Addition *expression = new Addition(c, v);
    Context context;
    context["x"] = 3;
    expression->print();
    std::cout << "\n" << expression->calculate(context) << std::endl;
}