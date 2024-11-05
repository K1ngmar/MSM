#include "ExampleStateMachine.hpp"
#include "MSM/StateMachine.hpp"

#include <thread>

int main(void)
{
    MSM::StateMachine<ExampleStateMachine::TransitionTable> fsm;

	// fsm.Start();

	// fsm.ProcessEvent(ExampleStateMachineFrontend::LocalEvent::FinishedBooting());
	// std::this_thread::sleep_for(std::chrono::seconds(2));
	// fsm.ProcessEvent(ExampleStateMachineFrontend::LocalEvent::FinishedConfiguring());
	// std::this_thread::sleep_for(std::chrono::seconds(2));
	// fsm.ProcessEvent(ExampleStateMachineFrontend::LocalEvent::StartGame());
	// std::this_thread::sleep_for(std::chrono::seconds(2));
	// fsm.ProcessEvent(ExampleStateMachineFrontend::LocalEvent::Pause());
	// std::this_thread::sleep_for(std::chrono::seconds(2));
	// fsm.ProcessEvent(ExampleStateMachineFrontend::LocalEvent::Unpause());
	// std::this_thread::sleep_for(std::chrono::seconds(2));
	// fsm.ProcessEvent(ExampleStateMachineFrontend::LocalEvent::ExitGame());
	// std::this_thread::sleep_for(std::chrono::seconds(2));
	// fsm.ProcessEvent(ExampleStateMachineFrontend::LocalEvent::ShutDown());

	// fsm.Stop();

    return 0;
}