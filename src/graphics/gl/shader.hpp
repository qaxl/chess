#pragma once

#include "math/mat.hpp"
#include <glm/mat4x4.hpp>
#include <cstdint>
#include <string_view>

namespace ftd::gl
{
    enum class ShaderSourceStage {
        Vertex,
        Fragment,
        NotAStageCount,
    };

    struct ShaderSource {
        uint32_t id = -1;
        ShaderSourceStage stage = ShaderSourceStage::NotAStageCount;
        
        ShaderSource(ShaderSourceStage stage, std::string_view source, bool file = true);
        ~ShaderSource();
    };

    class Shader;

    struct ShaderUniformLocation {
        uint32_t location = -1;

        ShaderUniformLocation(Shader& shader, std::string_view variable_name);
        ShaderUniformLocation(Shader& shader, uint32_t location);
        ShaderUniformLocation(uint32_t location);
    };

    class Shader {
    public:
        template <typename... Sources>
        Shader(Sources&&... sources) {
            // Use fold expression to iterate over sources and add to vector
            preinit_shader();
            (process_source(std::forward<Sources>(sources)), ...);
            postinit_shader();
        }

        void bind();
        void set(ShaderUniformLocation location, Mat4 matrix);
        void set(ShaderUniformLocation location, glm::mat4 matrix);
        void seti(ShaderUniformLocation location, int value);
        void setv(ShaderUniformLocation location, glm::vec4 value);

    private:
        void preinit_shader();
        void process_source(const ShaderSource& source);
        void postinit_shader();

        uint32_t id_ = -1;
        bool already_attached_[static_cast<size_t>(ShaderSourceStage::NotAStageCount)] = {};

        friend class ShaderUniformLocation;
    };
}
