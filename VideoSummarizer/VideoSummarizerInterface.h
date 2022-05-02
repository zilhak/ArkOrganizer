#include <string>

#ifdef SUMMARIZER
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace summarizer{
constexpr int fhd_resolution_width = 1920;
constexpr int fhd_resolution_height = 1080;

constexpr int       default_resolution_width  = fhd_resolution_width;
constexpr int       default_resolution_height = fhd_resolution_height;
constexpr int       default_output_row        = 5;
constexpr ImageType default_image_type        = ImageType::JPG;
constexpr bool      default_overwite          = false;

enum class ImageType : char {
    JPG,
    PNG
};

struct SummarizeConfig {
    std::string video_path;
    std::string output_path;
    int output_size_width  = default_resolution_width;
    int output_size_height = default_resolution_height;
    int output_rows        = default_output_row;
    ImageType image_type   = default_image_type;
    bool overwite          = default_overwite;
};

DLL_API bool runSummarize(SummarizeConfig const & config_data);

} // namespace summarizer
