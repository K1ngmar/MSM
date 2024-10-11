#pragma once

#include "FrontEnd/State.hpp"

namespace MSM
{

    /*!
    * The actual 
    */
    class StateMachine
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
        * @brief When implementing a State machine overload this function to set the initial state for when the state machine is constructed.
        */
        virtual State InitialState() const = 0;

    public:

        const State& CurrentState() const;

    };

} /* End of namespace MSM*/
