project(GVal)
cmake_minimum_required(VERSION 3.1)

option(GVAL_THROWS "Weather GVal will throw an excetion." OFF)

set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2")
set (CMAKE_CXX_STANDARD 11)

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

add_library(GVal STATIC ${GVAL_SOURCES} ${HEADER_FILES})
set_property(TARGET GVal PROPERTY POSITION_INDEPENDENT_CODE ON)

if(GVAL_THROWS)
    target_compile_definitions(GVal PUBLIC GVAL_THROWS=1)
endif()

add_executable(GValTest GValTest.cpp ${HEADER_FILES})
target_link_libraries(GValTest GVal debug Usutfd optimized Usutf )
set_target_properties(GValTest PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
