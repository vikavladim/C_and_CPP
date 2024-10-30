cmake_minimum_required(VERSION 3.22)
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    # GIT_TAG        v1.14.0
    GIT_TAG f8d7d77
)

FetchContent_MakeAvailable(googletest)


# target_compile_options(gtest PRIVATE "-w")
# target_compile_options(gmock PRIVATE "-w") 
