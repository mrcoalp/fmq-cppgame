cmake_minimum_required(VERSION 3.10)
project(fmq)

# Include cmake util functions
include(${CMAKE_SOURCE_DIR}/utils/cmake/utils.cmake)

# Downloads SFML library
downloadSFML()

set(SFML_DIR "external/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)

file(GLOB_RECURSE SOURCES
        src/*.h
        src/*.cpp
        )

include_directories(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
  
add_executable(fmq ${SOURCES})

#copy dll from sfml if in windows
IF(WIN32)
  file(GLOB SFML_BIN
    "external/SFML-2.5.1//bin/*.dll"
    )
  file(COPY ${SFML_BIN} DESTINATION "${CMAKE_BINARY_DIR}/bin/Release")
  file(COPY assets DESTINATION "${CMAKE_BINARY_DIR}/bin/Release")
ELSE()
  file(COPY assets DESTINATION "${CMAKE_BINARY_DIR}/bin")
ENDIF()

target_link_libraries(fmq sfml-graphics sfml-audio sfml-system sfml-window)
