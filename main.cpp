
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

template <class OriginState_, class Event_, class ...Transitions>
struct Row
{
    using OriginState = OriginState_;
    using Event = Event_;
    
    static const std::tuple<Transitions...> transitions;
};

template <class DestinationState, class Action, class Guard>
struct Transition
{
    using Tag = char;

    using Dest = DestinationState;
    using Act = Action;
    using Grd = Guard;
};

template <class DestinationState, class Action>
struct Transition<DestinationState, Action, None>
{
    using Tag = int;

    using Dest = DestinationState;
    using Act = Action;
    using Grd = None;
};

template <class DestinationState, class Guard>
struct Transition<DestinationState, None, Guard>
{
    using Tag = size_t;

    using Dest = DestinationState;
    using Act = None;
    using Grd = Guard;
};

template <class DestinationState>
struct Transition<DestinationState, None, None>
{
    using Tag = float;

    using Dest = DestinationState;
    using Act = None;
    using Grd = None;
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
				std::is_same_v<typename Rows::OriginState, State> && std::is_same_v<typename Rows::Event, Event>,
				std::tuple<Rows>,
				std::tuple<>
			>::type...
		>;
	};

    using AllRowsInATuple = tuple_cat_t<std::tuple<Rows>...>;
    AllRowsInATuple allRowsInATuple;

    template <typename Event, size_t N = 0>
    void get_transition(const size_t currentStateId)
    {
        if (N == currentStateId)
        {
            std::cout << typeid(std::tuple_element_t<N, AllRowsInATuple>::OriginState).name() << std::endl;
            return;
        }
        if constexpr (N + 1 < std::tuple_size_v<AllRowsInATuple>)
        {
            get_transition<N + 1>(currentStateId);
        }
        else
        {
            throw std::runtime_error("lol");
        }
    }

};

// template<class ...Rows>
// void PrintTransition(std::tuple<Rows...> transitionTable)
// {
//     ((
//         std::cout << typeid(typename Rows::OriginState).name() << ", " <<
//                      typeid(typename Rows::Event).name() << std::endl
//     ), ...);
// }

template<class ...Transitions>
void PrintTransitions(const std::tuple<Transitions...> trs) // Why in the world cant this take a reference?
{
    ((
        std::cout << "Transition: " << typeid(typename Transitions::Dest).name() << ", " <<
        typeid(typename Transitions::Act).name() << ", " <<
        typeid(typename Transitions::Grd).name() << ", " << "\n"
    ), ...);
}

template<class ...Rows>
void PrintRows(std::tuple<Rows...> transitionTable)
{
    ([]
    {
        std::cout << "\nRow: ";
        std::cout << typeid(typename Rows::OriginState).name() << ", " << typeid(typename Rows::Event).name() << "\n";
        PrintTransitions(Rows::transitions);
        std::cout << "\n";
    }(), ...);
    std::cout << std::endl;
}


int main()
{
    using transitionTable = TransitionTable<
        Row<int, float, Transition<char, bool, double>,
                        Transition<char, char, None> >,
        
        Row<float, int, Transition<char, bool, double>,
                        Transition<float, None, None> >
    >;
    transitionTable tt;


    // std::cout << "All possible transitions for <int, float>:\n";
	// transitionTable::GetPossibleTransitions<int, float>::possibleTransitions transitions;
	// PrintTransition(transitions);


    std::cout << "\n\nAll Rows:\n";
    PrintRows(tt.allRowsInATuple);


    std::cout << "\n\nTransition gotten at runtime by current state and event:\n";
	// PrintRows(transitions);


    return 0;
}


// template <typename Tuple, size_t N = 0>
// void parse(const size_t idx)
// {
//     if (N == idx)
//     {
//         std::cout << typeid(std::tuple_element_t<N, Tuple>).name() << std::endl;
//         return;
//     }
//     if constexpr (N + 1 < std::tuple_size_v<Tuple>)
//     {
//         parse<Tuple, N + 1>(idx);
//     }
//     else
//     {
//         throw std::runtime_error("lol");
//     }
// }

// int main(int argv, const char** argc)
// {
//     using Types = std::tuple<int, float, char, bool, double>;
//     while (true)
//     {
//         size_t idx;
//         std::cin >> idx;

//         parse<Types>(idx);
//     }
// }
