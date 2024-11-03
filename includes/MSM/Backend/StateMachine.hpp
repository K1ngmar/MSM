#pragma once

#include "MSM/Backend/TransitionTable.hpp"

#include "MSM/Frontend/State.hpp"

namespace MSM { namespace Back {

    /*!
     * @brief The actual implementation of the statemachine based on the frontend transition table. 
    */
    template<class TransitionTableFront>
    class StateMachine
    {
    private:
    
      using TransitionTable = MSM::Back::TransitionTable<typename TransitionTableFront::AllRowsInATuple>;

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

} /* End of namespace Back */

} /* End of namespace MSM */
