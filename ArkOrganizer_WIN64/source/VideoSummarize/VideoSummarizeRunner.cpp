#include "pch.h"
#include "VideoSummarizeRunner.h"

#include <Util/PathUtil.h>
#include <Util/ExtensionUtil.h>
#include <Util/FileUtil.h>
#include <thread>

bool VideoSummarizerRunner::IsReady()
{
    return !(input_home_path_.empty() || output_home_path_.empty());
}

void VideoSummarizerRunner::Run()
{
    if (!IsReady())
        return;

    summarizer::SummarizeConfig config;

    auto only_videofile = [](std::filesystem::path const & path)->bool {
        using namespace util::extension;
        path_type type = ClassifyType(path);
        if (type == path_type::video)
            return true;
        else
            return false;
    };

    auto run_move = [](std::wstring input_home_path, std::filesystem::path file_path, std::filesystem::path relative_file_path) { 
        std::filesystem::path special_case_save_dir(input_home_path);
        special_case_save_dir = special_case_save_dir.parent_path();
        special_case_save_dir /= "AO_special_case";
        special_case_save_dir /= relative_file_path;
        util::file::move(file_path, special_case_save_dir);
    };

    std::vector<Path> videoList = util::path::MakeFilePathList(input_home_path_, only_videofile);
    InsertFileList(videoList);

    for (auto const & file : videoList) {
        std::filesystem::path file_path(file);
        std::filesystem::path relative_file_path = std::filesystem::relative(file_path, input_home_path_);
        std::filesystem::path output_path(output_home_path_);
        output_path /= relative_file_path;
        if (!std::filesystem::exists(output_path.parent_path()))
            std::filesystem::create_directories(output_path.parent_path());
        
        try {
            config.video_path.assign(file_path.string());
            config.output_path.assign(output_path.string());
        } catch (std::system_error err) {
            std::error_code code = err.code();
            if (code.value() == 1113)
                run_move(input_home_path_, file_path, relative_file_path);
            continue;
        }
        config.output_rows = 5;
        config.output_size_width = 1800;
        config.output_size_height = 900;

        if (RunSummarize(config) == false) {
            
            std::thread runner(run_move, input_home_path_, file_path, relative_file_path);
            runner.detach();
        }
    }
}

std::wstring VideoSummarizerRunner::makeOutputPath(std::wstring const & video_path)
{
    std::filesystem::path origin_path(video_path);
    return origin_path;

}

std::wstring VideoSummarizerRunner::makeOutputPath(std::wstring && video_path)
{
    std::filesystem::path origin_path(std::move(video_path));

    return origin_path;
}

void VideoSummarizerRunner::InsertFile(Path const & file_name)
{
    InsertFileToQueue(file_name);
}

void VideoSummarizerRunner::InsertFileList(std::vector<Path> const & file_list)
{
    InsertFileListToQueue(file_list);
}

void VideoSummarizerRunner::InsertFileToQueue(Path const & file_name)
{
    queue_locker_.lock();
    target_queue_.push(file_name);
    queue_locker_.unlock();
}
void VideoSummarizerRunner::InsertFileListToQueue(std::vector<Path> const & file_list)
{
    queue_locker_.lock();
    for (auto const & file : file_list)
        target_queue_.push(file);
    queue_locker_.unlock();
}

std::wstring VideoSummarizerRunner::PopQueue()
{
    queue_locker_.lock();
    std::wstring first_value = target_queue_.front();
    target_queue_.pop();
    queue_locker_.unlock();

    return first_value;
}
