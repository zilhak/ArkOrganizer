
#include "VideoSummarizer.h"

#define SUMMARIZER

namespace summarizer {

bool runSummarize(std::string const& video_path, std::string const& output_path)
{
    cv::VideoCapture capture(video_path);
    cv::Mat frame;

    if (capture.isOpened() == false) {
        return false;
    }

    while (1) {
        capture >> frame;
        if (frame.empty()) { // video end
            break;
        }

        //cv::Sobel(frame, frame, frame.depth(), 1, 0);

        cv::imshow("w", frame);

        if (cv::waitKey(10) > 0)
            break;
    }
}

} // namespace summarizer