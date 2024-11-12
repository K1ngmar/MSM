#pragma once

#include "MSM/TransitionTable.hpp"

#include "MSM/State.hpp"

namespace MSM {

    namespace InternalEvents
    {
        /*!
         * @brief Emitted to the OnEntry of the initial states, if defined, when Start() is called on the statemachine.
        */
        struct StateMachineStarting
        {};

        /*!
         * @brief Emitted to the OnExit of the current states, if defined, when Stop() is called on the statemachine.
        */
        struct StateMachineStopping
        {};
    }

/*!
 * @brief The actual implementation of the statemachine based on the frontend transition table. 
*/
template<class TransitionTableType>
class StateMachine
{
private:

	using TransitionTable = TransitionTableType;

    size_t currentStateId; /*!< -. */
    bool isStatemachineRunning; /*!< -. */

	/*!
	 * @brief Tries to perform a transition based on the current state and incomming event.
	*/
	template <class Event, size_t N = 0>
	void ExecuteTransition(const Event& event);

    /*!
     * @brief Tries to execute the transition in the selected row based on the event.
    */
	template <size_t RowIndex, size_t N = 0, class Event>
	void ExecuteTransitionInRow(const Event& event);

    /*!
     * @brief -.
    */
    template <class Event, size_t N = 0>
    void ExecuteOnExitOfCurrentStateIfDefined(const Event& event);

public:

    /*!
     * @brief -.
    */
    bool IsStatemachineRunning() const;

    /*!
     * @brief -.
    */
    size_t CurrentStateId() const;

    /*!
     * @brief Starts the state machine.
    */
    void Start();

    /*!
     * @brief Stops the statemachine.
    */
    void Stop();

    /*!
     * @brief Processes event, tries to execute transition defined in the transition table.
     * @return True if the transition was enqueued and the statemachine was running.
    */
    template <class Event>
    bool ProcessEvent(const Event& e);
};


} /* End of namespace MSM */

#include "StateMachine.ipp"
