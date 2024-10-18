
#pragma once

#include "MSM/Frontend/StateMachine.hpp"

#include <iostream>

struct ExampleStateMachineFrontend : public MSM::Front::StateMachine
{

////////////
// Events //
////////////

	struct LocalEvent
	{
		struct FinishedBooting
		{};

		struct FinishedConfiguring
		{};

		struct StartGame
		{};

		struct GameStarted
		{};

		struct Pause
		{};

		struct Unpause
		{};

		struct ExitGame
		{};

		struct ShutDown
		{};
	};

////////////
// States //
////////////

	struct Booting : MSM::Front::State<MSM::Front::State_Type_Initial_Tag>
	{
		template<class Event, class StateMachine>
		void on_entry(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Booting entry" << std::endl;
		}

		template<class Event, class StateMachine>
		void on_exit(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Booting exit" << std::endl;
		}
	};

	struct Configuring : MSM::Front::State<>
	{
		template<class Event, class StateMachine>
		void on_entry(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Idle entry" << std::endl;
		}

		template<class Event, class StateMachine>
		void on_exit(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Idle exit" << std::endl;
		}
	};

	struct Idle : MSM::Front::State<>
	{
		template<class Event, class StateMachine>
		void on_entry(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Configuring entry" << std::endl;
		}

		template<class Event, class StateMachine>
		void on_exit(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Configuring exit" << std::endl;
		}
	};

	struct StartingGame : MSM::Front::State<>
	{
		template<class Event, class StateMachine>
		void on_entry(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Starging game entry" << std::endl;
		}

		template<class Event, class StateMachine>
		void on_exit(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Starting game exit" << std::endl;
		}
	};

	struct Playing : MSM::Front::State<>
	{
		template<class Event, class StateMachine>
		void on_entry(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Playing entry" << std::endl;
		}

		template<class Event, class StateMachine>
		void on_exit(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Playing exit" << std::endl;
		}
	};

	struct Paused : MSM::Front::State<>
	{
		template<class Event, class StateMachine>
		void on_entry(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Pause entry" << std::endl;
		}

		template<class Event, class StateMachine>
		void on_exit(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Pause exit" << std::endl;
		}
	};

	struct ShuttingDown : MSM::Front::State<MSM::Front::State_Type_Final_Tag>
	{
		template<class Event, class StateMachine>
		void on_entry(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Exit game entry" << std::endl;
		}

		template<class Event, class StateMachine>
		void on_exit(const Event& evt, StateMachine& fsm)
		{
			std::cout << "Exit game exit" << std::endl;
		}
	};

/////////////
// Actions //
/////////////

	struct SaveGame
	{
		template <class OriginState, class Event, class StateMachine>
		void operator()(const OriginState& ost, const Event& evt, StateMachine& fsm)
		{
			std::cout << "Saving Game" << std::endl;
		}
	};

////////////
// Guards //
////////////

	/*!
	 * @brief This is just a typedef to make clear that we are ignoring an event.
	*/
	using IgnoreEventGuard = MSM::Front::None;

/////////////////////
// TransitionTable //
/////////////////////

	using TransitionTable = MSM::Front::Transitiontable<
		MSM::Front::TTRow<Booting, LocalEvent::FinishedBooting, Configuring, MSM::Front::None, MSM::Front::None>,

		MSM::Front::TTRow<Configuring, LocalEvent::FinishedConfiguring, Idle, MSM::Front::None, MSM::Front::None>,

		MSM::Front::TTRow<Idle, LocalEvent::StartGame, StartingGame, MSM::Front::None, MSM::Front::None>,
		MSM::Front::TTRow<Idle, LocalEvent::StartGame, MSM::Front::None, MSM::Front::None, MSM::Front::None>,
		MSM::Front::TTRow<Idle, LocalEvent::ShutDown, ShuttingDown, MSM::Front::None, MSM::Front::None>,

		MSM::Front::TTRow<StartingGame, LocalEvent::GameStarted, Playing, MSM::Front::None, MSM::Front::None>,
		MSM::Front::TTRow<StartingGame, LocalEvent::ShutDown, MSM::Front::None, MSM::Front::None, IgnoreEventGuard>,

		MSM::Front::TTRow<Playing, LocalEvent::Pause, Paused, MSM::Front::None, MSM::Front::None>,
		MSM::Front::TTRow<Playing, LocalEvent::ExitGame, Idle, SaveGame, MSM::Front::None>,
		MSM::Front::TTRow<Playing, LocalEvent::ShutDown, ShuttingDown, SaveGame, MSM::Front::None>,

		MSM::Front::TTRow<Paused, LocalEvent::Unpause, Paused, MSM::Front::None, MSM::Front::None>,
		MSM::Front::TTRow<Paused, LocalEvent::ShutDown, ShuttingDown, SaveGame, MSM::Front::None>
	>;

};
