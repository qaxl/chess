#if defined(_WIN32)
#include "io.hpp"

#include <Windows.h>

namespace ftd::plat::win32 {
std::optional<FileView> FileView::open(std::string_view file_path) {
  HANDLE hFile = CreateFileA(file_path.data(), GENERIC_READ, FILE_SHARE_READ,
                             NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  if (hFile == INVALID_HANDLE_VALUE) {
    return std::nullopt;
  }

  DWORD fileSize = GetFileSize(hFile, NULL);
  if (fileSize == INVALID_FILE_SIZE) {
    CloseHandle(hFile);
    return std::nullopt;
  }

  HANDLE hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);

  if (hMap == NULL) {
    CloseHandle(hFile);
    return std::nullopt;
  }

  LPVOID pMap = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);

  if (pMap == NULL) {
    CloseHandle(hMap);
    CloseHandle(hFile);
    return std::nullopt;
  }

  return FileView{hMap, hFile, pMap, fileSize};
}

FileView::~FileView() {
  if (h_map_ && h_file_ && p_map_ && size_) {
    UnmapViewOfFile(p_map_);
    CloseHandle(h_map_);
    CloseHandle(h_file_);
  }
}
} // namespace ftd::plat::win32
#endif