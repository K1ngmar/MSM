
#include "includes/MSM/BackEnd/Row/Utility.hpp"

#include <string>
#include <iostream>
#include <tuple>
#include <functional>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <any>
#include <exception>

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


template<typename ...Rows>
using tuple_cat_t = decltype(std::tuple_cat(std::declval<Rows>()...));

template<class ...Rows>
struct TransitionTable
{
	template<class State, class Event>
	struct GetPossibleTransitions
	{
		using possibleTransitions = tuple_cat_t<
			typename std::conditional<
				std::is_same_v<typename Rows::State, State> && std::is_same_v<typename Rows::Event, Event>,
				std::tuple<Rows>,
				std::tuple<>
			>::type...
		>;
	};

    using PossibleStates = tuple_cat_t<std::tuple<typename Rows::State>...>;
    PossibleStates possibleStates;

    // Calls your func with tuple element.
    template <size_t N = 0>
    auto runtime_get(size_t idx)
    {
        if (N == idx)
        {
            return std::get<N>(possibleStates);
        }

        if constexpr (N + 1 < std::tuple_size_v<PossibleStates>)
        {
            return runtime_get<N + 1>(idx);
        }
        else
        {
            throw std::runtime_error("impossible state");
        }
    }
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

template<class ...States>
void PrintStates(std::tuple<States...> transitionTable)
{
    ((
        std::cout << typeid(States).name() << ", "
    ), ...);
    std::cout << std::endl;
}


// int main()
// {
//     using transitionTable = TransitionTable<
//         Row<int, float, char>,
//         Row<int, float, None>,
//         Row<float, int, None>,
//         Row<float, None, None>
//     >;
//     transitionTable tt;


//     std::cout << "All possible transitions:\n";
// 	transitionTable::GetPossibleTransitions<int, float>::possibleTransitions transitions;
// 	PrintRows(transitions);


//     std::cout << "\n\nALl possible states:\n";
//     PrintStates(tt.possibleStates);


//     std::cout << "\n\nTransition gotten at runtime by current state and event:\n";
//     auto currentState = tt.runtime_get(2);
// 	// PrintRows(transitions);


//     return 0;
// }


template <typename Tuple, size_t N = 0>
void parse(const size_t idx)
{
    if (N == idx)
    {
        std::cout << typeid(std::tuple_element_t<N, Tuple>).name() << std::endl;
        return;
    }
    if constexpr (N + 1 < std::tuple_size_v<Tuple>)
    {
        parse<Tuple, N + 1>(idx);
    }
    else
    {
        throw std::runtime_error("lol");
    }
}

int main(int argv, const char** argc)
{
    using Types = std::tuple<int, float, char, bool, double>;
    while (true)
    {
        size_t idx;
        std::cin >> idx;

        parse<Types>(idx);
    }
}
