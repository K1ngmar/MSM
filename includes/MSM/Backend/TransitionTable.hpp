#pragma once

#include <tuple>

namespace MSM { namespace Back {

	/*!
	 * @brief 
	 * @tparam AllRowsInATuple gotten from the MSM::Front::TransitionTable.
	*/
	template<typename AllRowsInATuple>
	struct TransitionTable
	{

		template <class Event, size_t N = 0>
		void DoSomethingWithTheTransition(const size_t currentStateId)
		{
			if (N == currentStateId)
			{
				PrintTransitions(std::tuple_element_t<N, AllRowsInATuple>::transitions);
				return;
			}
			if constexpr (N + 1 < std::tuple_size_v<AllRowsInATuple>)
			{
				DoSomethingWithTheTransition<Event, N + 1>(currentStateId);
			}
			else
			{
				throw std::runtime_error("Broken state machine, no state found for id: " + std::to_string(currentStateId));
			}
		}
	};

} /* End of namespace Back */

} /* End of namespace MSM */
