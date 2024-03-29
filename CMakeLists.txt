
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
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_definitions("-D_WIN32_WINNT=0x600" "-D_CRT_SECURE_NO_WARNINGS")
    add_compile_options("/wd4996" "/wd4251" "/wd4244" "/wd4267" "/wd4217")
endif ()

# Prepare for export and installation.
set(FMILIBCPP_HEADER_INSTALL_DIR "include")
if (WIN32)
    set(FMILIBCPP_CMAKE_INSTALL_DIR "cmake")
else ()
    set(FMILIBCPP_CMAKE_INSTALL_DIR "share/${PROJECT_NAME}/cmake")
endif ()
set(FMILIBCPP_INSTALL_DESTINATIONS
        ARCHIVE DESTINATION "lib"
        LIBRARY DESTINATION "lib"
        RUNTIME DESTINATION "bin"
        INCLUDES DESTINATION "${FMILIBCPP_HEADER_INSTALL_DIR}")
set(FMILIBCPP_EXPORT_TARGET "${PROJECT_NAME}-targets")

# ==============================================================================
# Dependencies
# ==============================================================================

if(CONAN_EXPORTED) # in conan local cache
    # standard conan installation, deps will be defined in conanfile.py
    # and not necessary to call conan again, conan is already running
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()

    include(cmake/conan.cmake)
    conan_cmake_autodetect(settings)

    conan_cmake_run(
            CONANFILE conanfile.py
            BUILD missing
            SETTINGS ${settings}
            BASIC_SETUP)

endif()

find_package(FMILIB REQUIRED)

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

install(
        EXPORT "${FMILIBCPP_EXPORT_TARGET}"
        DESTINATION "${FMILIBCPP_CMAKE_INSTALL_DIR}"
        NAMESPACE "${PROJECT_NAME}::"
)

include(CMakePackageConfigHelpers)

# Generate and install package-config file.
set(configFile "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake")
set(targetsFile "${FMILIBCPP_CMAKE_INSTALL_DIR}/${FMILIBCPP_EXPORT_TARGET}.cmake")
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/project-config.cmake.in"
        "${configFile}"
        INSTALL_DESTINATION "${FMILIBCPP_CMAKE_INSTALL_DIR}"
        PATH_VARS targetsFile
)
install(FILES "${configFile}" DESTINATION "${FMILIBCPP_CMAKE_INSTALL_DIR}")

# Generate and install package-version file
set(versionFile "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake")
write_basic_package_version_file(
        "${versionFile}"
        VERSION "${PROJECT_VERSION}"
        COMPATIBILITY "SameMajorVersion")
install(FILES "${versionFile}" DESTINATION "${FMILIBCPP_CMAKE_INSTALL_DIR}")

# Install custom find modules
install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindFMILIB.cmake"
        DESTINATION
        "${FMILIBCPP_CMAKE_INSTALL_DIR}"
        )

