#pragma once

#include "FrontEnd/State.hpp"

namespace MSM
{
    /*!
     * The actual implementation of the statemachine based on the frontend transition table. 
    */
    template<MSM::TransitionTable FrontEnd>
    class StateMachine<FrontEnd>
    {
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

        /*!
        * @brief When implementing a State machine overload this function to set the initial state when the state machine is constructed.
        */
        virtual State InitialState() const = 0;

    public:

        const State& CurrentState() const;

        template<EventType Event>
        const ProcessEvent(const Event& evt);

    };

} /* End of namespace MSM*/
