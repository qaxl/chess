#pragma once

#include "math/vec.hpp"
#include <cstdint>

namespace ftd
{
    class Mat4 {
    public:
        constexpr Mat4() : vals_{
            { 1.0f, 0.0f, 0.0f, 0.0f,},
            { 0.0f, 1.0f, 0.0f, 0.0f,},
            { 0.0f, 0.0f, 1.0f, 0.0f,},
            { 0.0f, 0.0f, 0.0f, 1.0f,},
        } {}

        constexpr static Mat4 ortho(float width, float height, float z_far, float z_near) {
            Mat4 mtx;

            // Scaling 
            mtx.vals_[0][0] =  2 / width;
            mtx.vals_[1][1] = -2 / height;
            mtx.vals_[2][2] = -2 / (z_far - z_near);

            // Translation
            mtx.vals_[0][3] = -width;
            mtx.vals_[1][3] = height;
            mtx.vals_[2][3] = -((z_far + z_near) / (z_far - z_near));

            return mtx;
        }

        constexpr Vec4f* data() {
            return vals_;
        }

    private:
        Vec4f vals_[4];
    };
}
