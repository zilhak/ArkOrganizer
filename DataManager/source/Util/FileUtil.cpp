#include "FileUtil.h"

namespace util
{
namespace file
{
bool moveToDir(std::filesystem::path const & file_path, std::filesystem::path const & output_path, bool make_dir)
{
    if (std::filesystem::exists(file_path) == false)
        return false;

    std::filesystem::path new_path = output_path;
    new_path /= file_path.filename();

    if (std::filesystem::exists(new_path))
        return false;

    if (make_dir && std::filesystem::exists(output_path) == false) {
        std::filesystem::create_directories(output_path);
    }

    std::filesystem::rename(file_path, new_path);

    return true;
}

bool move(std::filesystem::path const & file_path, std::filesystem::path const & output_file_path, bool make_dir)
{
    if (std::filesystem::exists(file_path) == false)
        return false;

    if (make_dir && std::filesystem::exists(output_file_path.parent_path()) == false) {
        std::filesystem::create_directories(output_file_path.parent_path());
    }

    std::filesystem::rename(file_path, output_file_path);

    return true;
}
} // namespace file
} // namespace util
