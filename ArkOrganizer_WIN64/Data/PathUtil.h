#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <functional>
#include <unordered_map>

namespace util 
{
namespace extension
{
enum class path_type 
{
    not_exists,
    unknown,
    dir,
    video,
    image,
    url,
    text,
    compress,
    etc // not unknown, but misc.
};
class ExtensionTable
{
public:
    ExtensionTable();
    path_type findType(std::wstring const & ext) const;
    path_type findType(std::wstring && ext);
private:
    std::unordered_map<std::wstring, path_type> type_table_;
};

path_type ClassifyType(std::filesystem::path const & path);
} // namespace extension

namespace path 
{ 
void InsertInnerFolderPathList(std::vector<std::wstring> & list, 
                               std::filesystem::path const & dir,
                               std::function<bool(std::filesystem::path const &)> const & file_check_func);
std::vector<std::wstring> MakeFilePathList(std::wstring const & base_dir, 
                                          std::function<bool(std::filesystem::path const &)> const file_check_func, 
                                          bool recursive = true);
} //namespace path
} // namespace util
