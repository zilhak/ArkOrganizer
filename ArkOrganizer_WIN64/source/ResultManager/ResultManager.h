#pragma once
#include <filesystem>

class ResultManager 
{
private:
    std::filesystem::path image_home_dir_;
    std::filesystem::path video_home_dir_;
    std::filesystem::path matching_file_;

public:
    ResultManager() {};

public:
    void SetImageHome(std::wstring const & home_dir);
    void SetVideoHome(std::wstring const & home_dir);
    std::vector<std::wstring> MakeImageList();
    std::wstring SetAndGetMatchingFileName(std::filesystem::path const & image_file_path);
    void StoreMatchingFile(int store_index);
};
