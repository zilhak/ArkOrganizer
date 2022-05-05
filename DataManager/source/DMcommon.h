#pragma once
#include <filesystem>

#ifdef DATA_MANAGER
    #define DLL_API __declspec(dllexport)
#else
    #define DLL_API __declspec(dllimport)
#endif

using Dir_Iterator = std::filesystem::directory_iterator;
using Path = std::filesystem::path;
