#include "VideoSummarizerInterface.h"
#include "VideoSummarizer.h"

#include <experimental/filesystem>
#define SUMMARIZER

namespace summarizer {

bool runSummarize(SummarizeConfig const & config_data)
{
    std::string output_real_path; 
    if (config_data.image_type == ImageType::JPG)
        output_real_path = config_data.output_path + ".jpg";
    else if (config_data.image_type == ImageType::PNG)
        output_real_path = config_data.output_path + ".png";
    
    if (config_data.overwite == false && std::experimental::filesystem::exists(output_real_path) == false)
        return false;
    
    cv::VideoCapture capture(config_data.video_path);
    if (capture.isOpened() == false) {
        return false;
    }

    cv::Mat frame;
    cv::Size outputImageSize(config_data.output_size_width, config_data.output_size_height);
    cv::Size frameSize(capture.get(cv::CAP_PROP_FRAME_HEIGHT), capture.get(cv::CAP_PROP_FRAME_WIDTH));

    MergeData image_data = defineFrameMatrix(frameSize, outputImageSize, config_data.output_rows);

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
    output_data.file_path = config_data.output_path;
    makeOutputImage(images, output_data);

    return true;
}

} // namespace summarizer