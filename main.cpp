
#include "MSM/backend/Utility/Utility.hpp"

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

template <class OriginState_, class ...Transitions>
struct Row
{
    using OriginState = OriginState_;
    
    static const std::tuple<Transitions...> transitions;
};

template <class Event, class DestinationState, class Action, class Guard>
struct Transition
{
    using Tag = char;

	using Evt = Event;
    using Dest = DestinationState;
    using Act = Action;
    using Grd = Guard;
};

template <class Event, class DestinationState, class Action>
struct Transition<Event, DestinationState, Action, None>
{
    using Tag = int;

	using Evt = Event;
    using Dest = DestinationState;
    using Act = Action;
    using Grd = None;
};

template <class Event, class DestinationState, class Guard>
struct Transition<Event, DestinationState, None, Guard>
{
    using Tag = size_t;

	using Evt = Event;
    using Dest = DestinationState;
    using Act = None;
    using Grd = Guard;
};

template <class Event, class DestinationState>
struct Transition<Event, DestinationState, None, None>
{
    using Tag = float;

	using Evt = Event;
    using Dest = DestinationState;
    using Act = None;
    using Grd = None;
};


template<typename ...Rows>
using tuple_cat_t = decltype(std::tuple_cat(std::declval<Rows>()...));

template<class ...Rows>
struct TransitionTable
{
    using AllRowsInATuple = tuple_cat_t<std::tuple<Rows>...>;
    AllRowsInATuple allRowsInATuple;

    template <class Event, size_t N = 0>
    void get_transition(const size_t currentStateId)
    {
        if (N == currentStateId)
        {
    		PrintTransitions(std::tuple_element_t<N, AllRowsInATuple>::transitions);
            return;
        }
        if constexpr (N + 1 < std::tuple_size_v<AllRowsInATuple>)
        {
            get_transition<Event, N + 1>(currentStateId);
        }
        else
        {
			throw std::runtime_error("lol");
        }
    }
};

template<class ...Transitions>
void PrintTransitions(const std::tuple<Transitions...> trs) // Why in the world cant this take a reference?
{
    ((
        std::cout << "Possible transition: " <<
		typeid(typename Transitions::Evt).name() << ", " <<
		typeid(typename Transitions::Dest).name() << ", " <<
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
        std::cout << typeid(typename Rows::OriginState).name() << "\n";
        PrintTransitions(Rows::transitions);
        std::cout << "\n";
    }(), ...);
    std::cout << std::endl;
}


int main(int argc, char** argv)
{
    using transitionTable = TransitionTable<
        Row<int, Transition<float, char, bool, double>,
            	 Transition<float, char, char, None> >,
        
        Row<float, Transition<int, char, bool, double>,
                   Transition<int, float, None, None>,
				   Transition<float, char, bool, double>,
                   Transition<float, float, None, None> >,

		Row<double, Transition<int, char, bool, double>,
                	Transition<int, float, None, char>,
					Transition<char, float, None, char> >,
		
		Row<char, Transition<int, char, bool, double>,
                	Transition<int, float, None, char>,
					Transition<char, None, None, None> >
    >;
    transitionTable tt;


    // std::cout << "All possible transitions for <int, float>:\n";
	// transitionTable::GetPossibleTransitions<int, float>::possibleTransitions transitions;
	// PrintTransition(transitions);


    // std::cout << "\n\nAll Rows:\n";
    // PrintRows(tt.allRowsInATuple);


    std::cout << "\n\nTransition gotten at runtime by current state and event:\n";
	tt.get_transition<float>(argc);


    return 0;
}
