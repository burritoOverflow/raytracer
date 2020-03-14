add_executable(LibraryTests "")

add_subdirectory(Canvas)
add_subdirectory(Utility)

target_sources(
  LibraryTests
  PRIVATE
    main.cpp
)

target_link_libraries(
  LibraryTests
  PRIVATE
    Canvas
    CanvasTests
    Utility
    UtilityTests
    gmock
)

add_test(LibraryTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LibraryTests)
