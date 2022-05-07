#pragma once
#include <DMcommon.h>

namespace util 
{
namespace file
{
DLL_API bool moveToDir(std::filesystem::path const & file_path, std::filesystem::path const & output_path, bool allow_rename = false, bool make_dir = true);
DLL_API bool move(std::filesystem::path const & file_path, std::filesystem::path const & output_file_path, bool make_dir = true);
} // namespace file
} // namespace util
