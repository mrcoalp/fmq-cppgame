cmake_minimum_required(VERSION 3.10.2)

project(fmq)

set(SFML_DIR "sfml/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio system window)

set(SOURCES
  src/main.cpp
  src/constants.h
  src/engine/game/game.h
  src/engine/game/game.cpp
  src/engine/movement/movementcomponent.h
  src/engine/movement/movementcomponent.cpp
  src/engine/state/gamestate.h
  src/engine/state/gamestate.cpp
  src/entities/entity.h
  src/entities/entity.cpp
  src/entities/rectangle/rectangle.h
  src/entities/rectangle/rectangle.cpp
  src/entities/circle/circle.h
  src/entities/circle/circle.cpp
  src/gui/gui.h
  src/gui/gui.cpp
  src/headers/sfml.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
file(COPY assets DESTINATION "${CMAKE_BINARY_DIR}/bin")
  
add_executable(fmq ${SOURCES})

IF(WIN32)
  file(GLOB SFML_BIN
    "sfml/bin/*.dll"
    )
  file(COPY ${SFML_BIN} DESTINATION "${CMAKE_BINARY_DIR}/bin")
ENDIF()

target_link_libraries(fmq sfml-graphics sfml-audio sfml-system sfml-window)
