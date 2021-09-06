set(publicHeaderDir ${CMAKE_SOURCE_DIR}/include)

# ==============================================================================
# common headers
# ==============================================================================

set(commonPublicHeaders
        "fmilibcpp/util/temp_dir.hpp"
        "fmilibcpp/util/fs_portability.hpp"
        "fmilibcpp/util/fixed_range_random_generator.hpp"
        )

set(commonPublicHeadersFull)
foreach (header IN LISTS commonPublicHeaders)
  list(APPEND commonPublicHeadersFull "${publicHeaderDir}/${header}")
endforeach ()

# ==============================================================================
# fmilib wrapper
# ==============================================================================

set(fmiPublicHeaders
        "fmilibcpp/fmu.hpp"
        "fmilibcpp/slave.hpp"
        "fmilibcpp/buffered_slave.hpp"
        "fmilibcpp/scalar_variable.hpp"
        "fmilibcpp/model_description.hpp"
        )

set(fmiPrivateHeaders
        "fmilibcpp/fmicontext.hpp"

        "fmilibcpp/fmi1/fmi1_fmu.hpp"
        "fmilibcpp/fmi1/fmi1_model_description.hpp"
        "fmilibcpp/fmi1/fmi1_slave.hpp"

        "fmilibcpp/fmi2/fmi2_fmu.hpp"
        "fmilibcpp/fmi2/fmi2_model_description.hpp"
        "fmilibcpp/fmi2/fmi2_slave.hpp"
        )

set(fmiSources
        "fmilibcpp/fmu.cpp"

        "fmilibcpp/fmi1/fmi1_fmu.cpp"
        "fmilibcpp/fmi1/fmi1_slave.cpp"
        "fmilibcpp/fmi1/fmi1_model_description.cpp"

        "fmilibcpp/fmi2/fmi2_fmu.cpp"
        "fmilibcpp/fmi2/fmi2_slave.cpp"
        "fmilibcpp/fmi2/fmi2_model_description.cpp"
        )

set(fmiPublicHeadersFull)
foreach (header IN LISTS fmiPublicHeaders)
  list(APPEND fmiPublicHeadersFull "${publicHeaderDir}/${header}")
endforeach ()

add_library(fmilibcpp ${commonPublicHeadersFull} ${fmiPublicHeadersFull} ${fmiPrivateHeaders} ${fmiSources})
target_compile_features(fmilibcpp PUBLIC "cxx_std_17")
set_target_properties(fmilibcpp PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(fmilibcpp
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )
target_link_libraries(fmilibcpp PRIVATE FMILIB::FMILIB)
if (UNIX)
  target_link_libraries(fmilibcpp INTERFACE stdc++fs PRIVATE dl)
endif ()

# ==============================================================================
# Installation rules
# ==============================================================================

install(
        TARGETS fmilibcpp
        EXPORT "${FMILIBCPP_EXPORT_TARGET}"
        ${FMILIBCPP_INSTALL_DESTINATIONS}
)
install(
        DIRECTORY "${publicHeaderDir}/fmilibcpp"
        DESTINATION "${FMILIBCPP_HEADER_INSTALL_DIR}"
)
