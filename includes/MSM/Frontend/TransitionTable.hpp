#pragma once

namespace MSM { namespace Front {

	/*!
	 * @brief In your frontend statemachine define `using TransitionTable = MSM::Front::StateMachine<Row....>` 
	 *		  To declare a statemachine.
	*/
	template<typename ...Rows>
	struct Transitiontable
	{
		/*!
		 * @brief This struct supplies a compiletime way of getting a subset of rows based on originState and event
		 *		  to retreive what transitions are defined for this state/event pair.
		*/
		template<class ...Rows>
		struct TransitionTable
		{
			using AllRowsInATuple = tuple_cat_t<std::tuple<Rows>...>;
			AllRowsInATuple allRowsInATuple;

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

	};

} /* End of namespace Front */

} /* End of namespace MSM */
