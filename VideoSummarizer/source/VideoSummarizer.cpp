#include "VideoSummarizer.h"

namespace summarizer {

constexpr int MARGIN = 10;

MergeData DefineFrameMatrix(cv::Size const & oneFrameSize, cv::Size const & outputImageSize, int rows)
{
    MergeData result;

    if (oneFrameSize.width < oneFrameSize.height) {
        rows--;
    }

    int area_height = outputImageSize.height - MARGIN;
    int area_width = outputImageSize.width - MARGIN;
    int resize_height = (area_height / rows);
    double ratio = (double)resize_height / (double)oneFrameSize.height;
    int resize_width = ((double)oneFrameSize.width * ratio);

    result.merge_mat.width = area_width / resize_width;
    result.merge_mat.height = rows;
    result.resize_mat.width = resize_width - MARGIN;
    result.resize_mat.height = resize_height - MARGIN;

    return result;
}

bool MakeOutputImage(std::vector<cv::Mat> & frame_vector, OutputData const & output_data)
{
    if (frame_vector.empty())
        return false;

    cv::Mat output(output_data.output_image_size.height + MARGIN, output_data.output_image_size.width, frame_vector[0].type(), cv::Scalar(240, 240, 240));

    int oneFrameWidth = frame_vector[0].cols;
    int oneFrameHeight = frame_vector[0].rows;

    int pos_x;
    int pos_y = MARGIN;
    int frame_index = 0;
    for (int y = 0; y < output_data.merge_mat.height; y++) {
        pos_x = MARGIN;
        for (int x = 0; x < output_data.merge_mat.width; x++) {
            cv::Mat roi(output, cv::Rect(pos_x, pos_y, oneFrameWidth, oneFrameHeight));
                                  
            frame_vector[frame_index].copyTo(roi);
            frame_index++;
            pos_x += oneFrameWidth + MARGIN;
        }
        pos_y += oneFrameHeight + MARGIN;
    }

    return cv::imwrite(output_data.file_path, output);
}

} // namespace summarizer
