
#pragma once

#include <tuple>

struct GlobalEvents
{
    struct Booting
    {

    };

	struct Initialized;

    struct Idle
    {

    };

    struct Busy
    {
        
    };

};

struct GlobalState {};

struct Initializing : GlobalState {};

struct Idle : GlobalState {

	void on_entry()
	{

	}

	void on_exit()
	{

	}

};

struct none {};

template<class OriginState, class Event, class DestinationState, class TransitionFunction, class Guard>
using row = std::tuple<OriginState, Event, DestinationState, TransitionFunction, Guard>;

template<class ...Rows>
class TransitionTable
{
	std::tuple<Rows...> table;
	const size_t numberOfTransitions = std::tuple_size<std::tuple<Rows...>

	TransitionTable()
	{
		for (size_t i = 0; i < std::tuple_size(table))
	}

}

TransitionTable<

row<Initializing, GlobalEvents::Initialized, Idle, none, none>,

row<Idle, GlobalEvents::Shutdown, ShuttingDown, none, none>
row<Idle, GlobalEvents::StartingGame, Starting, none, none>

>
