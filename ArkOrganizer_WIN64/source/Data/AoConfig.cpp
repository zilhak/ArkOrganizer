#include <pch.h>
#include "AoConfig.h"

#include <fstream>
#include <vector>

namespace configure {

static AoConfig g_config;

AoConfig const & GetConfigData()
{ 
    return g_config; 
}

std::vector<std::wstring> encode(AoConfig const & config)
{
    std::vector<std::wstring> encoded_strings;
    encoded_strings.emplace_back(std::wstring(base_dir_path_id)         + file_seperator + config.base_dir_path);
    encoded_strings.emplace_back(std::wstring(summarize_intput_path_id) + file_seperator + config.summarize_intput_path);
    encoded_strings.emplace_back(std::wstring(summarize_output_path_id) + file_seperator + config.summarize_output_path);
    encoded_strings.emplace_back(std::wstring(viewer_image_path_id)     + file_seperator + config.viewer_image_path);
    encoded_strings.emplace_back(std::wstring(viewer_video_path_id)     + file_seperator + config.viewer_video_path);

    encoded_strings.emplace_back(tag_line_seperator);
    for (std::wstring const & tag : config.tag_list) {
        encoded_strings.emplace_back(tag);
    }
    
    return encoded_strings;
}

void decode(AoConfig & config, std::wstring const & text)
{
    std::wstring id;
    std::wstring data;
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == file_seperator) {
            id = text.substr(0, i);
            i++;
            data = text.substr(i, text.size() - i);
            break;
        }
    }
    
    if (data.empty()) { // is <tags>?
        return;
    }

    if (id == base_dir_path_id)
        config.base_dir_path = data;
    else if (id == summarize_intput_path_id)
        config.summarize_intput_path = data;
    else if (id == summarize_output_path_id)
        config.summarize_output_path = data;
    else if (id == viewer_image_path_id)
        config.viewer_image_path = data;
    else if (id == viewer_video_path_id)
        config.viewer_video_path = data;
}

bool SaveConfig(AoConfig const & config_data, std::wstring const & config_file_name)
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

bool LoadConfig(std::wstring const & config_file_name)
{
    AoConfig load_config;
    std::wifstream config_file;
    config_file.open(config_file_name);

    if (!config_file.is_open()) {
        return false;
    }

    while (!config_file.eof()) { // decode
        std::wstring line;
        getline(config_file, line);
        if (line.compare(tag_line_seperator) == 0) {
            break;
        }
        decode(load_config, line);
    }

    while (!config_file.eof()) {
        std::wstring tag;
        getline(config_file, tag);
        load_config.tag_list.insert(tag);
    }

    g_config = load_config;

    config_file.close();

    return true;
}

void SetBaseDirPath(std::wstring const & base_dir_path)
{
    g_config.base_dir_path = base_dir_path;
}

void SetSummarizeInputPath(std::wstring const & summarize_intput_path)
{
    g_config.summarize_intput_path = summarize_intput_path;
}

void SetSummarizeOutputPath(std::wstring const & summarize_output_path)
{
    g_config.summarize_output_path = summarize_output_path;
}

void SetViewerImagePath(std::wstring const & viewer_image_path)
{
    g_config.viewer_image_path = viewer_image_path;
}

void SetViewerVideoPath(std::wstring const & viewer_video_path)
{
    g_config.viewer_video_path = viewer_video_path;
}

std::wstring const & GetBaseDirPath()
{
    return g_config.base_dir_path;
}

std::wstring const & GetSummarizeInputPath()
{
    return g_config.summarize_intput_path;
}

std::wstring const & GetSummarizeOutputPath()
{
    return g_config.summarize_output_path;
}

std::wstring const & GetViewerImagePath()
{
    return g_config.viewer_image_path;
}

std::wstring const & GetViewerVideoPath()
{
    return g_config.viewer_video_path;
}

void AddTag(std::wstring const & tag)
{
    g_config.tag_list.insert(tag);
}

bool DeleteTag(std::wstring const & tag)
{
    g_config.tag_list.erase(tag);
    return true;
}

} // namespace configure
