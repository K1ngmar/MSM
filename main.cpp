
#include <string>
#include <iostream>
#include <tuple>
#include <functional>
#include <typeindex>
#include <typeinfo>

struct None
{};

template<class A, class B, class C>
struct Row
{
    using Type = std::string;
    using State = A;
    using Event = B;
    using Guard = C;
};

template<class A, class C>
struct Row<A, None, C>
{
    using Type = int;
    using State = A;
    using Event = None;
    using Guard = C;
};

template<class A>
struct Row<A, None, None>
{
    using Type = float;
    using State = A;
    using Event = None;
    using Guard = None;
};

template<class A, class B>
struct Row<A, B, None>
{
    using Type = size_t;
    using State = A;
    using Event = B;
    using Guard = None;
};

template<class ...Rows>
struct TransitionTable
{
};

template<class ...Rows>
void PrintRows(std::tuple<Rows...> transitionTable)
{
    ((
        std::cout << typeid(typename Rows::State).name() << ", " <<
                     typeid(typename Rows::Event).name() << ", " <<
                     typeid(typename Rows::Guard).name() << std::endl
    ), ...);
}


template<typename ...Rows>
using tuple_cat_t = decltype(std::tuple_cat(std::declval<Rows>()...));

template<typename ...Rows>
using remove_t = tuple_cat_t<
    typename std::conditional<
        std::is_same_v<typename Rows::State, float>,
        std::tuple<Rows>,
        std::tuple<>
    >::type...
>;

int main()
{
    using transitionTable = TransitionTable<
        Row<int, float, char>,
        Row<int, float, None>,
        Row<float, int, None>,
        Row<float, None, None>
    >;

    // auto matchingRows = GetRows<int, float>(transitionTable);

    // PrintRows(transitionTable);



    remove_t<
        Row<int, float, char>,
        Row<int, float, None>,
        Row<float, int, None>,
        Row<float, None, None>
    > a;
	PrintRows(a);


    return 0;
}
