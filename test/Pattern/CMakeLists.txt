add_library(PatternTests SHARED "")

target_sources(
  PatternTests
  PRIVATE
    StripePatternTests.cpp
)

target_link_libraries(
  PatternTests
  PRIVATE
    Pattern
    Utility
    gmock
)