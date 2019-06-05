cmake_minimum_required(VERSION 3.9)
project(cz5test C CXX)

message(STATUS "Using C11")
message(CXX)
set(CMAKE_C_STANDARD 11)

if (NOT "${CMAKE_CXX_FLAGS}" MATCHES "-std=c\\+\\+17")
    message(STATUS "Using C++14")
    set(CMAKE_CXX_STANDARD 14)
else()
    message(STATUS "Using C++17")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED ENV{CONDA_PREFIX})
    include_directories(BEFORE $ENV{CONDA_PREFIX}/include)
    list(APPEND CMAKE_PREFIX_PATH $ENV{CONDA_PREFIX})
endif()

option(WITH_MARRAY ON)
if(WITH_MARRAY)
set(MARRAY_INCLUDE_DIR ${CMAKE_PREFIX_PATH} CACHE PATH "include")
    add_definitions(-DWITH_MARRAY)
    include_directories(${MARRAY_INCLUDE_DIR})
endif()

find_package(Boost REQUIRED COMPONENTS system filesystem)
option(WITH_ZLIB ON)
if(WITH_ZLIB)
    find_package(ZLIB REQUIRED)
    include_directories(ZLIB_INCLUDE_DIRS)
    message(ZLIB_INCLUDE_DIRS)
    add_definitions(-DWITH_ZLIB)
    SET(COMPRESSION_LIBRARIES "${COMPRESSION_LIBRARIES};${ZLIB_LIBRARIES}")
endif()
SET(TEST_LIBS
    ${Boost_FILESYSTEM_LIBRARY}    
    ${Boost_SYSTEM_LIBRARY})
add_executable(test_cpp main.cpp)
target_link_libraries(test_cpp LINK_PUBLIC ${TEST_LIBS} ${COMPRESSION_LIBRARIES})

add_executable(test_c main.c z5wrapper.cc)
target_link_libraries(test_c LINK_PUBLIC ${TEST_LIBS} ${COMPRESSION_LIBRARIES})

add_executable(test_attributes test_attributes.c z5wrapper.cc)
target_link_libraries(test_attributes LINK_PUBLIC ${TEST_LIBS} ${COMPRESSION_LIBRARIES})


install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/z5wrapper.h"
  DESTINATION "${CMAKE_INSTALL_PREFIX}/include")
