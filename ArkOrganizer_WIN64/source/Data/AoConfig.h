#pragma once
#include <string>

constexpr wchar_t* default_config_name = L"AoConfig.conf";
constexpr wchar_t* default_base_dir_path = L"C:\\";

struct AoConfig
{
    std::wstring base_dir_path = default_base_dir_path;
};

bool saveConfig(AoConfig const & config_data, std::wstring const & config_file_name = default_config_name);
AoConfig loadConfig(std::wstring const & config_file_name = default_config_name);
