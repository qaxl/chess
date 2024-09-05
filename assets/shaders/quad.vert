#version 460 core

layout (location = 0) in vec4 in_pos_tex_coord;
layout (location = 1) in int tex_id;

layout (location = 0) uniform mat4 proj;

out vec2 fs_coord;
flat out int fs_tex_id;

void main() {
    gl_Position = proj * vec4(in_pos_tex_coord.xy, 0.0, 1.0);
    fs_coord = in_pos_tex_coord.zw;
    fs_tex_id = tex_id;
}
