
cmake_minimum_required(VERSION 3.15)
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt" projectVersion)
project("fmilibcpp" VERSION ${projectVersion})
message("Current ${PROJECT_NAME} version: ${CMAKE_PROJECT_VERSION}\n")

# ==============================================================================
# Build settings
# ==============================================================================

set(BUILD_SHARED_LIBS OFF)
option(FMILIBCPP_BUILD_TESTS "Build tests" ON)
option(FMILIBCPP_BUILD_EXAMPLES "Build examples" OFF)

# ==============================================================================
# Global internal configuration
# ==============================================================================

set(CMAKE_CXX_STANDARD 17)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_definitions("-D_WIN32_WINNT=0x600" "-D_CRT_SECURE_NO_WARNINGS")
    add_compile_options("/wd4996" "/wd4251" "/wd4244" "/wd4267" "/wd4217")
endif ()

# ==============================================================================
# Dependencies
# ==============================================================================

find_package(unofficial-fmilib CONFIG REQUIRED)

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


# ==============================================================================
# Exports and remaining installation
# ==============================================================================

configure_package_config_file(cmake/config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/fmilibcpp-config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/fmilibcpp
        NO_SET_AND_CHECK_MACRO)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/fmilibcpp-config-version.cmake
        VERSION ${CMAKE_PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)
install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/fmilibcpp-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/fmilibcpp-config-version.cmake
        DESTINATION
        ${CMAKE_INSTALL_DATADIR}/fmilibcpp)

install(TARGETS fmilibcpp EXPORT fmilibcpp-targets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT fmilibcpp-targets
        NAMESPACE fmilibcpp::
        DESTINATION ${CMAKE_INSTALL_DATADIR}/fmilibcpp)
