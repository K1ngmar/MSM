
#pragma once

#include "Utility.hpp"

#include <tuple>
#include <type_traits>
#include <deque>
#include <variant>

namespace MSM { namespace Utility {

/////////////////////////////////////////
// Type is duplicate in parameter pack //
/////////////////////////////////////////

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

///////////////////////////////////////////////
// Add type to tuple if not already in tuple //
///////////////////////////////////////////////

    /*!
     * @brief Base definition, should not get used, the specializations overshadow this definition.
    */
    template <typename UniqueTypes, typename...>
    struct AddTypesToTupleIfNotAlreadyInTuple;

    /*!
     * @brief Final UniqueTypes definition.
    */
    template <typename... UniqueTypes>
    struct AddTypesToTupleIfNotAlreadyInTuple<std::tuple<UniqueTypes...> >
    {
        using type = std::tuple<UniqueTypes...>;
    };

    /*!
     * @brief Recursively adds types from TypesToAdd to UniqueTypes.
     * @tparam UniqueTypes is specialized as a tuple so that we can have two parameter packs in the struct.
    */
    template <typename... UniqueTypes, typename CurrentTypeToAdd, typename... TypesToAdd>
    struct AddTypesToTupleIfNotAlreadyInTuple<std::tuple<UniqueTypes...>, CurrentTypeToAdd, TypesToAdd...>
    {
        using type = std::conditional_t
        <
            TypeIsDuplicateInParameterPack<CurrentTypeToAdd, UniqueTypes...>::value,
            typename AddTypesToTupleIfNotAlreadyInTuple<std::tuple<UniqueTypes...>, TypesToAdd...>::type, // Skip CurrentTypeToAdd if it's a duplicate.
            typename AddTypesToTupleIfNotAlreadyInTuple<std::tuple<UniqueTypes..., CurrentTypeToAdd>, TypesToAdd...>::type // Include CurrentTypeToAdd.
        >;
    };


/////////////////////////////
// Unique tuple from types //
/////////////////////////////

    /*!
     * @brief Filters Types for unique types and stores them in a tuple.
    */
    template <typename... Types>
    using UniqueTuple = typename AddTypesToTupleIfNotAlreadyInTuple<std::tuple<>, Types...>::type;


/////////////////////////////
// Unique tuple from tuple //
/////////////////////////////

    /*!
     * @brief Base definition, should not get used, the specializations overshadow this definition.
    */
    template <typename Type>
    struct UnqiqueTupleFromTuple__Impl;

    /*!
     * @brief Filters Types in the tuple for unique types and stores them in a tuple.
    */
    template <typename... Types>
    struct UnqiqueTupleFromTuple__Impl<std::tuple<Types...> >
    {
        using type = UniqueTuple<Types...>;
    };

    /*!
     * @brief Filters Types in the tuple for unique types and stores them in a tuple.
    */
    template <typename Tuple>
    using UniqueTupleFromTuple = typename UnqiqueTupleFromTuple__Impl<Tuple>::type;

///////////////////////////////////////
// Deque of vector of types in tuple //
///////////////////////////////////////

    template <typename Type>
    struct TupleOfDequeOfType__Impl;

    /*!
     * @brief Filters Types in the tuple for unique types and stores them in a tuple.
    */
    template <typename... Types>
    struct TupleOfDequeOfType__Impl<std::tuple<Types...> >
    {
        using type = MSM::Utility::tuple_cat_t
        <
            std::tuple<std::deque<Types> >...
        >;
    };

    /*!
     * @brief Creates an tuple, with Deques of each type in the original tuple.
     *        ie. given tuple<int, float> will result in tuple<deque<int>, deque<float>>.
    */
    template <typename Tuple>
    using TupleOfDequeOfType = typename TupleOfDequeOfType__Impl<Tuple>::type;

////////////////////////////////////////
// Deque of variant of types in tuple //
////////////////////////////////////////

    template <typename Type>
    struct DequeOfVariantOfTupleTypes__Impl;

    /*!
     * @brief Filters Types in the tuple for unique types and stores them in a tuple.
    */
    template <typename... Types>
    struct DequeOfVariantOfTupleTypes__Impl<std::tuple<Types...> >
    {
        using type = std::deque<std::variant<Types...>>;
    };

    /*!
     * @brief Creates an tuple, with Deques of each type in the original tuple.
     *        ie. given tuple<int, float> will result in deque<std::variant<int, float>>.
    */
    template <typename Tuple>
    using DeuqeOfVaraintOfTupleType = typename DequeOfVariantOfTupleTypes__Impl<Tuple>::type;

} /* End of namespace Utility */

} /* End of namespace MSM */
