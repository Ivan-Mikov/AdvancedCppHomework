#include "typelist.h"

#include <iostream>

int main() {
    using namespace typelist;

    using Empty = TypeList<>;
    using Single = TypeList<int>;
    using Multiple = TypeList<int, float, double, char>;
    using Twice = TypeList<int, int>;

    // Size
    static_assert(Size<Empty>::value == 0);
    static_assert(Size<Single>::value == 1);
    static_assert(Size<Multiple>::value == 4);
    static_assert(Size<Twice>::value == 2);

    // Contains
    static_assert(!Contains<bool, Empty>::value);
    static_assert(!Contains<bool, Single>::value);
    static_assert(!Contains<bool, Multiple>::value);
    static_assert(Contains<int, Multiple>::value);
    static_assert(Contains<int, Twice>::value);

    // Get
    static_assert(std::is_same<int, Get<0, Single>::type>::value);
    static_assert(std::is_same<int, Get<0, Multiple>::type>::value);
    static_assert(std::is_same<float, Get<1, Multiple>::type>::value);
    static_assert(std::is_same<double, Get<2, Multiple>::type>::value);
    static_assert(std::is_same<char, Get<3, Multiple>::type>::value);

    // PushBack
    using TestPush = TypeList<int>;
    using TestPush2 = PushBack<float, TestPush>::type;
    static_assert(Size<TestPush2>::value == 2);
    static_assert(std::is_same<float, Get<1, TestPush2>::type>::value);

    // PushFront
    using TestPush3 = PushFront<char, TestPush2>::type;
    static_assert(Size<TestPush3>::value == 3);
    static_assert(std::is_same<char, Get<0, TestPush3>::type>::value);

    // Find
    static_assert(Find<int, Single>::value == 0);
    static_assert(Find<float, Multiple>::value == 1);
    static_assert(Find<double, Multiple>::value == 2);
    static_assert(Find<char, Multiple>::value == 3);

    // Errors (must not compiled)
    // size_t i = Find<bool, Multiple>::value;
    // using ten = Get<10, Multiple>::type;
}