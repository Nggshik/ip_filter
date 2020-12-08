cmake_minimum_required(VERSION 3.2)

if(NOT DEFINED ${TRAVIS_BUILD_NUMBER})
  set(TRAVIS_BUILD_NUMBER 1)
endif(NOT DEFINED ${TRAVIS_BUILD_NUMBER})

project(ip_filter VERSION 0.0.${TRAVIS_BUILD_NUMBER})

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

add_executable(ip_filter ip_filter.cpp)

add_library(versionlib lib.cpp)

add_executable(tests tests.cpp)

set_target_properties(ip_filter versionlib tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

set_target_properties(tests PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(ip_filter
    versionlib
    Threads::Threads
)

target_link_libraries(tests
    ${Boost_LIBRARIES}
    versionlib
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT baranovsky.s.a@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(myTest tests)