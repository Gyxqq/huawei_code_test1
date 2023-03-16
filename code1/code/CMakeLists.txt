project(CodeCraftSDK)
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

if (!WIN32)
    link_libraries(pthread rt m)
endif (!WIN32)

ADD_EXECUTABLE(main main.cpp c_map.cpp c_robot.cpp input.cpp output_process.cpp output.cpp process_control.cpp robot_table_control.cpp value_hash.cpp)