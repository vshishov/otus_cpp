cmake_minimum_required(VERSION 3.2)

IF(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
ELSE()  
    set(VERSION 0.0.1)
ENDIF()

project(print_ip VERSION ${VERSION})

find_package(Doxygen COMPONENTS dot)

set(SRC_PATH "src/")
# set(TEST_PATH "test/")
include_directories("inc/")

add_executable(print_ip ${SRC_PATH}/main.cpp)


set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(print_ip PRIVATE /W4)
else ()
    target_compile_options(print_ip PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

if(DOXYGEN_FOUND)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    @ONLY)
  add_custom_target(
    docs
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Creating HTML documentation with Doxygen" VERBATIM)
endif()

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT wladimir.shishov@gmail.com)

include(CPack)