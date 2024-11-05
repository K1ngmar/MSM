#pragma once

#include "MSM/TransitionTable.hpp"

#include "MSM/State.hpp"

namespace MSM {

struct StateMachineStarting
{};

/*!
 * @brief The actual implementation of the statemachine based on the frontend transition table. 
*/
template<class TransitionTableType>
class StateMachine
{
private:

    size_t currentStateId; /*!< -. */

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
