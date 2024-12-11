cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE main_cxx_sources CONFIGURE_DEPENDS "src/main/cxx/*")
file(GLOB_RECURSE main_ixx_sources CONFIGURE_DEPENDS "src/main/ixx/*")
file(GLOB_RECURSE test_cxx_sources CONFIGURE_DEPENDS "src/test/cxx/*")
file(GLOB_RECURSE test_ixx_sources CONFIGURE_DEPENDS "src/test/ixx/*")

find_package(GTest REQUIRED)

add_library(fm2gp)
target_sources(fm2gp
    PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
    ${main_ixx_sources}
    PRIVATE
    ${main_cxx_sources}
)

add_executable(fm2gp-test)
target_sources(fm2gp-test
    PRIVATE FILE_SET modules TYPE CXX_MODULES FILES
    ${main_ixx_sources}
    ${test_ixx_sources}
    PRIVATE
    ${main_cxx_sources}
    ${test_cxx_sources}
)
target_link_libraries(fm2gp-test GTest::gmock)
