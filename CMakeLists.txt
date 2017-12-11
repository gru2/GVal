PROJECT(GVal)
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

set(GVAL_SOURCES GVal.cpp ProgressReporter.cpp GValUtils.cpp Sutf.cpp
GValParser.cpp toString.cpp MultiArrayIterator.cpp MultiArraySlice.cpp
GValFormatter.cpp FileStream.cpp BinaryStream.cpp MemoryStream.cpp
GValSerializer.cpp)

set(HEADER_FILES BinaryStream.h GValFormatter.h GValParser.h GValUtils.h
MultiArrayIterator.h ProgressReporter.h Stream.h toString.h FileStream.h
GVal.h GValSerializer.h MemoryStream.h MultiArraySlice.h SmallVector.h 
Sutf.h)

INCLUDE_DIRECTORIES(.)

ADD_LIBRARY(GVal STATIC ${GVAL_SOURCES} ${HEADER_FILES})
ADD_EXECUTABLE(GValTest GValTest.cpp ${HEADER_FILES})
TARGET_LINK_LIBRARIES(GValTest GVal)
