#pragma once
#include <DMcommon.h>

#include <vector>
#include <functional>

namespace util
{
namespace path
{
DLL_API void InsertInnerFolderPathList(std::vector<std::wstring> & list,
                                       Path const & dir,
                                       std::function<bool(Path const &)> const & file_check_func);
DLL_API std::vector<std::wstring> MakeFilePathList(std::wstring const & base_dir,
                                                   std::function<bool(Path const &)> const file_check_func,
                                                   bool recursive = true);
DLL_API std::vector<Path> MakeFolderPathList(std::wstring const & base_dir,
                                             std::function<bool(Path const &)> const folder_check_func,
                                             bool recursive = false);
} //namespace path
} // namespace util
