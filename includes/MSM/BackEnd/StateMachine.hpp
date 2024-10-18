#pragma once

#include "Frontend/State.hpp"

namespace MSM { namespace Back {

    /*!
     * @brief The actual implementation of the statemachine based on the frontend transition table. 
    */
    template<class StateMachineFrontend>
    class StateMachine
    {
		using Frontend = StateMachineFrontend;
		using TransitionTable = Frontend::TransitionTable;

    private:

        State currentState; /*!< -. */

        /*!
         * @brief -.
        */
        StateMachine();

        /*!
        * @brief -.
        */
        void SetStateActive(const State& incommingState);

    public:

        /*!
         * @brief -.
        */
        const State& CurrentState() const;

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
        void ProcessEvent(const Event& e)
		{
			TransitionTable::GetPossibleTransitions<State, Event>()
		}

    };

} /* End of namespace Back */

} /* End of namespace MSM */
