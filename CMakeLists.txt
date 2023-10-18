
# Mandatory line, sets the minimum version of CMake that should be used with this repository.
# I specified 3.22 because I trust it. However, currently I have 3.26 installed on my machine.
# To verify your version run
# $ cmake --version
cmake_minimum_required(VERSION 3.22)

# Sets a few variables, like PROJECT_NAME
project(WolfSoundAudioPluginTemplate)

# Always use the newest C++ standard on green-field projects if possible.
set(CMAKE_CXX_STANDARD 23)

# I like to download the dependencies to the same folder as the project.
# If you want to install them system wide, set CPM_SOURCE_CACHE with the path to the dependencies
# either as an environment variable or pass it to the cmake script with -DCPM_SOURCE_CACHE=<path>.
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# Downloads CPM if not already downloaded. CPM is an easy-to-use package manager nicely integrated with CMake.
include(cmake/cpm.cmake)

# Adds googletest.
CPMAddPackage(
    NAME GOOGLETEST
    GITHUB_REPOSITORY google/googletest
    GIT_TAG v1.13.0
    VERSION 1.13.0
    SOURCE_DIR ${LIB_DIR}/googletest
    OPTIONS
        "INSTALL_GTEST OFF"
        "gtest_force_shared_crt ON"
)

CPMAddPackage(
    NAME AUDIOFILE
    GITHUB_REPOSITORY adamstark/AudioFile
    GIT_TAG 1.1.1
    VERSION 1.1.1
    SOURCE_DIR ${LIB_DIR}/audiofile
)

CPMAddPackage(
    NAME CSVWRITER
    GITHUB_REPOSITORY al-eax/CSVWriter
    GIT_TAG efaa5f1269ad7ff6e8fdbe3837a4e9726bdb2561
    SOURCE_DIR ${LIB_DIR}/csvwriter
)

# This command allows running tests from the "build" folder (the one where CMake generates the project to).
enable_testing()

# Enables all warnings and treats warnings as errors.
# This needs to be added AFTER all the third-party dependencies.
if(MSVC)
    add_compile_options(/Wall)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(examples STATIC
    source/FractionalDelayLine.cpp
    source/DelayLine.cpp
    source/FeedforwardCombFilter.cpp)

# Adds all the targets configured in the "test" folder.
add_subdirectory(test)
