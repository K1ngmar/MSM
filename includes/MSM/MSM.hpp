
#pragma once

#include "FrontEnd/TTRow.hpp"
#include "FrontEnd/Event.hpp"

namespace MSM
{

	/*!
	 * @brief Type to use when you dont want anything on that slot tof the TTRow.
	*/
	class None : public State<>
	{
		/*!
		 * @brief Defines empty on entry.
		*/
		template<class FSM, State OriginState, Event IncommingEvent, State DestinationState, Action TransitionAction, Action TransitionGuard>
		void on_entry(FSM& fsm, const OriginState& ost, const IncommingEvent& evt, const DestinationState& dst, cosnt TransitionAction& ta, const TransitionGuard& tg) override
		{}

		/*!
		 * @brief Defines empty on extit.
		*/
		template<class FSM, State OriginState, Event IncommingEvent, State DestinationState, Action TransitionAction, Action TransitionGuard>
		void on_exit(FSM& fsm, const OriginState& ost, const IncommingEvent& evt, const DestinationState& dst, cosnt TransitionAction& ta, const TransitionGuard& tg) override
		{}

		/*!
		 * @brief defines empty action.
		*/
		template<class FSM, State OriginState, Event IncommingEvent, State DestinationState, Action TransitionGuard>
		void operator()(FSM& fsm, const OriginState& ost, const IncommingEvent& evt, const DestinationState& dst, const TransitionGuard& tg)
		{}

		template<class FSM, State OriginState, Event IncommingEvent, State DestinationState, Action TransitionAction>
		bool operator()(FSM& fsm, const OriginState& ost, const IncommingEvent& evt, const DestinationState& dst, const TransitionAction& ta)
		{
			return true;
		}


	}

};


