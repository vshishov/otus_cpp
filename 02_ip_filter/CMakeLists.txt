cmake_minimum_required(VERSION 3.2)

IF(DEFINED ENV{TRAVIS_BUILD_NUMBER})
  message("TRAVIS_BUILD_NUMBER = $ENV{TRAVIS_BUILD_NUMBER}")
ELSE()
  message("TRAVIS_BUILD_NUMBER is not defined")
  # exit early
  return()
ENDIF()

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE 
  src/main.cpp
)

configure_file(
  src/version.h.in 
  ${CMAKE_CURRENT_BINARY_DIR}/version.h
)

add_executable(ip_filter_cli ${SOURCE})
add_library(ip_filter src/ip_filter.cpp)
add_executable(gtest_ip_filter test/ip_filter_tests.cpp)

set_target_properties(ip_filter_cli ip_filter gtest_ip_filter PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
  ip_filter_cli
  PRIVATE 
  "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(ip_filter_cli PRIVATE
  ip_filter
)

target_link_libraries(gtest_ip_filter
    ${GTEST_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}
    ip_filter
)

if (MSVC)
    target_compile_options(ip_filter_cli PRIVATE
        /W4
    )
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(gtest_ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(gtest_ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT wladimir.shishov@gmail.com)

include(CPack)

enable_testing()

add_test(gtest_ip_filter gtest_ip_filter)