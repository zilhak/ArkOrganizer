#include "pch.h"
#include "VideoSummarizeRunner.h"
#include "PathUtil.h"

void VideoSummarizerRunner::Run()
{
    summarizer::SummarizeConfig config;
    std::vector<std::string> fileList = util::path::MakeFilePathList(input_home_path_, nullptr);
    for (auto const & file : fileList) {
        config.video_path = file;

        insertConfig(config);
    }
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
