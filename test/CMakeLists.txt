add_executable(LibraryTests "")

add_subdirectory(Canvas)
add_subdirectory(Geometry)
add_subdirectory(Material)
add_subdirectory(Scene)
add_subdirectory(Utility)

target_sources(
  LibraryTests
  PRIVATE
    main.cpp
)

target_link_libraries(
  LibraryTests
  PRIVATE
    # CanvasTests
    GeometryTests
    # MaterialTests
    # SceneTests
    # UtilityTests
    gmock
)

add_test(LibraryTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LibraryTests)
