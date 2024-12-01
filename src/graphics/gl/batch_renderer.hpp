#pragma once

#include "graphics/gl/shader.hpp"
#include "graphics/gl/texture.hpp"
#include "math/mat.hpp"
#include "math/vec.hpp"
#include <cstdint>
#include <glm/mat4x4.hpp>
#include <vector>

namespace ftd::gl {
struct BatchVertex {
  float pos[4];
  int tex_id = 0;
};

struct BatchQuad {
  BatchVertex vertices[4];
};

class BatchRenderer {
public:
  BatchRenderer(Texture &texture);

  void begin();
  void flush();

  void draw(int x, int y, float tx, float ty, float tw, float th,
            bool highlight = false, bool draw_chess_piece = true);

private:
  uint32_t vao_;
  uint32_t vbo_;
  uint32_t ibo_;

  std::vector<BatchQuad> batch_{};
  std::vector<uint16_t> indices_{};

  uint16_t current_index_ = 4;
  size_t draw_calls_saved_ = 0;

  Mat4 proj_;
  glm::mat4 proj__;
  Shader shader_;
  Texture &texture_;
  Texture board_texture_;
  Texture highlight_texture_;
};
} // namespace ftd::gl
