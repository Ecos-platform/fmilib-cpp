
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(slave_example slave_example.cpp)
target_link_libraries(slave_example PUBLIC fmilibcpp)

add_executable(buffered_slave_example buffered_slave_example.cpp)
target_link_libraries(buffered_slave_example PUBLIC fmilibcpp)
