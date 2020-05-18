#pragma once

#include <type_traits>

/**
 * @brief Helper struct. Determines whether T is std::container.
 */
template <typename T, typename = void>
struct is_container : std::false_type { };

template <typename T>
struct is_container<T,
    std::void_t<decltype(std::declval<T&>().begin()),
           decltype(std::declval<T&>().end()),
           typename T::value_type
           >>
    : std::true_type { };

template <typename T>
inline constexpr bool is_container_v = is_container<T>::value;

/**
 * @brief Helper struct. Determines whether T is a specialisation of another
 */
template < template <typename ...> class T, typename = void >
struct is_instantiation_of : std::false_type {};

template < template <typename ...> class T, typename ... Args >
struct is_instantiation_of< T, T<Args...> > : std::true_type {};

template <template <typename ...> class T, typename U>
inline constexpr bool is_instantiation_of_v = is_instantiation_of<T, U>::value;