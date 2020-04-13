add_library(Pattern SHARED "")

target_sources(
  Pattern
  PRIVATE
    src/StripePattern.cpp
  PUBLIC
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
