#include "pch.h"
#include "PathUtil.h"
#include <algorithm>

namespace util 
{
namespace extension
{

ExtensionTable::ExtensionTable()
{
    constexpr const wchar_t* video_type[] = {L"avi",L"mkv",
        L"3g2", L"3gp", L"3gp2", L"3gpp", L"aac", L"ac3", L"aif", L"aiff", L"amr", L"amv", L"ape", 
        L"asf", L"ass", L"asx", L"avi", L"cda", L"cue", L"divx", L"dmskm", L"dpg", L"dpl", L"dsf",
        L"dts", L"dtshd", L"dvr-ms", L"eac3", L"evo", L"f4v", L"flac", L"flv", L"idx", L"ifo", L"k3g",
        L"lmp4", L"m1a", L"m1v", L"m2a", L"m2t", L"m2ts", L"m2v", L"m3u", L"m3u8", L"m4a", L"m4b", 
        L"m4p", L"m4v", L"mka", L"mod", L"mov", L"mp2", L"mp2v", L"mp3", L"mp4", L"mpa", L"mpcd", 
        L"mpe", L"mpeg", L"mpg", L"mpl", L"mpls", L"mpv2", L"mqv", L"mts", L"mxf", L"nsr", L"nsv", 
        L"ogg", L"ogm", L"ogv", L"opus", L"pls", L"psb", L"qt", L"ra", L"ram", L"rm", L"rmvb", L"rpm", 
        L"rt", L"sbv", L"skm", L"smi", L"srt", L"ssa", L"ssf", L"sub", L"sup", L"swf", L"tak", L"tp",
        L"tpr", L"trp", L"ts", L"tta", L"ttml", L"usf", L"vob", L"vtt", L"wav", L"wax", L"webm", L"wm",
        L"wma", L"wmp", L"wmv", L"wmx", L"wtv", L"wv", L"wvx", L"xspf", L"xss"
    };
    constexpr int video_type_num = sizeof(video_type) / sizeof(video_type[0]);
    for (int i = 0; i < video_type_num; i++) {
        type_table_.insert(std::make_pair<std::wstring, path_type>(video_type[i], path_type::video));
    }

    constexpr const wchar_t* image_type[] = {L"jpg",L"png"};
    constexpr int image_type_num = sizeof(image_type) / sizeof(image_type[0]);
    for (int i = 0; i < image_type_num; i++) {
        type_table_.insert(std::make_pair<std::wstring, path_type>(image_type[i], path_type::image));
    }

    constexpr const wchar_t* compress_type[] = {L"zip",L"rar",L"7z", L"egg", L"zipx", L"alz", L"cab", L"bh", 
        L"001", L"arj", L"lha", L"lzh", L"pma", L"ace", L"arc", L"aes", L"apaq", L"astd", L"br", L"tar", 
        L"gz", L"tgz", L"bz", L"bz2", L"tbz", L"tbz2", L"xz", L"txz", L"lzma", L"tlz", L"lz", L"z",
        L"jar", L"war", L"apk", L"ipa", L"xpi", L"deb", L"iso", L"img", L"isz", L"udf", L"wim", L"bin"
    };
    constexpr int compress_type_num = sizeof(compress_type) / sizeof(compress_type[0]);
    for (int i = 0; i < compress_type_num; i++) {
        type_table_.insert(std::make_pair<std::wstring, path_type>(compress_type[i], path_type::compress));
    }

    type_table_.insert(std::make_pair<std::wstring, path_type>(L"txt", path_type::text));
    type_table_.insert(std::make_pair<std::wstring, path_type>(L"url", path_type::url));
}

path_type ExtensionTable::findType(std::wstring const & ext) const
{
    std::wstring extension = ext;
    std::for_each(extension.begin(), extension.end(), [](wchar_t & c) {
        c = std::tolower(c);
    });
    return type_table_.find(extension)->second;
}

path_type ExtensionTable::findType(std::wstring && ext)
{
    std::for_each(ext.begin(), ext.end(), [](wchar_t & c) {
        c = std::tolower(c);
    });
    return type_table_.find(ext)->second;
}
static ExtensionTable g_extension_table_;

path_type ClassifyType(std::filesystem::path const & path)
{
    return g_extension_table_.findType(path);
}
} // namespace extension

namespace path 
{ 
using Dir_Iterator = std::filesystem::directory_iterator;
using Path = std::filesystem::path;

void InsertInnerFolderPathList(std::vector<std::wstring> & list,
                               std::filesystem::path const & dir,
                               std::function<bool(std::filesystem::path const&)> const & file_check_func)
{
    std::vector<std::wstring> inner_directory_list;
    for (auto const & file : Dir_Iterator(dir)) {
        if (file.is_directory()) {
            inner_directory_list.emplace_back(file.path().wstring());
        } else if (file_check_func == nullptr || file_check_func(file)) {
            list.emplace_back(file.path().wstring());
        }
    }

    for (auto const & sub_dir : inner_directory_list) {
        InsertInnerFolderPathList(list, sub_dir, file_check_func);
    }
}

std::vector<std::wstring> MakeFilePathList(std::wstring const & base_dir, 
                                          std::function<bool(std::filesystem::path const &)> const file_check_func, 
                                          bool recursive)
{
    Path root_path = base_dir;
    if (std::filesystem::is_directory(root_path) == false)
        return std::vector<std::wstring>();

    std::vector<std::wstring> file_path_list;
    std::vector<std::wstring> inner_directory_list;
    for (auto const & file : Dir_Iterator(root_path)) {
        if (file.is_directory()) {
            if (recursive)
                inner_directory_list.emplace_back(file.path().wstring());
        } else {
            if(file_check_func == nullptr || file_check_func(file))
                file_path_list.emplace_back(file.path().wstring());
        }
    }

    for (auto const & sub_dir : inner_directory_list) {
        InsertInnerFolderPathList(file_path_list, sub_dir, file_check_func);
    }

    return file_path_list;
}
} //namespace path
} // namespace util
