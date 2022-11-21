set(This Tests)

add_executable(${This} "")
target_link_libraries(${This} PUBLIC
  gtest_main
  Canvas
  Geometry
  Material
  Pattern
  Scene
  Utility
)

add_subdirectory(Canvas)
add_subdirectory(Geometry)
add_subdirectory(Material)
add_subdirectory(Pattern)
add_subdirectory(Scene)
add_subdirectory(Utility)

gtest_discover_tests(${This})
