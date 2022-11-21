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
    ${CMAKE_CURRENT_LIST_DIR}/include/CheckersPattern.h
    ${CMAKE_CURRENT_LIST_DIR}/include/GradientPattern.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Pattern.h
    ${CMAKE_CURRENT_LIST_DIR}/include/RingPattern.h
    ${CMAKE_CURRENT_LIST_DIR}/include/StripePattern.h
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
