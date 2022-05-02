#include "EventInterface.h"
#include "pch.h"
#include "../VideoSummarizer/VideoSummarizerInterface.h"

bool RunSummarize(summarizer::SummarizeConfig const & config)
{
    return summarizer::runSummarize(config);
}
