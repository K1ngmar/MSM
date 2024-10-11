
#pragma once

#include "FrontEnd/TTRow.hpp"
#include "FrontEnd/Event.hpp"

namespace MSM
{

	/*!
	 * @brief Type to use when you dont want anything on that slot tof the TTRow.
	 *		  This class can be used as Event
	*/
	class None : public State<>
	{
		/*!
		 * @brief Defines empty on entry.
		*/
		template<class FSM, State OriginState, Event IncommingEvent, State DestinationState, Action TransitionAction, Action TransitionGuard>
		void on_entry(FSM& fsm, const OriginState& ost, const IncommingEvent& evt, const DestinationState& dst, const TransitionAction& ta, const TransitionGuard& tg) override
		{}

		/*!
		 * @brief Defines empty on extit.
		*/
		template<class FSM, State OriginState, Event IncommingEvent, State DestinationState, Action TransitionAction, Action TransitionGuard>
		void on_exit(FSM& fsm, const OriginState& ost, const IncommingEvent& evt, const DestinationState& dst, const TransitionAction& ta, const TransitionGuard& tg) override
		{}

		/*!
		 * @brief Defines empty action.
		*/
		template<class FSM, State OriginState, Event IncommingEvent, State DestinationState, Action TransitionGuard>
		void operator()(FSM& fsm, const OriginState& ost, const IncommingEvent& evt, const DestinationState& dst, const TransitionGuard& tg)
		{}

		/*!
		 * @brief Ddefines a guard that will never block.
		*/
		template<class FSM, State OriginState, Event IncommingEvent, State DestinationState, Action TransitionAction>
		bool operator()(FSM& fsm, const OriginState& ost, const IncommingEvent& evt, const DestinationState& dst, const TransitionAction& ta)
		{
			return true;
		}
	};

};


