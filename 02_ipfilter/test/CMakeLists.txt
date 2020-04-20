cmake_minimum_required(VERSION 3.2)

project(ip_filter_test)

# Locate GTest
find_package(GTest REQUIRED)
find_package(Threads)

add_executable(gtest_ip_filter  
    main_test.cpp  
    version_test.cpp 
    ip_filter_test.cpp       
)

 target_include_directories(
    gtest_ip_filter
    PRIVATE
    ${GTEST_INCLUDE_DIRS}
    ${TEST_SOURCE_DIR}
    ip_filter_lib
)

target_link_libraries(gtest_ip_filter
    ${GTEST_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}
    ip_filter_lib
)

if (MSVC)
    target_compile_options(gtest_ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(gtest_ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

add_test(gtest_ip_filter gtest_ip_filter)