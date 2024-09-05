#include "texture.hpp"
#include "platform/io.hpp"

#include <cstdio>
#include <vector>
#include <spng.h>
#include <glad/glad.h>
#include "stb_image.h"

namespace ftd::gl
{
    Texture::Texture(std::string_view path) {
        auto view = FileView::open(path);
        if (!view) {
            fprintf(stderr, "Couldn't load a texture: %s\n", path.data());
            return;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &id_);
        glBindTexture(GL_TEXTURE_2D, id_);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // TODO: cache?
        // spng_ctx* ctx = spng_ctx_new(0);
        // spng_set_chunk_limits(ctx, 1024 * 1024 * 256, 1024 * 1024 * 256);
        // spng_set_png_buffer(ctx, view->read<uint8_t>(), view->len());

        // struct spng_ihdr ihdr;
        // spng_get_ihdr(ctx, &ihdr);

        // size_t len;
        // spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &len);

        // std::vector<uint8_t> image(len, 0);
        // int ret = spng_decode_image(ctx, image.data(), len, SPNG_FMT_RGBA8, 0);
        // if (ret) {
        //     fprintf(stderr, "spng_decode_image() failed, error: %s\n", spng_strerror(ret));
        //     return;
        // }

        int w, h, ch;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* d = stbi_load(path.data(), &w, &h, &ch, 4);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, d);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(d);
        // spng_ctx_free(ctx);
    }

    void Texture::bind(ActiveTextureSlot slot) {
        glActiveTexture((GLenum)slot);
        glBindTexture(GL_TEXTURE_2D, id_);
    }
}
