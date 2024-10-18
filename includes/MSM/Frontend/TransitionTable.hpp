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
		 * @brief This will define a tuple with all types supplied as a parameter pack. 
		*/
		template<typename ...Types>
		using tuple_cat_t = decltype(std::tuple_cat(std::declval<Types>()...));
		
		/*!
		 * @brief This struct supplies a compiletime way of getting a subset of rows based on originState and event
		 *		  to retreive what transitions are defined for this state/event pair.
		*/
		template<class OriginState, class Event>
		struct GetPossibleTransitions
		{
			/*!
			 * @brief This defines a tuple with all rows that have the same OriginState and Event.
			 *        By making clever use of a fold expression and tuple cat we can create a 
			 * 		  subset of our parameterpack stored in a tuple.
			*/
			using PossibleTransitions = tuple_cat_t<
				typename std::conditional<
					std::is_same_v<typename Rows::OriginState, OriginState> && std::is_same_v<typename Rows::Event, Event>,
					std::tuple<Rows>,
					std::tuple<>
				>::type...
			>;
		};

	};

} /* End of namespace Front */

} /* End of namespace MSM */
