#include <pch.h>
#include "ResultManager.h"

#include <Data/PathUtil.h>
#include <Interface/EventInterface.h>

void ResultManager::viewResult(std::filesystem::path const& home_dir)
{
    summarizer::ImageViewer viewer;

    auto is_image = [](std::filesystem::path const& file_path)->bool {
        auto file_type = util::extension::ClassifyType(file_path);
        if (file_type == util::extension::path_type::image)
            return true;
        else
            return false;
    };

    auto path_list = util::path::MakeFilePathList(home_dir, is_image);

    std::vector<std::string> path_list_string;
    for (auto const & path_unicode : path_list) {
        std::filesystem::path path = (path_unicode);
        path_list_string.emplace_back(path.string());
    }

    viewer.SetImageList(path_list_string);
    viewer.RunImageViewer();
}
