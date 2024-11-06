#pragma once

namespace MSM {

    /*!
     * @brief A row is a combination of a OriginState and al list of all transitions possible from this state.
    */
    template <class OriginStateType, class ...TransitionTypes>
    struct Row
    {
        using OriginState = OriginStateType;
        
        using Transitions = std::tuple<TransitionTypes...>;

        template <size_t N = 0, class Event>
        static void ExecuteTransition(const Event& event)
        {
            using CurrentTransition = std::tuple_element_t<N, Transitions>;
            if constexpr (std::is_same_v<typename CurrentTransition::Event, Event>)
            {
                bool performTransition = true;
                if constexpr (requires { CurrentTransition::ExecuteGuard(event); })
                {
                    performTransition = CurrentTransition::ExecuteGuard(event);
                }
                if (performTransition)
                {
                    if constexpr (requires { OriginState::on_exit(event); })
                    {
                        std::cout << "Performing on_exit of current state:" + std::string(typeid(OriginState).name()) + "\n";
                        OriginState::on_exit(event);
                    }
                    if constexpr (requires { CurrentTransition::ExecuteAction(event); })
                    {
                        std::cout << "Performing action:\n";
                        CurrentTransition::ExecuteAction(event);
                    }
                    if constexpr (requires { CurrentTransition::TargetState::on_entry(event); })
                    {
                        std::cout << "Performing on_entry of target state: " + std::string(typeid(typename CurrentTransition::TargetState).name()) + "\n";
                        CurrentTransition::TargetState::on_entry(event);
                    }
                    return;
                }
            }
            if constexpr (N + 1 < std::tuple_size_v<Transitions>)
            {
                ExecuteTransition<N + 1>(event);
            }
            else
            {
                throw std::runtime_error(
                    std::string("Broken state machine, no transition implemented: ") +
                    typeid(OriginState).name() + ", " + typeid(Event).name()
                );
            }
        }
    };

} /* End of namespace MSM */
