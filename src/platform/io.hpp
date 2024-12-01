#pragma once

#if defined(__UNIX__) || defined(__LINUX__) || defined(__POSIX__)
#include "unix/io.hpp"
#elif defined(_WIN32)
#include "win32/io.hpp"
#endif

namespace ftd {
#if defined(__UNIX__) || defined(__LINUX__) || defined(__POSIX__)
using FileView = plat::nix::FileView;
#elif defined(_WIN32)
using FileView = plat::win32::FileView;
#endif
} // namespace ftd
