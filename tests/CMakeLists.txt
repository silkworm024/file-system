# ---------------------------------
# Download and link GoogleTest code
# ---------------------------------
# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24
# https://github.com/ethereum/solidity/pull/13429
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

# Adapted from googletest CMake instructions
# https://github.com/google/googletest/blob/main/googletest/README.md
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now link against gtest or gtest_main.
add_executable(teststudio16 Studio16.cpp)
target_link_libraries(teststudio16 mockos gtest_main)

add_executable(teststudio17 Studio17.cpp)
target_link_libraries(teststudio17 mockos gtest_main)

add_executable(teststudio18 Studio18.cpp)
target_link_libraries(teststudio18 mockos gtest_main)

add_executable(teststudio19 Studio19.cpp)
target_link_libraries(teststudio19 mockos gtest_main)

add_executable(teststudio20 Studio20.cpp)
target_link_libraries(teststudio20 mockos gtest_main)

add_executable(teststudio21 Studio21.cpp CommandTest.cpp CommandTest.h)
target_link_libraries(teststudio21 mockos gtest_main)

add_executable(testlab5 Lab5.cpp CommandTest.cpp CommandTest.h)
target_link_libraries(testlab5 mockos gtest_main)
