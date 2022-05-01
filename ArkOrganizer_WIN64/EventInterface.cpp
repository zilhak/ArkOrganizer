#include "EventInterface.h"
#include "pch.h"
#include "../VideoSummarizer/VideoSummarizerInterface.h"

bool RunSummarize(std::string const & base_dir)
{
    return summarizer::runSummarize(base_dir, std::string());
}
