
#pragma once

#include "MSM/Frontend/State.hpp"
#include "MSM/Frontend/TransitionTable.hpp"
#include "MSM/Frontend/Row.hpp"
#include "MSM/Frontend/Transition.hpp"

#include <iostream>

namespace ExampleStateMachine
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
	using None = MSM::Front::None;

	using TransitionTable = MSM::Front::TransitionTable
	<
		MSM::Front::Row<Booting,
			MSM::Front::Transition<LocalEvent::FinishedBooting, Configuring, None, None>
		>,

		MSM::Front::Row<Configuring,
			MSM::Front::Transition<LocalEvent::FinishedConfiguring, Idle, None, None>
		>,

		MSM::Front::Row<Idle,
			MSM::Front::Transition<LocalEvent::StartGame, StartingGame, None, None>,
			MSM::Front::Transition<LocalEvent::StartGame, None, None, None>,
			MSM::Front::Transition<LocalEvent::ShutDown, ShuttingDown, None, None>
		>,

		MSM::Front::Row<StartingGame,
			MSM::Front::Transition<LocalEvent::GameStarted, Playing, None, None>,
			MSM::Front::Transition<LocalEvent::ShutDown, None, None, IgnoreEventGuard>
		>,

		MSM::Front::Row<Playing,
			MSM::Front::Transition<LocalEvent::Pause, Paused, None, None>,
			MSM::Front::Transition<LocalEvent::ExitGame, Idle, SaveGame, None>,
			MSM::Front::Transition<LocalEvent::ShutDown, ShuttingDown, SaveGame, None>
		>,

		MSM::Front::Row<Paused,
			MSM::Front::Transition<LocalEvent::Unpause, Paused, None, None>,
			MSM::Front::Transition<LocalEvent::ShutDown, ShuttingDown, SaveGame, None>
		>
	>;

} /* Namespace ExampleStateMachine */
