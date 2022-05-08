#include "PathUtil.h"
#include <algorithm>

namespace util
{
namespace path
{
void InsertInnerFolderStrList(std::vector<std::wstring> & list,
                               Path const & dir,
                               std::function<bool(std::filesystem::path const &)> const & file_check_func)
{
    std::vector<std::wstring> inner_directory_list;
    for (auto const & file : Dir_Iterator(dir)) {
        if (file.is_directory()) {
            inner_directory_list.emplace_back(file.path().wstring());
        } else if (file_check_func == nullptr || file_check_func(file)) {
            list.emplace_back(file.path().wstring());
        }
    }

    for (auto const & sub_dir : inner_directory_list) {
        InsertInnerFolderStrList(list, sub_dir, file_check_func);
    }
}

DLL_API void InsertInnerFolderPathList(std::vector<Path> & list,
                                       Path const & dir,
                                       std::function<bool(Path const &)> const & file_check_func)
{
    std::vector<Path> inner_directory_list;
    for (auto const & file : Dir_Iterator(dir)) {
        if (file.is_directory()) {
            inner_directory_list.emplace_back(file.path());
        } else if (file_check_func == nullptr || file_check_func(file)) {
            list.emplace_back(file.path());
        }
    }

    for (auto const & sub_dir : inner_directory_list) {
        InsertInnerFolderPathList(list, sub_dir, file_check_func);
    }
}

std::vector<std::wstring> MakeFileStrList(std::wstring const & base_dir,
                                           std::function<bool(std::filesystem::path const &)> const file_check_func,
                                           bool recursive)
{
    Path root_path = base_dir;
    if (std::filesystem::is_directory(root_path) == false)
        return std::vector<std::wstring>();

    std::vector<std::wstring> file_path_list;
    std::vector<std::wstring> inner_directory_list;
    for (auto const & file : Dir_Iterator(root_path)) {
        if (file.is_directory()) {
            if (recursive)
                inner_directory_list.emplace_back(file.path().wstring());
        } else {
            if (file_check_func == nullptr || file_check_func(file))
                file_path_list.emplace_back(file.path().wstring());
        }
    }

    for (auto const & sub_dir : inner_directory_list) {
        InsertInnerFolderStrList(file_path_list, sub_dir, file_check_func);
    }

    return file_path_list;
}

DLL_API std::vector<Path> MakeFilePathList(Path const & base_dir,
                                           std::function<bool(Path const &)> const file_check_func,
                                           bool recursive)
{
    Path root_path = base_dir;
    if (std::filesystem::is_directory(root_path) == false)
        return std::vector<Path>();

    std::vector<Path> file_path_list;
    std::vector<Path> inner_directory_list;
    for (auto const & file : Dir_Iterator(root_path)) {
        if (file.is_directory()) {
            if (recursive)
                inner_directory_list.emplace_back(file.path().wstring());
        } else {
            if (file_check_func == nullptr || file_check_func(file))
                file_path_list.emplace_back(file.path().wstring());
        }
    }

    for (auto const & sub_dir : inner_directory_list) {
        InsertInnerFolderPathList(file_path_list, sub_dir, file_check_func);
    }

    return file_path_list;
}

std::vector<Path> MakeFolderPathList(std::wstring const & base_dir,
                                     std::function<bool(Path const &)> const folder_check_func,
                                     bool recursive)
{
    Path root_path = base_dir;
    if (std::filesystem::is_directory(root_path) == false)
        return std::vector<std::filesystem::path>();

    std::vector<std::filesystem::path> inner_directory_list;
    for (auto const & file : Dir_Iterator(root_path)) {
        if (file.is_directory() && (folder_check_func == nullptr || folder_check_func(file))) {
            inner_directory_list.emplace_back(file.path().wstring());
        }
    }

    if (recursive) {
        // TODO
        for (auto const & sub_dir : inner_directory_list) {
            //InsertInnerFolderPathList(file_path_list, sub_dir, folder_check_func);
        }
    }

    return inner_directory_list;
}
} //namespace path
} // namespace util
