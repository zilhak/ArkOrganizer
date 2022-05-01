
#include "VideoSummarizerInterface.h"
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

    cv::Size outputImageSize(1920, 1050);
    cv::Size frameSize(capture.get(cv::CAP_PROP_FRAME_HEIGHT), capture.get(cv::CAP_PROP_FRAME_WIDTH));
    MergeData image_data = defineFrameMatrix(frameSize, outputImageSize);
    long long total_frame_count = capture.get(cv::CAP_PROP_FRAME_COUNT);
    int extract_frame_count = image_data.merge_mat.area();
    int frame_jump = total_frame_count / extract_frame_count;
    
    std::vector<cv::Mat> images;

    for (int i = 0; i < image_data.merge_mat.area(); i++) {
        capture.set(cv::CAP_PROP_POS_FRAMES, frame_jump * i);
        capture >> frame;
        cv::Mat resized_frame;
        cv::resize(frame, resized_frame, image_data.resize_mat);
        images.push_back(resized_frame);
    }

    OutputData output_data;
    output_data.output_image_size = outputImageSize;
    output_data.merge_mat = image_data.merge_mat;
    output_data.file_path = video_path;
    makeOutputImage(images, output_data);

    return true;
}

} // namespace summarizer