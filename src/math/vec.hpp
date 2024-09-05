#pragma once

#include <cmath>
#include <string>

namespace ftd
{
    template<typename T, size_t R>
    class Vec {
    public:
        constexpr Vec() : v_(T(0)) {}

        template<typename... Args>
        constexpr Vec(Args... args) : v_{ static_cast<T>(args)... } {
            static_assert(sizeof...(args) == R, "Number of arguments must match the size R");
        }

        // Constructor that accepts a raw array reference
        constexpr Vec(const T (&arr)[R]) {
            #pragma GCC unroll 4
            for (size_t i = 0; i < R; ++i) {
                v_[i] = arr[i];
            }
        }

        // cross product; only works for 3D (and 7D) vectors
        template<size_t U = R>
        constexpr std::enable_if_t<R == U, Vec> cross(const Vec& o) const {
            Vec res;

            res.v_[0] =     (v_[1] * o.v_[2]) - (o.v_[1] * v_[2]);
            res.v_[1] = -(  (v_[0] * o.v_[2]) - (o.v_[0] * v_[2]));
            res.v_[2] =     (v_[0] * o.v_[1]) - (o.v_[0] * v_[1]);

            return res;
        }

        // dot product
        constexpr T dot(const Vec& o) const {
            T sum = 0;
            #pragma GCC unroll 4
            for (size_t i = 0; i < R; ++i) {
                sum += v_[i] * o.v_[i];   
            }
            return sum;
        }

        constexpr T magnitude() {
            return std::sqrt(dot(*this));
        }

        constexpr Vec operator*(T scalar) const {
            Vec res;
            #pragma GCC unroll 4
            for (size_t i = 0; i < R; ++i) {
                res.v_[i] = this->v_[0] * scalar;
            }

            return res;
        }

        constexpr Vec operator-(const Vec& o) const {
            Vec res;
            for (size_t i = 0; i < R; ++i) {
                res.v_[i] = this->v_[0] - o.v_[i];
            }

            return res;
        }

        constexpr Vec operator+(const Vec& o) const {
            Vec res;
            for (size_t i = 0; i < R; ++i) {
                res.v_[i] = this->v_[0] + o.v_[i];
            }

            return res;
        }

        constexpr std::string to_printable_string() const {
            return std::to_string(v_[0]) + ',' + std::to_string(v_[1]) + ',' + std::to_string(v_[2]);
        }

        T* data() {
            return v_;
        }

        constexpr T& operator[](size_t index) {
            return v_[index];
        }

        constexpr const T& operator[](size_t index) const {
            return v_[index];
        }

    private:
        T v_[R];
    };

    using Vec2f = Vec<float, 2>;
    using Vec2i = Vec<int, 2>;
    using Vec3f = Vec<float, 3>;
    using Vec3i = Vec<int, 3>;
    using Vec4f = Vec<float, 4>;
    using Vec4i = Vec<int, 4>;
}
