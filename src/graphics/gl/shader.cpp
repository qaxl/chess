#include "shader.hpp"

#include "platform/io.hpp"

#include <cstdio>

#include <glad/glad.h>

namespace ftd::gl
{
    constexpr GLenum stage_to_gl_shader_type(ShaderSourceStage stage) {
        switch (stage) {
            case ShaderSourceStage::Vertex:
                return GL_VERTEX_SHADER;
            case ShaderSourceStage::Fragment:
                return GL_FRAGMENT_SHADER;
            default:
                return -1;
        }
    }

    ShaderSource::ShaderSource(ShaderSourceStage stage, std::string_view source, bool file) {
        id = glCreateShader(stage_to_gl_shader_type(stage));
        this->stage = stage;

        const char* cstr;
        FileView view;
        if (file) {
            auto temp_view = FileView::open(source);
            if (!temp_view) {
                fprintf(stderr, "Shader source couldn't be loaded from file: \"%s\"! This is not an CRITICAL ERROR; but graphics may not work as expected.\n", source.data());
            }

            view = std::move(temp_view.value());
            cstr = view.read<const char>();
        } else {
            cstr = source.data();
        }

        glShaderSource(id, 1, &cstr, nullptr);
        glCompileShader(id);
        
        GLint status;
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            char log[1024];
            glGetShaderInfoLog(id, 1024, nullptr, log);

            // TODO: logger
            // This is a soft error, as of now.
            fprintf(stderr, "Shader couldn't be compiled: %s\n", log);
        }
    }

    ShaderSource::~ShaderSource() {
        printf("deleting... %d\n", id);
        glDeleteShader(id);
        id = -1;
    }

    ShaderUniformLocation::ShaderUniformLocation(Shader& shader, std::string_view variable_name) {
        this->location = glGetUniformLocation(shader.id_, variable_name.data());
    }

    ShaderUniformLocation::ShaderUniformLocation(Shader& shader, uint32_t location) : location(location) {}
    ShaderUniformLocation::ShaderUniformLocation(uint32_t location) : location(location) {}

    void Shader::bind() {
       //printf("bound %d\n", id_);
        glUseProgram(id_);
    }

    void Shader::set(ShaderUniformLocation location, Mat4 matrix) {
        glUniformMatrix4fv(location.location, 1, GL_FALSE, &matrix.data()[0][0]);
    }

    void Shader::set(ShaderUniformLocation location, glm::mat4 matrix) {
        glUniformMatrix4fv(location.location, 1, GL_FALSE, &matrix[0][0]);
    }

    void Shader::seti(ShaderUniformLocation location, int value) {
        glUniform1i(location.location, value);
    }


    void Shader::setv(ShaderUniformLocation location, glm::vec4 value) {
        glUniform4fv(location.location, 1, &value[0]);
    }

    void Shader::preinit_shader() {
        id_ = glCreateProgram();
        printf("created %d\n", id_);
    }

    void Shader::process_source(const ShaderSource& source) {
        auto& cache = already_attached_[static_cast<size_t>(source.stage)]; 
        if (cache) {
            fprintf(stderr, "Shader already has same type of source attached!\n");
            return;
        }

        cache = true;
        glAttachShader(id_, source.id);
    }

    static void spit_errors_out_if_any(uint32_t program, GLenum type) {
        GLint status;
        glGetProgramiv(program, type, &status);

        if (status != GL_TRUE) {
            char buf[4096] {};
            glGetProgramInfoLog(program, 4096, nullptr, buf);

            fprintf(stderr, "Failed to %s a shader program: %s\n", type == GL_LINK_STATUS ? "link" : "validate", buf);
        }
    }

    void Shader::postinit_shader() {
        glLinkProgram(id_);
        spit_errors_out_if_any(id_, GL_LINK_STATUS);
        glValidateProgram(id_);
        spit_errors_out_if_any(id_, GL_VALIDATE_STATUS);
    }
}
