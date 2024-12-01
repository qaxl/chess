#include "chess/chess.hpp"
#include "graphics/gl/shader.hpp"
#include "graphics/gl/texture.hpp"
#include "math/mat.hpp"
#include "math/vec.hpp"
#include <SDL2/SDL_events.h>
#include <glad/glad.h>

#include <SDL2/SDL.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include <imgui.h>
#include <vector>

#include "platform/error/res.hpp"

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  SDL_Window *window = SDL_CreateWindow(
      "chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 480,
      SDL_WINDOW_OPENGL | /*SDL_WINDOW_BORDERLESS |*/ SDL_WINDOW_RESIZABLE);
  SDL_GLContext ctx = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, ctx);
  SDL_GL_SetSwapInterval(-1);

  gladLoadGLLoader(SDL_GL_GetProcAddress);

  glViewport(0, 0, 480, 480);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForOpenGL(window, ctx);
  ImGui_ImplOpenGL3_Init("#version 330 core");

  glClearColor(0.22f, 0.22f, 0.22f, 1.0f);
  glViewport(0, 0, 480, 480);

  bool run = true;
  SDL_Event event;

  ftd::Vec3f origin;
  std::vector<ftd::Vec3f> vec3s;

  ftd::Mat4 proj = ftd::Mat4::ortho(480, 480, 0, 1);
  ftd::ChessBoard board;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  bool jump = false;
  while (run) {
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);

      switch (event.type) {
      case SDL_QUIT:
        run = false;
        break;

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == 1) {
          board.move(event.button.x, event.button.y);
        }
        break;

      case SDL_KEYDOWN:
        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
          run = false;
        break;

      case SDL_WINDOWEVENT:
        switch (event.window.event) {
        case SDL_WINDOWEVENT_RESIZED:
          glViewport(0, 0, event.window.data1, event.window.data2);
          break;
        }
        break;
      }
    }

    glClear(GL_COLOR_BUFFER_BIT);

    board.draw();
    // Non-GUI rendering above ^^^
    // -------------------------------------------------
    // ImGui rendering below vvv

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // GUI here.

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  return 0;
}
