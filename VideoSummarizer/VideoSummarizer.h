#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <vector>

namespace summarizer {

struct MergeData {
    cv::Size merge_mat;
    cv::Size resize_mat;
};

struct OutputData {
    cv::Size merge_mat;
    cv::Size output_image_size;
    std::string file_path;
};

MergeData defineFrameMatrix(cv::Size const & one_frame_size, cv::Size const & output_image_size);
bool makeOutputImage(std::vector<cv::Mat> & frame_vector, OutputData const & output_data);

} // namespace summarizer

