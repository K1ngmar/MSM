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
                if (CurrentTransition::ExecuteGuard(event))
                {
                    std::cout << "woop performing transition:\n";
                    std::cout << typeid(OriginState).name() << ", " << typeid(typename CurrentTransition::Event).name();
                    std::cout << typeid(typename CurrentTransition::Guard).name() << "\n";
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
