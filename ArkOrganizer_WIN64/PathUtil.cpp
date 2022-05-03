#include "pch.h"
#include "PathUtil.h"
#include <algorithm>

namespace util 
{
namespace extension
{
ExtensionTable g_extension_table_;

ExtensionTable::ExtensionTable()
{
    constexpr const char* video_type[] = {"avi","mkv"};
    constexpr int video_type_num = sizeof(video_type) / sizeof(video_type[0]);
    for (int i = 0; i < video_type_num; i++) {
        type_table_.insert(std::make_pair<std::string, path_type>(video_type[i], path_type::video));
    }

    constexpr const char* image_type[] = {"jpg","png"};
    constexpr int image_type_num = sizeof(video_type) / sizeof(video_type[0]);
    for (int i = 0; i < image_type_num; i++) {
        type_table_.insert(std::make_pair<std::string, path_type>(image_type[i], path_type::image));
    }
}

path_type ExtensionTable::findType(std::string const & ext) const
{
    std::string extension = ext;
    std::for_each(extension.begin(), extension.end(), [](char & c) {
        c = std::tolower(c);
    });
    return type_table_.find(extension)->second;
}

path_type ExtensionTable::findType(std::string && ext)
{
    std::for_each(ext.begin(), ext.end(), [](char & c) {
        c = std::tolower(c);
    });
    return type_table_.find(ext)->second;
}
}

namespace path 
{ 
using Dir_Iterator = std::filesystem::directory_iterator;
using Path = std::filesystem::path;

void InsertInnerFolderPathList(std::vector<std::string> & list,
                               std::filesystem::path const & dir,
                               std::function<bool(std::filesystem::path const&)> const & file_check_func)
{
    std::vector<std::string> inner_directory_list;
    for (auto const & file : Dir_Iterator(dir)) {
        if (file.is_directory()) {
            inner_directory_list.emplace_back(file.path().string());
        } else if (file_check_func == nullptr || file_check_func(file)) {
            list.emplace_back(file.path().string());
        }
    }

    for (auto const & sub_dir : inner_directory_list) {
        InsertInnerFolderPathList(list, sub_dir, file_check_func);
    }
}

std::vector<std::string> MakeFilePathList(std::string const & base_dir, 
                                          std::function<bool(std::filesystem::path const &)> const file_check_func, 
                                          bool recursive)
{
    Path root_path = base_dir;
    if (std::filesystem::is_directory(root_path) == false)
        return std::vector<std::string>();

    std::vector<std::string> file_path_list;
    std::vector<std::string> inner_directory_list;
    for (auto const & file : Dir_Iterator(root_path)) {
        if (file.is_directory()) {
            if (recursive)
                inner_directory_list.emplace_back(file.path().string());
        } else {
            if(file_check_func == nullptr || file_check_func(file))
                file_path_list.emplace_back(file.path().string());
        }
    }

    for (auto const & sub_dir : inner_directory_list) {
        InsertInnerFolderPathList(file_path_list, sub_dir, file_check_func);
    }

    return file_path_list;
}
} //namespace path
} // namespace util
