
cmake_minimum_required(VERSION 3.11)
file(STRINGS "${CMAKE_SOURCE_DIR}/version.txt" projectVersion)
project("fmilibcpp" VERSION ${projectVersion})
message("Current ${PROJECT_NAME} version: ${CMAKE_PROJECT_VERSION}\n")

# ==============================================================================
# Build settings
# ==============================================================================

option(FMILIBCPP_BUILD_TESTS "Build tests" ON)
option(FMILIBCPP_BUILD_EXAMPLES "Build examples" OFF)

# ==============================================================================
# Global internal configuration
# ==============================================================================

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif ()

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(CMAKE_DEBUG_POSTFIX "d")
    add_definitions("-D_WIN32_WINNT=0x600" "-D_CRT_SECURE_NO_WARNINGS")
    add_compile_options("/wd4996" "/wd4251" "/wd4244" "/wd4267")
endif ()

# ==============================================================================
# Dependencies
# ==============================================================================

set(dependencies
        fmilibrary/2.0.3
        )

if (FMILIBCPP_BUILD_TESTS)
    list(APPEND dependencies boost/1.71.0)
endif ()


# Download automatically, you can also just copy the conan.cmake file
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(
        REQUIRES
        ${dependencies}
        BUILD missing
        SETTINGS build_type=${CMAKE_BUILD_TYPE}
        BASIC_SETUP CMAKE_TARGETS)

# ==============================================================================
# Targets
# ==============================================================================

add_subdirectory(src)

if (FMILIBCPP_BUILD_EXAMPLES OR FMILIBCPP_BUILD_TESTS)
    file(COPY data/fmus DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

    if (FMILIBCPP_BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif ()

    if (FMILIBCPP_BUILD_TESTS)
        enable_testing()
        add_subdirectory(tests)
    endif ()

endif ()
