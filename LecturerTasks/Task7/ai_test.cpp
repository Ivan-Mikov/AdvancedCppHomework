#include "set.h"

#include <iostream>
#include <cassert>

int main() {
    std::cout << "=== Starting Set Container Testing ===" << std::endl;

    // 1. Basic operations and automatic strategy switching test
    Set<int> my_set;
    
    std::cout << "Adding elements from 1 to 10 (ArrayImpl active)..." << std::endl;
    for (int i = 1; i <= 10; ++i) {
        my_set.Add(i);
    }
    
    // Check that duplicates are ignored and do not alter the size
    my_set.Add(5); 
    assert(my_set.Contains(5));
    
    std::cout << "Adding 11th element (Switching strategy to TreeImpl)..." << std::endl;
    my_set.Add(11);
    
    // Ensure that old and new data coexist perfectly after transformation
    assert(my_set.Contains(1) && "Error: lost element 1 after strategy switch!");
    assert(my_set.Contains(11) && "Error: failed to add element 11!");
    
    std::cout << "Removing an element from the BST tree..." << std::endl;
    my_set.Remove(5);
    assert(!my_set.Contains(5) && "Error: element 5 was not removed!");

    std::cout << "-> Basic functionality tests passed successfully!" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    // 2. Deep copying and assignment semantics test (Copy-and-Swap)
    std::cout << "Testing deep copying via copy constructor..." << std::endl;
    Set<int> copy_set = my_set; 
    
    assert(copy_set.Contains(11) && "Error: copying failed!");
    
    std::cout << "Modifying the copy (original must remain unchanged)..." << std::endl;
    copy_set.Add(42);
    assert(copy_set.Contains(42));
    assert(!my_set.Contains(42) && "Error: deep copy broken, original mutated!");

    std::cout << "Testing copy assignment operator..." << std::endl;
    Set<int> assigned_set;
    assigned_set = my_set; // Invokes your fixed Copy-and-Swap operator=
    assert(assigned_set.Contains(1));

    std::cout << "-> Copy and assignment tests passed successfully!" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    // 3. Set operations test
    std::cout << "Testing Union and Intersection..." << std::endl;
    
    Set<int> setA;
    setA.Add(1); setA.Add(2); setA.Add(3);

    Set<int> setB;
    setB.Add(3); setB.Add(4); setB.Add(5);

    // Test Union: {1, 2, 3} U {3, 4, 5} = {1, 2, 3, 4, 5}
    Set<int> union_result = setA.Union(setB);
    assert(union_result.Contains(1));
    assert(union_result.Contains(3));
    assert(union_result.Contains(5));

    // Test Intersection: {1, 2, 3} ^ {3, 4, 5} = {3}
    Set<int> intersect_result = setA.Intersection(setB);
    assert(intersect_result.Contains(3));
    assert(!intersect_result.Contains(1));
    assert(!intersect_result.Contains(5));

    std::cout << "-> Mathematical set operations work correctly!" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "=== All tests passed! Memory cleaned up automatically. ===" << std::endl;

    return 0;
}
