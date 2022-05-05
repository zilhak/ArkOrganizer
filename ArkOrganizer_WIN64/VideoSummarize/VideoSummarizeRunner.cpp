#include "pch.h"
#include "VideoSummarizeRunner.h"
#include <Data/PathUtil.h>
#include "stack"

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


    std::vector<std::wstring> videoList = util::path::MakeFilePathList(input_home_path_, only_videofile);
    for (auto const & file : videoList) {
        std::filesystem::path origin_path(file);
        std::filesystem::path output_path = output_home_path_;
        std::stack<std::filesystem::path> path_stack;
        
        while (origin_path != input_home_path_) {
            path_stack.push(origin_path.filename());
            origin_path = origin_path.parent_path();
        }

        while (!path_stack.empty()) {
            if (!std::filesystem::exists(output_path))
                std::filesystem::create_directories(output_path);
            output_path /= path_stack.top();
            path_stack.pop();
        }
        
        config.video_path.assign(std::filesystem::path(file).string());
        config.output_path.assign(output_path.string());
        config.output_rows = 5;

        //insertConfig(config);
        RunSummarize(config);
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

void VideoSummarizerRunner::insertConfig(summarizer::SummarizeConfig const config)
{
    queue_locker_.lock();
    config_queue_.push(config);
    queue_locker_.unlock();
}

summarizer::SummarizeConfig VideoSummarizerRunner::popConfig()
{
    summarizer::SummarizeConfig result;
    queue_locker_.lock();
    result = config_queue_.front();
    config_queue_.pop();
    queue_locker_.unlock();

    return result;
}
