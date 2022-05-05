#include <string>
#include <vector>

#ifdef SUMMARIZER
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace summarizer{
enum class ImageType : char {
    JPG,
    PNG
};

constexpr int fhd_resolution_width = 1920;
constexpr int fhd_resolution_height = 1080;

constexpr int       default_resolution_width  = fhd_resolution_width;
constexpr int       default_resolution_height = fhd_resolution_height;
constexpr int       default_output_row        = 5;
constexpr ImageType default_image_type        = ImageType::JPG;
constexpr bool      default_overwite          = false;

struct SummarizeConfig {
    std::string video_path;
    std::string output_path;
    int output_size_width  = default_resolution_width;
    int output_size_height = default_resolution_height;
    int output_rows        = default_output_row;
    ImageType image_type   = default_image_type;
    bool overwite          = default_overwite;
};

DLL_API bool VideoSummarize(SummarizeConfig const & config_data);


DLL_API class ImageViewer 
{
using PauseCode = char;
public:
    ImageViewer() {};
    ImageViewer(std::vector<std::string> const & image_paths);
public:
   DLL_API void SetImageList(std::vector<std::string> const & image_paths);
   DLL_API PauseCode RunImageViewer(size_t start_index = 0);
   DLL_API PauseCode Resume();
   DLL_API std::string GetCurImagePath();

private:
    int index_ = 0;
    std::vector<std::string> image_list_;
};

} // namespace summarizer
