#pragma once

#include "FrontEnd/State.hpp"

namespace MSM
{
    /*!
     * The actual implementation of the statemachine based on the frontend transition table. 
    */
    template<class StateMachineFrontEnd>
    class StateMachine<StateMachineFrontEnd>
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
        void ProcessEvent(const Event& e);

    };

} /* End of namespace MSM*/
