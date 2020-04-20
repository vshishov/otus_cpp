cmake_minimum_required(VERSION 3.2)

IF(DEFINED ENV{TRAVIS_BUILD_NUMBER})
  message("TRAVIS_BUILD_NUMBER = $ENV{TRAVIS_BUILD_NUMBER}")
ELSE()
  message("TRAVIS_BUILD_NUMBER is not defined")
  # exit early
  return()
ENDIF()

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file(
  versiondef.h.in 
  ${CMAKE_CURRENT_BINARY_DIR}/versiondef.h
)

add_executable(ip_filter main.cpp)
add_library(ip_filter_lib ip_filter.cpp version.cpp)


set_target_properties(ip_filter ip_filter_lib PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    ip_filter_lib
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT wladimir.shishov@gmail.com)

include(CPack)