#include "pch.h"
#include "EventInterface.h"

bool RunSummarize(summarizer::SummarizeConfig const & config)
{
    return summarizer::VideoSummarize(config);
}
