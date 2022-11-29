add_executable(${PROJECT_NAME} "")

target_sources(
  ${PROJECT_NAME}
  PRIVATE
    main.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/CreateWorld.hpp
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    Canvas
    Geometry
    Scene
    Utility
)
