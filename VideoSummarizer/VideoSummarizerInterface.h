#include <string>

#ifdef SUMMARIZER
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

namespace summarizer{

DLL_API bool runSummarize(std::string const & video_path, std::string const & output_path);

} // namespace summarizer
