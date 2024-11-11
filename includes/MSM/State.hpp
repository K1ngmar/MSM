#pragma once

#include "MSM/Utility/TypeTraits.hpp"

namespace MSM {

    /*!
     * @brief Tag to use for the inital state, no transition to this state will be possible.
    */
    struct State_Type_Initial_Tag {};

    /*!
     * @brief Tag to use for normal states.
    */
    struct State_Type_Normal_Tag {};

    /*!
     * @brief Tag to use for the terminal state, no state transition from this state will be possible.
    */
    struct State_Type_Final_Tag {};

    /*!
     * @brief -.
    */
    template <class StateTypeTag = State_Type_Normal_Tag>
    struct State
    {
        using StateType = StateTypeTag;
    };

    /*!
     * @brief Executes the OnEntry function of state if it is defined.
    */
    template<class State, class Event>
    void ExecuteOnEntryIfDefined(const Event& e)
    {
        if constexpr (requires { State::OnEntry(e); })
        {
            State::OnEntry(e);
        }
    }

    /*!
     * @brief Executes the OnExit function of state if it is defined.
    */
    template<class State, class Event>
    void ExecuteOnExitIfDefined(const Event& e)
    {
        if constexpr (requires { State::OnExit(e); })
        {
            State::OnExit(e);
        }
    }

} /* End namespace MSM */
