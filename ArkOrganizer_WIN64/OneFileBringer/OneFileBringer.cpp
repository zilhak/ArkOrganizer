#include <pch.h>
#include "OneFileBringer.h"
#include <Util/PathUtil.h>

void OneFileBringer::BringOneFile(std::filesystem::path const& home_dir)
{
    auto have_one_file = [](std::filesystem::path const& dir)->bool {
        int count = 0;
        for (auto const & file : std::filesystem::directory_iterator(dir)) {
            if (count > 0)
                return false;
            count++;
        }
        
        if (count == 1)
            return true;
        else
            return false;
    };

    auto one_file_folder_list = util::path::MakeFolderPathList(home_dir, have_one_file);

    for (auto const& one_file_folder : one_file_folder_list) {
        for (auto const & file : std::filesystem::directory_iterator(one_file_folder)) {
            std::filesystem::path new_name = one_file_folder.parent_path();
            new_name /= file.path().filename();
            if (!std::filesystem::exists(new_name)) {
                std::filesystem::rename(file, new_name);
            }
        }
    }

    for (auto const& one_file_folder : one_file_folder_list) {
        bool file_exists = false;
        for (auto const & file : std::filesystem::directory_iterator(one_file_folder)) {
            file_exists = true;
        }
        if (file_exists == false)
            std::filesystem::remove(one_file_folder);
    }
}