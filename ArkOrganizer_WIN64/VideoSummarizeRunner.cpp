#include "pch.h"
#include "VideoSummarizeRunner.h"

void VideoSummarizerRunner::Run()
{

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
