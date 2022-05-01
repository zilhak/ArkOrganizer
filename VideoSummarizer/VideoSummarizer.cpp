#include "VideoSummarizer.h"

namespace summarizer {

constexpr int FRAME_ROWS = 5;
constexpr int MARGIN = 10;

MergeData defineFrameMatrix(cv::Size const & oneFrameSize, cv::Size const & outputImageSize)
{
    MergeData result;

    int resize_height = (outputImageSize.height / FRAME_ROWS) - MARGIN;
    int resize_width = ((outputImageSize.width * (long long)resize_height) / (5 * (long long)oneFrameSize.height)) - MARGIN;

    result.merge_mat.width = outputImageSize.width / (resize_width + MARGIN);
    result.merge_mat.height = FRAME_ROWS;
    result.resize_mat.width = resize_width;
    result.resize_mat.height = resize_height;

    return result;
}

bool makeOutputImage(std::vector<cv::Mat> & frame_vector, OutputData const & output_data)
{
    if (frame_vector.empty())
        return false;

    cv::Mat output(output_data.output_image_size.height + MARGIN, output_data.output_image_size.width, frame_vector[0].type(), cv::Scalar(240, 240, 240));

    int oneFrameWidth = frame_vector[0].cols;
    int oneFrameHeight = frame_vector[0].rows;

    int pos_x;
    int pos_y = MARGIN;
    for (int y = 0; y < output_data.merge_mat.height; y++) {
        pos_x = MARGIN;
        for (int x = 0; x < output_data.merge_mat.width; x++) {
            cv::Mat roi(output, cv::Rect(pos_x, pos_y, oneFrameWidth, oneFrameHeight));
                                  
            frame_vector[(y * output_data.merge_mat.width) + x].copyTo(roi);
            pos_x += oneFrameWidth + MARGIN;
        }
        pos_y += oneFrameHeight + MARGIN;
    }

    std::string output_path = output_data.file_path + "_ArkOrganizer.jpg";
    cv::imwrite(output_path, output);

    return true;
}

} // namespace summarizer
