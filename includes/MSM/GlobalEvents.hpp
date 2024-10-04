
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



TransitionTable<

row<Initializing, GlobalEvents::Initialized, Idle, none, none>,

row<Idle, GlobalEvents::Shutdown, ShuttingDown, none, none>
row<Idle, GlobalEvents::StartingGame, Starting, none, none>

>
