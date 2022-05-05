#pragma once
#include <DMcommon.h>

#include <vector>
#include <string>
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

DLL_API path_type ClassifyType(std::filesystem::path const & path);
} // namespace extension
} // namespace util
