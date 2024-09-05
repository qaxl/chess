#include "batch_renderer.hpp"
#include "glad/glad.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "graphics/gl/shader.hpp"
#include "graphics/gl/texture.hpp"

namespace ftd::gl {
    BatchRenderer::BatchRenderer(Texture& texture) : texture_(texture), 
        shader_(ShaderSource(ShaderSourceStage::Vertex, "assets/shaders/quad.vert"), 
                ShaderSource(ShaderSourceStage::Fragment, "assets/shaders/quad.frag")),
        board_texture_("assets/textures/board.png"),
        highlight_texture_("assets/textures/selected_piece.png") {
        glCreateVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        uint32_t bufs[2];
        glGenBuffers(2, bufs);

        vbo_ = bufs[0];
        ibo_ = bufs[1];

        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);

        glBufferData(GL_ARRAY_BUFFER, sizeof(BatchQuad) * 10983, nullptr, GL_DYNAMIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6 * 10983, nullptr, GL_DYNAMIC_DRAW);

        BatchQuad quad = {
            { 
                { 0.0f, 0.0f, 0.0f, 1.0f, },
                { 0.0f, 480.0f, 0.0f, 0.0f, },
                { 480.0f, 0.0f, 1.0f, 1.0f, },
                { 480.0f, 480.0f, 1.0f, 0.0f, }, 
            }
        };
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(BatchQuad), &quad);
        uint16_t indices[] = {
            0, 1, 2,
            2, 1, 3
        };
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

        proj_ = Mat4::ortho(1024.0f, 768.0f, 1.0f, 0.0f);
        proj__ = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f);
    
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
        glVertexAttribIPointer(1, 1, GL_INT, 5 * sizeof(float), (void*)(4 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        // batch_.reserve(16);
        // indices_.reserve(16 * 6);
    }

    void BatchRenderer::begin() {
        draw_calls_saved_ = 0;
    }

    void BatchRenderer::flush() {
        draw_calls_saved_++;

        glBindVertexArray(vao_);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);

        glBufferSubData(GL_ARRAY_BUFFER, sizeof(BatchQuad), batch_.size() * sizeof(BatchQuad), batch_.data());
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, indices_.size() * sizeof(uint16_t), indices_.data());

        shader_.bind();
        shader_.set(0, proj__);

        texture_.bind(ActiveTextureSlot::Slot0);
        board_texture_.bind(ActiveTextureSlot::Slot1);
        highlight_texture_.bind(ActiveTextureSlot::Slot2);

        shader_.seti(ShaderUniformLocation(shader_, "hl_tex"), 2);
        shader_.seti(ShaderUniformLocation(shader_, "tex"), 1);
        shader_.setv(ShaderUniformLocation(shader_, "color_correction"), glm::vec4(0.25f, 0.25f, 0.25f, 0.0f));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

        shader_.seti(ShaderUniformLocation(shader_, "tex"), 0);
        shader_.setv(ShaderUniformLocation(shader_, "color_correction"), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
        glDrawElementsBaseVertex(GL_TRIANGLES, batch_.size() * 6, GL_UNSIGNED_SHORT, (void*)(sizeof(uint16_t) * 6), 0);
        // glDrawElements(GL_TRIANGLES, batch_.size() * 6, GL_UNSIGNED_SHORT, nullptr);

        glBindVertexArray(0);

        batch_.clear();
        indices_.clear();
        current_index_ = 4;
    }

    void BatchRenderer::draw(int x, int y, float tx, float ty, float tw, float th, bool highlight) {
        float ntw = tw / 360.0f;
        float nth = th / 120.0f;
        batch_.emplace_back(BatchQuad {
            { { (float)x, (float)y, tx, ty + nth, },
                { (float)x, (float)(y) + th, tx, ty },
                { (float)(x) + tw, (float)y, tx + ntw, ty + nth },
                { (float)(x) + tw, (float)(y) + th, tx + ntw, ty }
             }
        });

        indices_.emplace_back(current_index_);
        indices_.emplace_back(current_index_ + 1);
        indices_.emplace_back(current_index_ + 2);
        indices_.emplace_back(current_index_ + 2);
        indices_.emplace_back(current_index_ + 1);
        indices_.emplace_back(current_index_ + 3);

        current_index_ += 4;

        if (highlight) {
            batch_.emplace_back(BatchQuad {
                { { (float)x, (float)y, 0.0f, 1.0f, 2 },
                    { (float)x, (float)(y) + th, 0.0f, 0.0f, 2 },
                    { (float)(x) + tw, (float)y, 1.0f, 1.0f, 2 },
                    { (float)(x) + tw, (float)(y) + th, 1.0f, 0.0f, 2 }
                }
            });

            indices_.emplace_back(current_index_);
            indices_.emplace_back(current_index_ + 1);
            indices_.emplace_back(current_index_ + 2);
            indices_.emplace_back(current_index_ + 2);
            indices_.emplace_back(current_index_ + 1);
            indices_.emplace_back(current_index_ + 3);

            current_index_ += 4;
        }

        // printf("%zu, %zu\n", batch_.size(), indices_.size());
    }

}
