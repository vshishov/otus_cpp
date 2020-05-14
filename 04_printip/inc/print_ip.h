#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>

/**
 * @brief Octet separator for printing IP addresses
 */
const char OCTET_SEPARATOR = '.';

/** 
 * @brief Print IP address
 * Overloaded method for printing integer values
 * @param num Integer value
 * @param sout Output stream
 */
template<
  typename T, 
  typename = std::enable_if_t<std::is_integral<T>::value> 
>
void print_ip(T num, std::ostream &sout = std::cout){
  int nCountByte = static_cast<int>(sizeof(T));
  for (int i = nCountByte - 1; i >= 0; --i) {    
    sout << (num >> ((i) * 8) & 0xFF);
    if (i != 0) {
       sout << OCTET_SEPARATOR;
    }
  }
  sout << std::endl;
}

/** 
 * @brief Print IP address
 * Overloaded method for STL containers
 * 
 * @param container STL container
 * @param sout Output stream
 */
template <
    template <class, class> class Container,
    typename T,
    typename Allocator
>
void print_ip(const Container<T, Allocator>& container, std::ostream &sout = std::cout){
  for (auto it = container.begin(); it != container.end(); ++it) {
    if (it != container.begin())
      sout << OCTET_SEPARATOR;
    
    sout << *it;
  }
  sout << std::endl;
}

/** 
 * @brief Print IP address
 * Overloaded method for printing values in pair
 * 
 * @param tup tuple with two identical types
 * @param sout Output stream
 * 
 * @throw static_assert When types in a tuple are different.
 */
template <typename T1, typename T2>
void print_ip(const std::tuple<T1, T2>& tup, std::ostream& sout = std::cout) {
  static_assert(std::is_same<T1, T2>(), "Types in a tuple are different!");
  sout << std::get<0>(tup) << OCTET_SEPARATOR << std::get<1>(tup) << std::endl;
}

/** 
 * @brief Print IP address
 * Overloaded method for printing values in tuple
 * 
 * @param tup tuple with two identical typesTuple with the same types
 * @param sout Output stream
 * 
 * @throw static_assert When types in a tuple are different.
 */
template <typename T, typename ... Ts>
void print_ip(const std::tuple<T, Ts ...>& tup, std::ostream& sout = std::cout) {
  using Item = typename std::tuple_element<0, std::tuple<Ts ...> >::type;
  static_assert(std::is_same<T, Item>(), "Types in a tuple are different!");
  sout << std::get<0>(tup) << OCTET_SEPARATOR;
  std::apply
  (
    [&sout](auto , auto ... tail) {
      print_ip(std::make_tuple(tail...), sout);
    }, tup
  );
}

/** 
 * @brief Print IP address
 * Overloaded method for printing values from sting as is
 * @param value std::string need print
 * @param sout Output stream
 * @details Prints the contents of a string
 */
void print_ip(const std::string& value, std::ostream &sout = std::cout){
  sout << value << std::endl;
}

/** 
 * @brief Print IP address
 * Overloaded method for printing values from C-sting as is
 * @param cstr C-string need print
 * @param sout Output stream
 * @details Prints the contents of a string
 */
void print_ip(const char* cstr, std::ostream &sout = std::cout){
  sout << cstr << std::endl;
}
