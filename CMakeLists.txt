PROJECT(GVal)
cmake_minimum_required(VERSION 2.8)

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
