#include <pch.h>
#include "ResultManager.h"

#include <Util/PathUtil.h>
#include <Util/ExtensionUtil.h>
#include <Interface/EventInterface.h>

constexpr wchar_t* move_dir_1 = L"AoStore1";
constexpr wchar_t* move_dir_2 = L"AoStore2";
constexpr wchar_t* move_dir_3 = L"AoStore3";
constexpr wchar_t* move_dir_4 = L"AoStore4";

std::vector<std::wstring> ResultManager::MakeImageList()
{
    auto is_image = [](std::filesystem::path const& file_path)->bool {
        auto file_type = util::extension::ClassifyType(file_path);
        if (file_type == util::extension::path_type::image)
            return true;
        else
            return false;
    };

    auto path_list = util::path::MakeFilePathList(image_home_dir_, is_image);

    std::vector<std::string> path_list_string;
    for (auto const & path_unicode : path_list) {
        std::filesystem::path path = (path_unicode);
        path_list_string.emplace_back(path.string());
    }
}

std::wstring ResultManager::SetAndGetMatchingFileName(std::filesystem::path const & image_file_path)
{
    std::filesystem::path video_file_name = image_file_path.filename().replace_extension();
    std::filesystem::path relative_path = std::filesystem::relative(image_file_path.parent_path(), image_home_dir_);
    std::filesystem::path video_path = video_home_dir_;
    video_path /= relative_path;
    video_path /= video_file_name;

    if (std::filesystem::exists(video_path))
        matching_file_ = video_path;

    return matching_file_.wstring();
}

void ResultManager::SetImageHome(std::wstring const & home_dir)
{
    image_home_dir_ = home_dir;
    if (!std::filesystem::exists(image_home_dir_) || !std::filesystem::is_directory(image_home_dir_)) {
        image_home_dir_.clear();
    }
}

void ResultManager::SetVideoHome(std::wstring const & home_dir)
{
    video_home_dir_ = home_dir;
    if (!std::filesystem::exists(video_home_dir_) || !std::filesystem::is_directory(video_home_dir_)) {
        video_home_dir_.clear();
    }
}
