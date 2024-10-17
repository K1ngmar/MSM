
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
void PrintRows(TransitionTable<Rows...> transitionTable)
{
    ((
        std::cout << typeid(typename Rows::State).name() << ", " <<
                     typeid(typename Rows::Event).name() << ", " <<
                     typeid(typename Rows::Guard).name() << std::endl
    ), ...);
}

int main()
{
    TransitionTable<
        Row<int, float, char>,
        Row<int, float, None>,
        Row<float, int, None>,
        Row<float, None, None>
    > transitionTable;

    // auto matchingRows = GetRows<int, float>(transitionTable);

    PrintRows(transitionTable);


    return 0;
}
