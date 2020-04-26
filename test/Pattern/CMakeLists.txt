add_library(PatternTests SHARED "")

target_sources(
  PatternTests
  PRIVATE
    GradientPatternTests.cpp
    PatternTests.cpp
    StripePatternTests.cpp
)

target_link_libraries(
  PatternTests
  PRIVATE
    Geometry
    Pattern
    Utility
    gmock
)