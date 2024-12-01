add_executable(ftd
    main.cpp

    chess/chess.cpp
    
    graphics/gl/batch_renderer.cpp
    graphics/gl/shader.cpp
    graphics/gl/stb_image.c
    graphics/gl/texture.cpp
    
    platform/unix/io.cpp
    platform/win32/io.cpp)

target_link_libraries(ftd SDL2 SDL2main glad imgui glm)
target_include_directories(ftd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
