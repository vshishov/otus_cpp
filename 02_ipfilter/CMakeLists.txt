cmake_minimum_required(VERSION 3.2)

IF(DEFINED ENV{TRAVIS_BUILD_NUMBER})
  message("TRAVIS_BUILD_NUMBER = $ENV{TRAVIS_BUILD_NUMBER}")
ELSE()
  message("TRAVIS_BUILD_NUMBER is not defined")
  # exit early
  return()
ENDIF()

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

enable_testing()

add_subdirectory(src)

add_subdirectory(test)

# install(TARGETS ip_filter RUNTIME DESTINATION bin)

# set(CPACK_GENERATOR DEB)

# set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
# set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
# set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# set(CPACK_PACKAGE_CONTACT wladimir.shishov@gmail.com)

# include(CPack)

