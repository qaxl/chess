#if defined(__UNIX__) || defined(__LINUX__) || defined(__POSIX__)
#include "io.hpp"

#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace ftd::plat::nix {
std::optional<FileView> FileView::open(std::string_view file_path) {
  struct stat s;
  int file = ::open(file_path.data(), O_RDONLY);
  if (file == -1 || stat(file_path.data(), &s)) {
    return std::nullopt;
  }

  void *view = mmap(nullptr, s.st_size, PROT_READ, MAP_PRIVATE, file, 0);
  close(file);
  if (!view) {
    return std::nullopt;
  }

  return FileView(view, s.st_size);
}

FileView::~FileView() {
  if (mapped_ && size_) {
    munmap(mapped_, size_);
  }
}
} // namespace ftd::plat::nix
#endif
