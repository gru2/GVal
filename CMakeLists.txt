project(GVal)
cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2")

set(WORK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
link_directories(${WORK_DIR}/Usutf/build)
include_directories(. ${WORK_DIR}/Usutf)

set(GVAL_SOURCES GVal.cpp ProgressReporter.cpp GValUtils.cpp
GValParser.cpp toString.cpp MultiArrayIterator.cpp MultiArraySlice.cpp
GValFormatter.cpp FileStream.cpp BinaryStream.cpp MemoryStream.cpp
GValSerializer.cpp)

set(HEADER_FILES BinaryStream.h GValFormatter.h GValParser.h GValUtils.h
MultiArrayIterator.h ProgressReporter.h Stream.h toString.h FileStream.h
GVal.h GValSerializer.h MemoryStream.h MultiArraySlice.h SmallVector.h)

include_directories(.)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release mode.")
    add_library(GVal STATIC ${GVAL_SOURCES} ${HEADER_FILES})
    add_executable(GValTest GValTest.cpp ${HEADER_FILES})
    target_link_libraries(GValTest GVal Usutf)
endif(CMAKE_BUILD_TYPE STREQUAL "Release")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug mode.")
    add_library(GVald STATIC ${GVAL_SOURCES} ${HEADER_FILES})
    add_executable(GValTestd GValTest.cpp ${HEADER_FILES})
    target_link_libraries(GValTestd GVald Usutfd)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug") 
