// tests.cpp
#include "typelist.h"
#include <iostream>

using namespace typelist;

// Тестовые списки
using Empty = TypeList<>;
using Single = TypeList<int>;
using Two = TypeList<int, double>;
using Multiple = TypeList<int, float, double, char>;

// ========== Size ==========
static_assert(Size<Empty>::value == 0, "Size: empty");
static_assert(Size<Single>::value == 1, "Size: single");
static_assert(Size<Two>::value == 2, "Size: two");
static_assert(Size<Multiple>::value == 4, "Size: multiple");

// ========== Contains ==========
static_assert(Contains<int, Single>::value, "Contains: int in single");
static_assert(!Contains<float, Single>::value, "Contains: float not in single");
static_assert(Contains<int, Two>::value, "Contains: int in two");
static_assert(Contains<double, Two>::value, "Contains: double in two");
static_assert(!Contains<float, Two>::value, "Contains: float not in two");
static_assert(Contains<int, Multiple>::value, "Contains: int in multiple");
static_assert(Contains<float, Multiple>::value, "Contains: float in multiple");
static_assert(Contains<double, Multiple>::value, "Contains: double in multiple");
static_assert(Contains<char, Multiple>::value, "Contains: char in multiple");
static_assert(!Contains<long, Multiple>::value, "Contains: long not in multiple");
static_assert(!Contains<void, Empty>::value, "Contains: empty list");

// ========== PushBack ==========
using PB1 = PushBack<int, Empty>::type;
static_assert(Size<PB1>::value == 1, "PushBack: size after push to empty");
static_assert(Contains<int, PB1>::value, "PushBack: int after push to empty");

using PB2 = PushBack<float, Single>::type;
static_assert(Size<PB2>::value == 2, "PushBack: size after push to single");
static_assert(Contains<int, PB2>::value, "PushBack: old type exists");
static_assert(Contains<float, PB2>::value, "PushBack: new type exists");

using PB3 = PushBack<char, Multiple>::type;
static_assert(Size<PB3>::value == 5, "PushBack: size after push to multiple");
static_assert(Contains<int, PB3>::value && Contains<float, PB3>::value && 
              Contains<double, PB3>::value && Contains<char, PB3>::value, 
              "PushBack: all original types exist");
static_assert(std::is_same<char, Get<4, PB3>::type>::value, "PushBack: new type at end");

// ========== PushFront ==========
using PF1 = PushFront<int, Empty>::type;
static_assert(Size<PF1>::value == 1, "PushFront: size after push to empty");
static_assert(std::is_same<int, Get<0, PF1>::type>::value, "PushFront: type at front");

using PF2 = PushFront<float, Single>::type;
static_assert(Size<PF2>::value == 2, "PushFront: size after push to single");
static_assert(std::is_same<float, Get<0, PF2>::type>::value, "PushFront: new type at front");
static_assert(std::is_same<int, Get<1, PF2>::type>::value, "PushFront: old type shifted");

using PF3 = PushFront<char, Multiple>::type;
static_assert(Size<PF3>::value == 5, "PushFront: size after push to multiple");
static_assert(std::is_same<char, Get<0, PF3>::type>::value, "PushFront: char at front");
static_assert(std::is_same<int, Get<1, PF3>::type>::value, "PushFront: int at second");
static_assert(std::is_same<float, Get<2, PF3>::type>::value, "PushFront: float at third");
static_assert(std::is_same<double, Get<3, PF3>::type>::value, "PushFront: double at fourth");

// ========== Get ==========
static_assert(std::is_same<int, Get<0, Single>::type>::value, "Get: index 0 from single");
static_assert(std::is_same<int, Get<0, Two>::type>::value, "Get: index 0 from two");
static_assert(std::is_same<double, Get<1, Two>::type>::value, "Get: index 1 from two");
static_assert(std::is_same<int, Get<0, Multiple>::type>::value, "Get: index 0 from multiple");
static_assert(std::is_same<float, Get<1, Multiple>::type>::value, "Get: index 1 from multiple");
static_assert(std::is_same<double, Get<2, Multiple>::type>::value, "Get: index 2 from multiple");
static_assert(std::is_same<char, Get<3, Multiple>::type>::value, "Get: index 3 from multiple");

// ========== Find ==========
static_assert(Find<int, Single>::value == 0, "Find: int at index 0 in single");
static_assert(Find<int, Two>::value == 0, "Find: int at index 0 in two");
static_assert(Find<double, Two>::value == 1, "Find: double at index 1 in two");
static_assert(Find<int, Multiple>::value == 0, "Find: int at index 0");
static_assert(Find<float, Multiple>::value == 1, "Find: float at index 1");
static_assert(Find<double, Multiple>::value == 2, "Find: double at index 2");
static_assert(Find<char, Multiple>::value == 3, "Find: char at index 3");

// ========== Комбинированные тесты ==========
// PushBack + Get
using Combined = PushBack<char, PushBack<float, Single>::type>::type;
static_assert(Size<Combined>::value == 3, "Combined: size");
static_assert(std::is_same<int, Get<0, Combined>::type>::value, "Combined: first");
static_assert(std::is_same<float, Get<1, Combined>::type>::value, "Combined: second");
static_assert(std::is_same<char, Get<2, Combined>::type>::value, "Combined: third");

// PushFront + Find
using Combined2 = PushFront<char, PushFront<float, Single>::type>::type;
static_assert(Find<char, Combined2>::value == 0, "Combined2: char at front");
static_assert(Find<float, Combined2>::value == 1, "Combined2: float at second");
static_assert(Find<int, Combined2>::value == 2, "Combined2: int at third");

// Contains + Get
static_assert(Contains<Get<2, Multiple>::type, Multiple>::value, "Get returns type that exists in list");

int main() {
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
