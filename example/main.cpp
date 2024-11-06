#include "ExampleStateMachine.hpp"
#include "MSM/StateMachine.hpp"

#include <thread>

int main(void)
{
    MSM::StateMachine<ExampleStateMachine::TransitionTable> fsm;

	fsm.Start();

	fsm.ProcessEvent(ExampleStateMachine::LocalEvent::FinishedBooting());
	std::this_thread::sleep_for(std::chrono::seconds(2));
	// fsm.ProcessEvent(ExampleStateMachine::LocalEvent::FinishedConfiguring());
	// std::this_thread::sleep_for(std::chrono::seconds(2));
	// fsm.ProcessEvent(ExampleStateMachine::LocalEvent::StartGame());
	// std::this_thread::sleep_for(std::chrono::seconds(2));
	// fsm.ProcessEvent(ExampleStateMachine::LocalEvent::Pause());
	// std::this_thread::sleep_for(std::chrono::seconds(2));
	// fsm.ProcessEvent(ExampleStateMachine::LocalEvent::Unpause());
	// std::this_thread::sleep_for(std::chrono::seconds(2));
	// fsm.ProcessEvent(ExampleStateMachine::LocalEvent::ExitGame());
	// std::this_thread::sleep_for(std::chrono::seconds(2));
	// fsm.ProcessEvent(ExampleStateMachine::LocalEvent::ShutDown());

	// fsm.Stop();

    return 0;
}