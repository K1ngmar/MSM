#pragma once

#include "MSM/TransitionTable.hpp"
#include "MSM/State.hpp"
#include "MSM/Utility/TupTility.hpp"

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

    size_t currentStateId = 0; /*!< -. */
    bool isStatemachineRunning = false; /*!< -. */
    bool isExecutingTransition = false; /*!< -. */

    /*!
	 * All events added with ProcessEvent, get temporarily stored here.
	 * If a transition is ongoing it will check what transition should be used next.
	*/
	MSM::Utility::ArrayOfQueueOfType<typename TransitionTable::AllPossibleEvents> eventBuffer;

	/*!
	 * Stores the order of the events to process next.
	 * Stored in this queue is the id of the next event to process from the eventBuffer.
	*/
	std::queue<size_t> eventToProcessOrder;

	/*!
	 * @brief Tries to perform a transition based on the current state and incomming event.
	*/
	template <class Event, size_t N = 0>
	void ExecuteTransition(const Event& event);

    /*!
     * @brief Tries to execute all enqueued transitions.
    */
    void ExecuteTransitionsFromQueue();

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

    /*!
     * @brief Clears all enqueued events.
    */
    void ClearQueue();

public:

    /*!
     * @brief Checks wheter there are any events enqueued.
     * @return
    */
    bool IsEventEnqueued() const;

    /*!
     * @brief -.
     * @return
    */
    bool IsStatemachineRunning() const;

    /*!
     * @brief -.
     * @return
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
