#pragma once

namespace MSM
{
    /*!
     * @brief 
    */
    template <Template Derived>
    class State<Derived>
    {
        
        /*!
         * @brief Function to execute on entry of state.
         * @param Event
         * @param DestinationState
        */
        template<class FSM, State OriginState, Event IncommingEvent, State DestinationState, Action TransitionAction, Action TransitionGuard>
        virtual on_entry(FSM& fsm, const OriginState& ost, const IncommingEvent& evt, const DestinationState& dst, cosnt TransitionAction& ta, const TransitionGuard& tg) = 0;

        template<class FSM, State OriginState, Event IncommingEvent, State DestinationState, Action TransitionAction, Action TransitionGuard>
        virtual on_entry(FSM& fsm, const OriginState& ost, const IncommingEvent& evt, const DestinationState& dst, cosnt TransitionAction& ta, const TransitionGuard& tg) = 0;
    };

} /* End namespace MSM */
