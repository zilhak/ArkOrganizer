#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <vector>

namespace summarizer {

struct Matrix {
    int x;
    int y;
};

struct MergeDatga {
    Matrix mergeMat;
    double resizeRatio;
};

Matrix defineFrameMatrix(Matrix const & oneFrameSize, Matrix const & outputImageMaxSize);
bool makeOutputImage(std::vector<cv::Mat> & frameVector, Matrix const & matrix);


} // namespace summarizer

