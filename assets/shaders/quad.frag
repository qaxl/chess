#version 460 core

in vec2 fs_coord;
flat in int fs_tex_id;

layout (location = 1) uniform sampler2D tex;
layout (location = 2) uniform vec4 color_correction;
layout (location = 3) uniform sampler2D hl_tex;

out vec4 out_color;

void main() {
    if (fs_tex_id == 2) {
        out_color = texture(hl_tex, fs_coord);
    } else {
        out_color = clamp(texture(tex, fs_coord) + color_correction, vec4(0.0, 0.0, 0.0, 0.0), vec4(1.0, 1.0, 1.0, 1.0));
    }
}
