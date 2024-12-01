#pragma once

#include <optional>
#include <string_view>
#include <type_traits>

namespace ftd::plat::win32 {
template <typename T>
concept ScalarType = std::is_scalar_v<T>;

class FileView {
public:
  static std::optional<FileView> open(std::string_view path);

  FileView() {}
  ~FileView();

  FileView(FileView &&o) {
    this->h_map_ = o.h_map_;
    this->h_file_ = o.h_file_;
    this->p_map_ = o.p_map_;
    this->size_ = o.size_;

    o.h_map_ = nullptr;
    o.h_file_ = nullptr;
    o.p_map_ = nullptr;
    o.size_ = 0;
  }

  FileView &operator=(FileView &&o) {
    this->h_map_ = o.h_map_;
    this->h_file_ = o.h_file_;
    this->p_map_ = o.p_map_;
    this->size_ = o.size_;

    o.h_map_ = nullptr;
    o.h_file_ = nullptr;
    o.p_map_ = nullptr;
    o.size_ = 0;
    return *this;
  }

  template <ScalarType T> T *read() { return static_cast<T *>(p_map_); }

  size_t len() { return size_; }

private:
  FileView(void *h_map, void *h_file, void *p_map, size_t size)
      : h_map_{h_map}, h_file_{h_file}, p_map_{p_map}, size_{size} {}

  void *h_map_ = nullptr;
  void *h_file_ = nullptr;
  void *p_map_ = nullptr;

  size_t size_ = 0;
};
} // namespace ftd::plat::win32
