
#include <string>
#include <iostream>
#include <tuple>

struct None
{};

template<class A, class B, class C>
struct Row
{};

template<class A, class C>
struct Row<A, None, C>
{
    using Type = int;
};

int main()
{
    std::cout << static_cast<Row<int, None, float>::Type>(5.4) << std::endl;


    return 0;
}
