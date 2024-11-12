
#pragma once

#include "Utility.hpp"

#include <tuple>
#include <type_traits>

namespace MSM { namespace Utility {

    /*!
     * @brief Base definition, should not get used, the specializations overshadow this definition.
    */
    template <typename T, typename... Types>
    struct TypeIsDuplicateInParameterPack;

    /*!
     * @brief If its the only type, it is unique.
    */
    template <typename T>
    struct TypeIsDuplicateInParameterPack<T> : std::false_type
    {};

    /*!
     * @brief Unpack the parameter pack in order to compare types.
    */
    template <typename CurrentType, typename NextType, typename... OtherTypesToCheck>
    struct TypeIsDuplicateInParameterPack<CurrentType, NextType, OtherTypesToCheck...>
        : std::conditional_t
        <
            std::is_same_v<CurrentType, NextType>,
            std::true_type, // If T and NextType are the same it is duplicate.
            TypeIsDuplicateInParameterPack<CurrentType, OtherTypesToCheck...> // Otherwise recursively inheirit to see if it is duplicate.
        >
    {};

    /*!
     * @brief Base definition, should not get used, the specializations overshadow this definition.
    */
    template <typename Result, typename...>
    struct AddTypesToTupleIfNotAlreadyInTuple;

    /*!
     * @brief Final result definition.
    */
    template <typename... Result>
    struct AddTypesToTupleIfNotAlreadyInTuple<std::tuple<Result...> >
    {
        using type = std::tuple<Result...>;
    };

    /*!
     * @brief Recursively adds types from TypesToAdd to Result.
     * @tparam Result is specialized as a tuple so that we can have two parameter packs in the struct.
    */
    template <typename... Result, typename CurrentTypeToAdd, typename... TypesToAdd>
    struct AddTypesToTupleIfNotAlreadyInTuple<std::tuple<Result...>, CurrentTypeToAdd, TypesToAdd...>
    {
        using type = std::conditional_t
        <
            TypeIsDuplicateInParameterPack<CurrentTypeToAdd, Result...>::value,
            typename AddTypesToTupleIfNotAlreadyInTuple<std::tuple<Result...>, TypesToAdd...>::type, // Skip CurrentTypeToAdd if it's a duplicate.
            typename AddTypesToTupleIfNotAlreadyInTuple<std::tuple<Result..., CurrentTypeToAdd>, TypesToAdd...>::type // Include CurrentTypeToAdd.
        >;
    };

    /*!
     * @brief Filters Types for unique types and stores them in a tuple.
    */
    template <typename... Types>
    using UniqueTuple = typename AddTypesToTupleIfNotAlreadyInTuple<std::tuple<>, Types...>::type;


} /* End of namespace Utility */

} /* End of namespace MSM */
