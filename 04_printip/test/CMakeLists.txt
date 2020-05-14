cmake_minimum_required(VERSION 3.2)

project(ip_filter_test)

# Locate GTest
find_package(GTest REQUIRED)
find_package(Threads)

add_executable(gtest_print_ip  
    main_test.cpp  
    version_test.cpp 
    #ip_filter_test.cpp       
)

set_target_properties(gtest_print_ip PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

 target_include_directories(
    gtest_print_ip
    PRIVATE
    ${GTEST_INCLUDE_DIRS}
    ${TEST_SOURCE_DIR}
    print_ip_lib
)

target_link_libraries(gtest_print_ip
    ${GTEST_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}
    print_ip_lib
)

if (MSVC)
    target_compile_options(gtest_print_ip PRIVATE
        /W4
    )
else ()
    target_compile_options(gtest_print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

add_test(gtest_print_ip gtest_print_ip)