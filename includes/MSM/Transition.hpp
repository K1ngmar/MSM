#pragma once

#include "MSM/TransitionTraits.hpp"

namespace MSM {

    /*!
     * @brief Special type to use when you want to use a slot for the transition.
    */
    struct None
    {
    };

    // Transition<Event, Target, Action, Guard>
    template<class EventType, class TargetStateType, class ActionType, class GuardType>
    struct Transition
    {
        using TransitionType_Tag = MSM::Normal_Transition_With_Action_And_Guard_Tag;
    
		using Event = EventType;
		using TargetState = TargetStateType;
		using Action = ActionType;
		using Guard = GuardType;

        static void ExecuteAction(const Event& evt)
        {
            Action()(evt);
        }

        static bool ExecuteGuard(const Event& evt)
        {
            return Guard()(evt);
        }
    };

    // Transition<Event, Target, None, None>
    template<class EventType, class TargetStateType>
    struct Transition<EventType, TargetStateType, None, None>
    {
        using TransitionType_Tag = MSM::Normal_Transition_Tag;

		using Event = EventType;
		using TargetState = TargetStateType;
    };

    // Transition<Event, Target, Action, None>
    template<class EventType, class TargetStateType, class ActionType>
    struct Transition<EventType, TargetStateType, ActionType, None>
    {
        using TransitionType_Tag = MSM::Normal_Transition_With_Action_Tag;

		using Event = EventType;
		using TargetState = TargetStateType;
		using Action = ActionType;

        static void ExecuteAction(const Event& evt)
        {
            Action()(evt);
        }
    };

    // Transition<Event, Target, None, Guard>
    template<class EventType, class TargetStateType, class GuardType>
    struct Transition<EventType, TargetStateType, None, GuardType>
    {
        using TransitionType_Tag = MSM::Normal_Transition_With_Guard_Tag;

		using Event = EventType;
		using TargetState = TargetStateType;
		using Guard = GuardType;

        static bool ExecuteGuard(const Event& evt)
        {
            return Guard()(evt);
        }
    };

    // Transition<Event, None, Action, None>
    template<class EventType, class ActionType>
    struct Transition<EventType, None, ActionType, None>
    {
        using TransitionType_Tag = MSM::Internal_Transition_Tag;

		using Event = EventType;
		using Action = ActionType;

        static void ExecuteAction(const Event& evt)
        {
            Action()(evt);
        }
    };

    // Transition<Event, None, Action, Guard>
    template<class EventType, class ActionType, class GuardType>
    struct Transition<EventType, None, ActionType, GuardType>
    {
        using TransitionType_Tag = MSM::Internal_Transition_With_Guard_Tag;

		using Event = EventType;
		using Action = ActionType;
		using Guard = GuardType;

        static void ExecuteAction(const Event& evt)
        {
            Action()(evt);
        }

        static bool ExecuteGuard(const Event& evt)
        {
            return Guard()(evt);
        }
    };

    // Transition<Event, None, None, Guard>
    template<class EventType, class GuardType>
    struct Transition<EventType, None, None, GuardType>
    {
        using TransitionType_Tag = MSM::Empty_Transition_With_Guard_Tag;

		using Event = EventType;
		using Guard = GuardType;

        static bool ExecuteGuard(const Event& evt)
        {
            return Guard()(evt);
        }
    };

    // Transition<Event, None, None, None>
    template<class EventType>
    struct Transition<EventType, None, None, None>
    {
        using TransitionType_Tag = MSM::Empty_Transition_Tag;
    
		using Event = EventType;
	};

} /* End of namespace MSM */
