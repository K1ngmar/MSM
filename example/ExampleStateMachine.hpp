
#pragma once

#include "MSM/State.hpp"
#include "MSM/TransitionTable.hpp"
#include "MSM/Row.hpp"
#include "MSM/Transition.hpp"

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

	struct Booting : MSM::State<MSM::State_Type_Initial_Tag>
	{
		template<class Event>
		static void on_entry(const Event& evt)
		{
			std::cout << "Booting entry" << std::endl;
		}

		template<class Event>
		static void on_exit(const Event& evt)
		{
			std::cout << "Booting exit" << std::endl;
		}
	};

	struct Configuring : MSM::State<>
	{
		template<class Event>
		static void on_entry(const Event& evt)
		{
			std::cout << "Idle entry" << std::endl;
		}

		template<class Event>
		static void on_exit(const Event& evt)
		{
			std::cout << "Idle exit" << std::endl;
		}
	};

	struct Idle : MSM::State<>
	{
		template<class Event>
		static void on_entry(const Event& evt)
		{
			std::cout << "Configuring entry" << std::endl;
		}

		template<class Event>
		static void on_exit(const Event& evt)
		{
			std::cout << "Configuring exit" << std::endl;
		}
	};

	struct StartingGame : MSM::State<>
	{
		template<class Event>
		static void on_entry(const Event& evt)
		{
			std::cout << "Starging game entry" << std::endl;
		}

		template<class Event>
		static void on_exit(const Event& evt)
		{
			std::cout << "Starting game exit" << std::endl;
		}
	};

	struct Playing : MSM::State<>
	{
		template<class Event>
		static void on_entry(const Event& evt)
		{
			std::cout << "Playing entry" << std::endl;
		}

		template<class Event>
		static void on_exit(const Event& evt)
		{
			std::cout << "Playing exit" << std::endl;
		}
	};

	struct Paused : MSM::State<>
	{
		template<class Event>
		static void on_entry(const Event& evt)
		{
			std::cout << "Pause entry" << std::endl;
		}

		template<class Event>
		static void on_exit(const Event& evt)
		{
			std::cout << "Pause exit" << std::endl;
		}
	};

	struct ShuttingDown : MSM::State<MSM::State_Type_Final_Tag>
	{
		template<class Event>
		static void on_entry(const Event& evt)
		{
			std::cout << "Exit game entry" << std::endl;
		}

		template<class Event>
		static void on_exit(const Event& evt)
		{
			std::cout << "Exit game exit" << std::endl;
		}
	};

/////////////
// Actions //
/////////////

	struct SaveGame
	{
		template <class OriginState, class Event>
		void operator()(const OriginState& ost, const Event& evt)
		{
			std::cout << "Saving Game" << std::endl;
		}
	};

////////////
// Guards //
////////////

	struct TESTGUARD
	{
		template <class Event>
		bool operator()(const Event& evt)
		{
			std::cout << "EXECUTING GUARD, YEETTTT" << std::endl;
			return true;
		}
	};

	/*!
	 * @brief This is just a typedef to make clear that we are ignoring an event.
	*/
	using IgnoreEventGuard = MSM::None;

/////////////////////
// TransitionTable //
/////////////////////
	using None = MSM::None;

	using TransitionTable = MSM::TransitionTable
	<
		MSM::Row<Booting,
			MSM::Transition<LocalEvent::FinishedBooting, Configuring, None, TESTGUARD>
		>,

		MSM::Row<Configuring,
			MSM::Transition<LocalEvent::FinishedConfiguring, Idle, None, None>
		>,

		MSM::Row<Idle,
			MSM::Transition<LocalEvent::StartGame, StartingGame, None, None>,
			MSM::Transition<LocalEvent::StartGame, None, None, None>,
			MSM::Transition<LocalEvent::ShutDown, ShuttingDown, None, None>
		>,

		MSM::Row<StartingGame,
			MSM::Transition<LocalEvent::GameStarted, Playing, None, None>,
			MSM::Transition<LocalEvent::ShutDown, None, None, IgnoreEventGuard>
		>,

		MSM::Row<Playing,
			MSM::Transition<LocalEvent::Pause, Paused, None, None>,
			MSM::Transition<LocalEvent::ExitGame, Idle, SaveGame, None>,
			MSM::Transition<LocalEvent::ShutDown, ShuttingDown, SaveGame, None>
		>,

		MSM::Row<Paused,
			MSM::Transition<LocalEvent::Unpause, Paused, None, None>,
			MSM::Transition<LocalEvent::ShutDown, ShuttingDown, SaveGame, None>
		>
	>;

} /* Namespace ExampleStateMachine */
