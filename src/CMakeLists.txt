set(publicHeaderDir ${CMAKE_CURRENT_SOURCE_DIR}/../include)


# ==============================================================================
# fmilib wrapper
# ==============================================================================

set(publicHeaders
        "fmilibcpp/fmu.hpp"
        "fmilibcpp/slave.hpp"
        "fmilibcpp/buffered_slave.hpp"
        "fmilibcpp/scalar_variable.hpp"
        "fmilibcpp/model_description.hpp"

        "fmilibcpp/util/fs_portability.hpp"
        )

set(privateHeaders
        "fmilibcpp/fmicontext.hpp"

        "fmilibcpp/fmi1/fmi1_fmu.hpp"
        "fmilibcpp/fmi1/fmi1_model_description.hpp"
        "fmilibcpp/fmi1/fmi1_slave.hpp"

        "fmilibcpp/fmi2/fmi2_fmu.hpp"
        "fmilibcpp/fmi2/fmi2_model_description.hpp"
        "fmilibcpp/fmi2/fmi2_slave.hpp"

        "fmilibcpp/util/temp_dir.hpp"
        "fmilibcpp/util/uuid.hpp"
        )

set(sources
        "fmilibcpp/fmu.cpp"

        "fmilibcpp/fmi1/fmi1_fmu.cpp"
        "fmilibcpp/fmi1/fmi1_slave.cpp"
        "fmilibcpp/fmi1/fmi1_model_description.cpp"

        "fmilibcpp/fmi2/fmi2_fmu.cpp"
        "fmilibcpp/fmi2/fmi2_slave.cpp"
        "fmilibcpp/fmi2/fmi2_model_description.cpp"

        "fmilibcpp/util/uuid.cpp"
        )

set(publicHeadersFull)
foreach (header IN LISTS publicHeaders)
  list(APPEND publicHeadersFull "${publicHeaderDir}/${header}")
endforeach ()

add_library(fmilibcpp ${commonPublicHeadersFull} ${publicHeadersFull} ${privateHeaders} ${sources})
target_compile_features(fmilibcpp PUBLIC "cxx_std_17")
#set_target_properties(fmilibcpp PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(fmilibcpp
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )
target_link_libraries(fmilibcpp PRIVATE unofficial::fmilib::fmilib)
if (UNIX)
  target_link_libraries(fmilibcpp INTERFACE stdc++fs PRIVATE dl)
endif ()
