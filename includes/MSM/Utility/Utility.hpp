#pragma once

#include <tuple>
#include <type_traits>
#include <iostream>

namespace MSM { namespace Utility {

    template<typename ...Ts>
    using tuple_cat_t = decltype(std::tuple_cat(std::declval<Ts>()...));


    /*!
     * @brief Prints all types of all transitions to the standard output.
    */
    template<class ...Transitions>
    void PrintTransitions(const std::tuple<Transitions...>) // Why in the world cant this take a reference?
    {
        ((
            std::cout << "Transition: " <<
            typeid(typename Transitions::Evt).name() << ", " <<
            typeid(typename Transitions::Dest).name() << ", " <<
            typeid(typename Transitions::Act).name() << ", " <<
            typeid(typename Transitions::Grd).name() << ", " << "\n"
        ), ...);
    }

    /*!
     * @brief Prints all types of all rows and transitions contained in it to the standard output.
    */
    template<class ...Rows>
    void PrintRows(std::tuple<Rows...> transitionTable)
    {
        ([]
        {
            std::cout << "\nRow: ";
            std::cout << typeid(typename Rows::OriginState).name() << "\n";
            PrintTransitions(Rows::transitions);
            std::cout << "\n";
        }(), ...);
        std::cout << std::endl;
    }

} /* End of namespace Utility */

} /* End of namespace MSM */
