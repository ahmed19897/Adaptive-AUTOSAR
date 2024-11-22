#determine the minimum version to check and stop if we don't meet the minimum version
cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_FLAGS "-g -Wall")

project(ErrorTypes)



#determine and set our source files to build
set(SRC_FILES
    ErrorTypes_Test_Main.cpp
    core_core_error_domain_tests.cpp
    core_error_code_test.cpp
    core_result_test.cpp
)
#determine and set our source files to build


#this part is to static link a library and build a main.c
message(STATUS "YOUR SOURCE FILES ARE:      ${SRC_FILES}")
message("OUR MAIN SOURCE PATH STARTS AT: ${CMAKE_SOURCE_DIR}")
#this part is to static link a library and build a main.c



#check if the source file exists in our current directory
if(EXISTS ${CMAKE_SOURCE_DIR}/ErrorTypes_Test_Main.cpp)
    message(STATUS"main Exists")
else()
    message(FETAL_ERROR"File NOT FOUND !")
endif()
#check if the source file exists in our current directory



#creates the exe
add_executable(ErrorTypes_Test_Main ${SRC_FILES})
target_link_libraries(ErrorTypes_Test_Main gtest )