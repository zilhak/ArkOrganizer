#pragma once
#include <string>
#include <filesystem>

class OneFileBringer
{
public:
    static void BringOneFile(std::filesystem::path const & home_dir);
};

