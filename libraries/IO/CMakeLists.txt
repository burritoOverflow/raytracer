add_library(IO STATIC "")

target_sources(
  IO
  PRIVATE
    src/FileOBJParser.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/FileOBJParser.hpp
)

target_include_directories(
  IO
  PUBLIC
    include
)

target_link_libraries(
  IO
  PRIVATE
    Utility
)
