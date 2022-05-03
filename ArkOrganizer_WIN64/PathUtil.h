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
    etc // not unknown, but misc.
};
class ExtensionTable
{
public:
    ExtensionTable();
    path_type findType(std::string const & ext) const;
    path_type findType(std::string && ext);
private:
    std::unordered_map<std::string, path_type> type_table_;
};
}

namespace path 
{ 
void InsertInnerFolderPathList(std::vector<std::string> & list, 
                               std::filesystem::path const & dir,
                               std::function<bool(std::filesystem::path const &)> const & file_check_func);
std::vector<std::string> MakeFilePathList(std::string const & base_dir, 
                                          std::function<bool(std::filesystem::path const &)> const file_check_func, 
                                          bool recursive = true);
} //namespace path
} // namespace util
