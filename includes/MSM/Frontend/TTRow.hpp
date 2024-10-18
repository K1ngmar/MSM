#pragma once

namespace MSM
{

namespace Front
{
    /*!
     * @brief Special type to use when you want to use a slot for the transition.
    */
    struct None
    {
    };

    // Row<Origin, Event, Target, Action, Guard>
    template<class OriginStateType, class EventType, class TargetStateType, class ActionType, class GuardType>
    struct TTRow
    {
        using Row_Type_Tag = Normal_Transition_With_Action_And_Guard_Tag;
    
		using OriginState = OriginStateType;
		using Event = EventType;
		using TargetState = TargetStateType;
		using Action = ActionType;
		using Guard = GuardType;


        template <class Fsm>
        static void ExecuteAction(Fsm& fsm, const Event& evt, TargetState& tgs)
        {
            Action()(fsm, evt, tgs);
        }

        template <class Fsm>
        static bool ExecuteGuard(Fsm& fsm, const Event& evt, TargetState& tgs)
        {
            return Guard()(fsm, evt, tgs);
        }
    };

    // Row<Origin, Event, Target, None, None>
    template<class OriginState, class Event, class TargetState>
    struct TTRow<OriginState, Event, TargetState, None, None>
    {
        using Row_Type_Tag = Normal_Transition_Tag;

		using OriginState = OriginStateType;
		using Event = EventType;
		using TargetState = TargetStateType;
    };

    // Row<Origin, Event, Target, Action, None>
    template<class OriginState, class Event, class TargetState, class Action>
    struct TTRow<OriginState, Event, TargetState, Action, None>
    {
        using Row_Type_Tag = Normal_Transition_With_Action_Tag;

		using OriginState = OriginStateType;
		using Event = EventType;
		using TargetState = TargetStateType;
		using Action = ActionType;

        template <class Fsm>
        static void ExecuteAction(Fsm& fsm, const Event& evt, TargetState& tgs)
        {
            Action()(fsm, evt, tgs);
        }
    };

    // Row<Origin, Event, Target, None, Guard>
    template<class OriginState, class Event, class TargetState, class Guard>
    struct TTRow<OriginState, Event, TargetState, None, Guard>
    {
        using Row_Type_Tag = Normal_Transition_With_Guard_Tag;

		using OriginState = OriginStateType;
		using Event = EventType;
		using TargetState = TargetStateType;
		using Guard = GuardType;

        template <class Fsm>
        static bool ExecuteGuard(Fsm& fsm, const Event& evt, TargetState& tgs)
        {
            return Guard()(fsm, evt, tgs);
        }
    };

    // Row<Origin, Event, None, Action, None>
    template<class OriginState, class Event, class Action>
    struct TTRow<OriginState, Event, None, Action, None>
    {
        using Row_Type_Tag = Internal_Transition_Tag;

		using OriginState = OriginStateType;
		using Event = EventType;
		using Action = ActionType;

        template <class Fsm>
        static void ExecuteAction(Fsm& fsm, const Event& evt, TargetState& tgs)
        {
            Action()(fsm, evt, tgs);
        }
    };

    // Row<Origin, Event, None, Action, Guard>
    template<class OriginState, class Event, class Action, class Guard>
    struct TTRow<OriginState, Event, None, Action, Guard>
    {
        using Row_Type_Tag = Internal_Transition_With_Guard_Tag;

		using OriginState = OriginStateType;
		using Event = EventType;
		using Action = ActionType;
		using Guard = GuardType;

        template <class Fsm>
        static void ExecuteAction(Fsm& fsm, const Event& evt, TargetState& tgs)
        {
            Action()(fsm, evt, tgs);
        }

        template <class Fsm>
        static bool ExecuteGuard(Fsm& fsm, const Event& evt, TargetState& tgs)
        {
            return Guard()(fsm, evt, tgs);
        }
    };

    // Row<Origin, Event, None, None, Guard>
    template<class OriginState, class Event, class Guard>
    struct TTRow<OriginState, Event, None, None, Guard>
    {
        using Row_Type_Tag = Empty_Transition_With_Guard_Tag;

		using OriginState = OriginStateType;
		using Event = EventType;
		using Guard = GuardType;

        template <class Fsm>
        static bool ExecuteGuard(Fsm& fsm, const Event& evt, TargetState& tgs)
        {
            return Guard()(fsm, evt, tgs);
        }
    };

    // Row<Origin, Event, None, None, None>
    template<class OriginState, class Event>
    struct TTRow<OriginState, Event, None, None, None>
    {
        using Row_Type_Tag = Empty_Transition_Tag;
    
		using OriginState = OriginStateType;
		using Event = EventType;
	};

} /* End of namespace Front*/

} /* End of namespace MSM */
