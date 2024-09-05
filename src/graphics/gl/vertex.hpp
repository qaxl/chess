#pragma once

#include "glad/glad.h"
#include <cstdint>
namespace ftd::gl
{
    class VertexAttribute {
    public:
        VertexAttribute() {
            glCreateVertexArrays(1, &vao_);
        }

        void bind() {
            glBindVertexArray(vao_);

            glVertexAttribPointer(0, sizeof(float) * 2, GL_FLOAT, GL_FALSE, 0, 0);
        }

        template<typename T>
        void push_attr() {}

        template<float>
        void push_attr() {

        }

    private:
        uint32_t vao_;
    };
}
