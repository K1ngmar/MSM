#pragma once

#include "MSM/TransitionTable.hpp"

#include "MSM/State.hpp"

namespace MSM {

    namespace InternalEvents
    {
        /*!
         * @brief Emitted when the statemachine is starting, to the on entry of the first state if it is defined.
        */
        struct StateMachineStarting
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

public:

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
    */
    template <class Event>
    void ProcessEvent(const Event& e);
};


} /* End of namespace MSM */

#include "StateMachine.ipp"
