#pragma once
#include <vector>
#include <set>

namespace configure {

constexpr wchar_t* base_dir_path_id = L"BaseDir";
constexpr wchar_t* summarize_intput_path_id = L"SummarizeInput";
constexpr wchar_t* summarize_output_path_id = L"SummarizeOutput";
constexpr wchar_t* viewer_image_path_id = L"ViewerImagePath";
constexpr wchar_t* viewer_video_path_id = L"ViewerVideoPath";

constexpr wchar_t file_seperator = L'>';

constexpr wchar_t* default_config_name = L"Config.aoconf";
constexpr wchar_t* default_base_dir_path = L"C:\\";
constexpr wchar_t* none_path = L"";

constexpr wchar_t* tag_line_seperator = L"<tags>";

constexpr wchar_t* tag_list = L"tags.txt";

struct AoConfig
{
    std::wstring base_dir_path = default_base_dir_path;
    std::wstring summarize_intput_path = none_path;
    std::wstring summarize_output_path = none_path;
    std::wstring viewer_image_path = none_path;
    std::wstring viewer_video_path = none_path;
    std::set<std::wstring> tag_list;
};

AoConfig const & GetConfigData();

std::vector<std::wstring> encode(AoConfig const & config);
void decode(AoConfig & config, std::wstring const & text);

bool SaveConfig(AoConfig const & config_data = GetConfigData(), std::wstring const & config_file_name = default_config_name);
bool LoadConfig(std::wstring const & config_file_name = default_config_name);

void SetBaseDirPath(std::wstring const & path);
void SetSummarizeInputPath(std::wstring const & path);
void SetSummarizeOutputPath(std::wstring const & path);
void SetViewerImagePath(std::wstring const & path);
void SetViewerVideoPath(std::wstring const & path);

std::wstring const & GetBaseDirPath();
std::wstring const & GetSummarizeInputPath();
std::wstring const & GetSummarizeOutputPath();
std::wstring const & GetViewerImagePath();
std::wstring const & GetViewerVideoPath();

void AddTag(std::wstring const & tag);
bool DeleteTag(std::wstring const & tag);

} // namespace configure
