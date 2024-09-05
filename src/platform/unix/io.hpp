#pragma once

#include <string_view>
#include <optional>
#include <type_traits>

namespace ftd::plat::nix
{
    template<typename T>
    concept ScalarType = std::is_scalar_v<T>;

    class FileView {
    public:
        static std::optional<FileView> open(std::string_view path);

        FileView() {}
        ~FileView();

        FileView(FileView&& o) { 
            this->mapped_ = o.mapped_; 
            this->size_ = o.size_; 

            o.mapped_ = nullptr; 
            o.size_ = 0;
        }

        FileView& operator=(FileView&& o) {
            this->mapped_ = o.mapped_; 
            this->size_ = o.size_; 

            o.mapped_ = nullptr; 
            o.size_ = 0;
            return *this;
        }

        template<ScalarType T>
        T* read() {
            return static_cast<T*>(mapped_);
        }

        size_t len() {
            return size_;
        }

    private:
        FileView(void* mapped, size_t size) : mapped_{mapped}, size_{size} {}

        void* mapped_ = nullptr;
        size_t size_ = 0;
    };
}
