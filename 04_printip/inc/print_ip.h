#pragma once

#include "helper.h"

#include <iostream>
#include <tuple>

/**
 * @brief Octet separator for printing IP addresses
 */
const char OCTET_SEPARATOR = '.';

/** 
 * @brief Print IP address
 * This method for printing integer values
 * @param num Integer value
 * @param sout Output stream
 */
template<
  typename T, 
  std::enable_if_t< std::is_integral_v<T>, bool > = true 
>
void print_ip(T t, std::ostream &sout = std::cout){
  int nCountByte = static_cast<int>(sizeof(T));
  for (int i = nCountByte - 1; i >= 0; --i) {    
    sout << (t >> ((i) * 8) & 0xFF);
    if (i != 0) {
       sout << OCTET_SEPARATOR;
    }
  }
  sout << std::endl;
}

/** 
 * @brief Print IP address
 * This method for STL containers
 * 
 * @param t STL container
 * @param sout Output stream
 */
template<
  typename T, 
  std::enable_if_t< is_container_v<T> && !std::is_same_v<T, std::string>, bool > = true 
>
void print_ip(const T& t, std::ostream &sout = std::cout){
  for (auto it = t.begin(); it != t.end(); ++it) {
    if (it != t.begin())
      sout << OCTET_SEPARATOR;
    
    sout << *it;
  }
  sout << std::endl;
}

/** 
 * @brief Print tuple
 * This method for printing values in pair
 * 
 * @param tup tuple with two identical types
 * @param sout Output stream
 * 
 * @throw static_assert When types in a tuple are different.
 */
template <typename T1, typename T2>
void print_tuple(const std::tuple<T1, T2>& tup, std::ostream& sout = std::cout) {
  static_assert(std::is_same<T1, T2>(), "Types in a tuple are different!");
  sout << std::get<0>(tup) << OCTET_SEPARATOR << std::get<1>(tup) << std::endl;
}

/** 
 * @brief Print tuple
 * Overloaded method for printing values in tuple
 * 
 * @param tup tuple with two identical typesTuple with the same types
 * @param sout Output stream
 * 
 * @throw static_assert When types in a tuple are different.
 */
template <typename T, typename ... Ts>
void print_tuple(const std::tuple<T, Ts ...>& tup, std::ostream& sout = std::cout) {
  using Item = typename std::tuple_element<0, std::tuple<Ts ...> >::type;
  static_assert(std::is_same<T, Item>(), "Types in a tuple are different!");
  sout << std::get<0>(tup) << OCTET_SEPARATOR;
  std::apply
  (
    [&sout](auto , auto ... tail) {
      print_tuple(std::make_tuple(tail...), sout);
    }, tup
  );
}

template<
  typename T, 
  std::enable_if_t< is_instantiation_of_v<std::tuple, T>, bool > = true 
>
void print_ip(const T& t, std::ostream &sout = std::cout){
   print_tuple(t, sout);
}


/** 
 * @brief Print IP address
 * This method for printing values from sting as is
 * @param t std::string need print
 * @param sout Output stream
 * @details Prints the contents of a string
 */
template<
  typename T, 
  std::enable_if_t< std::is_same_v<T, std::string>, bool > = true 
>
void print_ip(const T& t, std::ostream &sout = std::cout){
  sout << t << std::endl;
}

/** 
 * @brief Print IP address
 * This method for printing values from C-sting as is
 * @param t C-string need print
 * @param sout Output stream
 * @details Prints the contents of a string
 */
template<
  typename T, 
  std::enable_if_t< std::is_same_v<T, const char *>, bool > = true 
>
void print_ip(T t, std::ostream &sout = std::cout){
  sout << t << std::endl;
}
