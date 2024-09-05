add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
target_link_libraries(glad dl)

add_library(imgui STATIC imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/imgui.cpp 
    imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_sdl2.cpp)
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

add_subdirectory(glm)
add_subdirectory(libspng)
