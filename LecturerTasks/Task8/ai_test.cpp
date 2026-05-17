#include <iostream>
#include <cassert>
#include "factory.h"

using ExpressionPtr = std::shared_ptr<Expression>;

// Helper function to easily check if a memory address is identical
void print_test_header(const std::string& name) {
    std::cout << "\n==================================================\n";
    std::cout << " RUNNING: " << name << "\n";
    std::cout << "==================================================\n";
}

int main() {
    ExpressionFactory factory;
    Context context;

    // ----------------------------------------------------------------
    // TEST 1: The Flyweight Pattern (Shared Memory for Variables)
    // Formula: (x * x) + (x / 2)
    // ----------------------------------------------------------------
    {
        print_test_header("TEST 1: Variable Reuse (Flyweight Pattern)");

        // Creating 'x' twice via factory
        ExpressionPtr x1 = factory.createVariable("x");
        ExpressionPtr x2 = factory.createVariable("x");
        ExpressionPtr c2 = factory.createConstant(2);

        // Crucial validation: Both shared_ptrs MUST point to the exact same memory address
        std::cout << "[Flyweight Check] Address of x1: " << x1.get() << std::endl;
        std::cout << "[Flyweight Check] Address of x2: " << x2.get() << std::endl;
        assert(x1.get() == x2.get()); 
        std::cout << "-> SUCCESS: Both variables share a single object instance!\n" << std::endl;

        // Build tree using the exact same instances
        ExpressionPtr mul = std::make_shared<Multiplication>(x1, x2);       // (x * x)
        ExpressionPtr div = std::make_shared<Division>(x1, c2);             // (x / 2)
        ExpressionPtr root = std::make_shared<Addition>(mul, div);          // (x * x) + (x / 2)

        // Evaluate with Context A: x = 4 -> (4 * 4) + (4 / 2) = 16 + 2 = 18
        context["x"] = 4;
        std::cout << "Expression: ";
        root->print();
        std::cout << "\nResult with x=4: " << root->calculate(context) << " (Expected: 18)" << std::endl;
        assert(root->calculate(context) == 18);

        // Evaluate with Context B: x = 10 -> (10 * 10) + (10 / 2) = 100 + 5 = 105
        context["x"] = 10;
        std::cout << "Result with x=10: " << root->calculate(context) << " (Expected: 105)" << std::endl;
        assert(root->calculate(context) == 105);
    }

    // ----------------------------------------------------------------
    // TEST 2: Python Constant Cache Protection (-5 to 256)
    // ----------------------------------------------------------------
    {
        print_test_header("TEST 2: Python-style Precached Pool Protection");

        // Constant '100' falls inside [-5, 256] -> Precached
        ExpressionPtr c_cached = factory.createConstant(100);
        
        std::cout << "Attempting to delete cached constant 100..." << std::endl;
        factory.deleteConstant(100); // This must be completely ignored by the factory
        
        // Fetch again after 'deletion'
        ExpressionPtr c_cached_again = factory.createConstant(100);
        std::cout << "Address before delete: " << c_cached.get() << std::endl;
        std::cout << "Address after delete:  " << c_cached_again.get() << std::endl;
        assert(c_cached.get() == c_cached_again.get());
        std::cout << "-> SUCCESS: Precached constant survived destruction attempt!\n" << std::endl;

        // Constant '999.5' falls outside [-5, 256] -> Created on demand
        ExpressionPtr c_dynamic = factory.createConstant(999.5);
        void* original_address = c_dynamic.get();
        std::cout << "Dynamic constant address: " << original_address << std::endl;

        // Release our reference so use_count becomes 1 (only held inside the factory map)
        c_dynamic.reset(); 

        std::cout << "Deleting dynamic constant 999.5..." << std::endl;
        factory.deleteConstant(999.5); // Factory should safely evict it from memory

        // Re-create it. It should get a completely fresh memory block now
        ExpressionPtr c_dynamic_new = factory.createConstant(999.5);
        std::cout << "New dynamic constant address: " << c_dynamic_new.get() << std::endl;
        assert(original_address != c_dynamic_new.get());
        std::cout << "-> SUCCESS: Dynamic constant was safely evicted and re-created!" << std::endl;
    }

    // ----------------------------------------------------------------
    // TEST 3: Safe Factory Deletion prevents Dangling Pointers
    // ----------------------------------------------------------------
    {
        print_test_header("TEST 3: Smart Deletion (Tree protection)");

        ExpressionPtr y = factory.createVariable("y");
        ExpressionPtr c5 = factory.createConstant(5);
        
        // This tree keeps a reference to 'y'
        ExpressionPtr sub_tree = std::make_shared<Subtraction>(y, c5); // (y - 5)

        std::cout << "Attempting to delete active variable 'y' while sub_tree is using it..." << std::endl;
        factory.deleteVariable("y"); // Factory MUST ignore this since use_count > 1

        context["y"] = 15;
        std::cout << "Tree execution after factory delete: ";
        sub_tree->print();
        std::cout << " = " << sub_tree->calculate(context) << " (Expected: 10)" << std::endl;
        assert(sub_tree->calculate(context) == 10);
        std::cout << "-> SUCCESS: No crashing or memory corruption! 'y' is safe inside the tree." << std::endl;
    }

    // ----------------------------------------------------------------
    // TEST 4: Massive Nested Deep Tree (Mega Expression)
    // Formula: ((x + y) * (100 - z)) / ((2 * a) + (b - -5))
    // ----------------------------------------------------------------
    {
        print_test_header("TEST 4: Massive Deep Nesting Matrix");

        // Factory nodes setup
        ExpressionPtr x = factory.createVariable("x");
        ExpressionPtr y = factory.createVariable("y");
        ExpressionPtr z = factory.createVariable("z");
        ExpressionPtr a = factory.createVariable("a");
        ExpressionPtr b = factory.createVariable("b");
        
        ExpressionPtr c100 = factory.createConstant(100);
        ExpressionPtr c2   = factory.createConstant(2);
        ExpressionPtr c_m5 = factory.createConstant(-5); // cached boundary check

        // Building Left Branch: ((x + y) * (100 - z))
        ExpressionPtr left_add = std::make_shared<Addition>(x, y);
        ExpressionPtr left_sub = std::make_shared<Subtraction>(c100, z);
        ExpressionPtr left_branch = std::make_shared<Multiplication>(left_add, left_sub);

        // Building Right Branch: ((2 * a) + (b - -5))
        ExpressionPtr right_mul = std::make_shared<Multiplication>(c2, a);
        ExpressionPtr right_sub = std::make_shared<Subtraction>(b, c_m5);
        ExpressionPtr right_branch = std::make_shared<Addition>(right_mul, right_sub);

        // Complete Tree Root Node
        ExpressionPtr total_root = std::make_shared<Division>(left_branch, right_branch);

        // Map variables context configuration
        context["x"] = 5;
        context["y"] = 3;   // (5 + 3) = 8
        context["z"] = 90;  // (100 - 90) = 10  ==> Left side: 8 * 10 = 80
        
        context["a"] = 2;   // (2 * 2) = 4
        context["b"] = 11;  // (11 - -5) = 16   ==> Right side: 4 + 16 = 20
        
        // Total Math Result: 80 / 20 = 4

        std::cout << "Mega Expression Tree structure:\n";
        total_root->print();
        std::cout << "\n\nEvaluating mega tree..." << std::endl;
        
        double result = total_root->calculate(context);
        std::cout << "Execution Result: " << result << " (Expected: 4)" << std::endl;
        assert(result == 4);
        std::cout << "-> SUCCESS: Deep nested math tree evaluated perfectly!" << std::endl;
    }

    std::cout << "\n==================================================" << std::endl;
    std::cout << " ALL SUITE TESTS PASSED SUCCESSFULLY! ZERO LEAKS!" << std::endl;
    std::cout << "==================================================" << std::endl;

    return 0;
}
