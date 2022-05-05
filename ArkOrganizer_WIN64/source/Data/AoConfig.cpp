#include <pch.h>
#include "AoConfig.h"

#include <fstream>
#include <vector>

std::vector<std::wstring> encode(AoConfig const & config)
{
    std::vector<std::wstring> encoded_strings;
    encoded_strings.emplace_back(config.base_dir_path);

    return encoded_strings;
}

void decode(AoConfig & config, std::wstring const & text)
{
    config.base_dir_path = text;
}

bool saveConfig(AoConfig const & config_data, std::wstring const & config_file_name)
{
    std::wofstream config_file;
    config_file.open(config_file_name);

    if (!config_file.is_open()) {
        return false;
    }

    std::vector<std::wstring> encoded_texts = encode(config_data);
    for (auto const & line : encoded_texts) {
        config_file << line << std::endl;
    }

    config_file.close();

    return true;
}

AoConfig loadConfig(std::wstring const & config_file_name)
{
    AoConfig load_config;
    std::wifstream config_file;
    config_file.open(config_file_name);

    if (!config_file.is_open()) {
        return AoConfig();
    }

    while (!config_file.eof()) {
        std::wstring line;
        getline(config_file, line);
        decode(load_config, line);
    }

    config_file.close();

    return load_config;
}
