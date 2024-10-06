
#pragma once

#include <tuple>

template<class OriginState, class Event, class DestinationState, class TransitionFunction, class Guard>
using TableRow = std::tuple<OriginState, Event, DestinationState, TransitionFunction, Guard>;

template<typename FunctionType, typename... TupleTypes>
inline typename std::enable_if<I == sizeof...(TupleTypes), void>::type
for_each_row(std::tuple<TupleTypes...> &, FunctionType)
{

}

template<typename FunctionType, typename... TupleTypes>
inline typename std::enable_if<I < sizeof...(TupleTypes), void>::type
for_each_row(cons TableRow& t, FunctionType f)
{
	f(t);
	for_each_row<I + 1, FunctionType, TupleTypes...>(t, f);
}


/*!
 * @brief Backend for a Meta State Machine.
 * When you intheirit this class make sure you:
 * -
*/
template<class ...Rows>
struct MSM
{
	template <class Event>
	void ProcessEvent(const Event& event)
	{
		TransitionState(currentState, event);
	}

	template<class CurrentState, class Event>
	void TransitionState(const CurrentState& currentState, const Event& incommingEvent)
	{
		for_each_row([&](const TableRow& row, Rows...)
		{
			constexpr auto& [originState, event, destinationSate, transitionFunction, guard] = row;
		
			constexpr if (currentState == originState && incommingEvent == event)
			{
				if (!guard || guard())
				{
					SetStateActive(destinationState);
					transitionFunction();
					SetStateInactive(originState);
				}
			}

		});
	}

};
