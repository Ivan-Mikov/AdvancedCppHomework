#include <memory>

namespace typelist {

    template <typename... Types>
    struct TypeList;

    // ----- Size -----
    template <typename T>
    struct Size;

    template <>
    struct Size<TypeList<>> {
        constexpr static size_t value = 0;
    };

    template <typename Head, typename... Tail>
    struct Size<TypeList<Head, Tail...>>
    {
        constexpr static size_t value = 1 + Size<TypeList<Tail...>>::value;
    };

    // ----- Contains -----
    template <typename T, typename List>
    struct Contains;

    template <typename T>
    struct Contains<T, TypeList<>> {
        constexpr static bool value = false;
    };

    template <typename T, typename Head, typename... Tail>
    struct Contains<T, TypeList<Head, Tail...>>
    {
        constexpr static bool value = std::is_same<T, Head>::value || Contains<T, TypeList<Tail...>>::value;
    };

    // ----- PushBack -----
    template <typename New, typename List>
    struct PushBack;
    
    template <typename New, typename... Types>
    struct PushBack<New, TypeList<Types...>> {
        using type = TypeList<Types..., New>;
    };

    // ----- PushFront -----
    template <typename New, typename List>
    struct PushFront;
    
    template <typename New, typename... Types>
    struct PushFront<New, TypeList<Types...>> {
        using type = TypeList<New, Types...>;
    };

    // ----- Get -----
    template<size_t Index, typename List>
    struct Get;

    template<size_t Index>
    struct Get<Index, TypeList<>> {
        static_assert(false, "Index is out of range");
    };

    template<typename Head, typename... Tail>
    struct Get<0, TypeList<Head, Tail...>> {
        using type = Head;
    };

    template<size_t Index, typename Head, typename... Tail>
    struct Get<Index, TypeList<Head, Tail...>> {
        using type = typename Get<(Index - 1), TypeList<Tail...>>::type;
    };

    // ----- Find -----
    template <typename T, typename List>
    struct Find;

    template <typename T>
    struct Find<T, TypeList<>> {
        static_assert(false, "There isn't this type in TypeList");
    };

    template <typename T, typename... Tail>
    struct Find<T, TypeList<T, Tail...>> {
        constexpr static int value = 0;
    };

    template <typename T, typename Head, typename... Tail>
    struct Find<T, TypeList<Head, Tail...>> {
        constexpr static int value = 1 + Find<T, TypeList<Tail...>>::value;
    };
}
