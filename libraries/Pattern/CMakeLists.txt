add_library(Pattern SHARED "")

target_sources(
  Pattern
  PRIVATE
    src/Pattern.cpp
    src/StripePattern.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/Pattern.h
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
