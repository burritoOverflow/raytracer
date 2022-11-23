add_library(Pattern STATIC "")

target_sources(
  Pattern
  PRIVATE
    src/CheckersPattern.cpp
    src/GradientPattern.cpp
    src/Pattern.cpp
    src/RingPattern.cpp
    src/StripePattern.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/CheckersPattern.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/GradientPattern.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/Pattern.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/RingPattern.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/StripePattern.hpp
)

target_include_directories(
  Pattern
  PUBLIC
    include
)

target_link_libraries(
  Pattern
  PRIVATE
    Utility
)
