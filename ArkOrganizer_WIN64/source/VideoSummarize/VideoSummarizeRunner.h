#pragma once
#include <queue>
#include <mutex>
#include <atomic>
#include <Interface/EventInterface.h>

class VideoSummarizerRunner
{
public:
    VideoSummarizerRunner() { /* EMPTY */ };
    ~VideoSummarizerRunner() { /* EMPTY */ };

public:
    void SetThreadNum        (int thread_num)                        { thread_num_       = thread_num;       }
    void SetInputHomeDirPath (std::wstring const & input_home_path)  { input_home_path_  = input_home_path;  }
    void SetOutputHomeDirPath(std::wstring const & output_home_path) { output_home_path_ = output_home_path; }
    void SetOutputPrefix     (std::wstring const & prefix)           { output_prefix_    = prefix;           }
    void SetOutputSuffix     (std::wstring const & suffix)           { output_suffix_    = suffix;           }

    void SetInputHomeDirPath (std::wstring && input_home_path)  { input_home_path_  = std::move(input_home_path);  }
    void SetOutputHomeDirPath(std::wstring && output_home_path) { output_home_path_ = std::move(output_home_path); }
    void SetOutputPrefix     (std::wstring && prefix)           { output_prefix_    = std::move(prefix);           }
    void SetOutputSuffix     (std::wstring && suffix)           { output_suffix_    = std::move(suffix);           }

    int GetThreadNum()                  const { return thread_num_;       }
    std::wstring GetInputHomeDirPath()  const { return input_home_path_;  }
    std::wstring GetOutputHomeDirPath() const { return output_home_path_; }
    std::wstring GetOutputPrefix()      const { return output_prefix_;    }
    std::wstring GetOutputSuffix()      const { return output_suffix_;    }

    int GetTotalVideoSize() const;
    std::wstring makeOutputPath(std::wstring const & video_path);
    std::wstring makeOutputPath(std::wstring && video_path);

public:
    bool IsReady();
    void Run();

public:
    void InsertFile(std::wstring const & file_name);
    void InsertFileList(std::vector<std::wstring> const & file_list);

private:
    void InsertFileToQueue(std::wstring const file_name);
    void InsertFileListToQueue(std::vector<std::wstring> const & file_list);
    std::wstring GetFileName(size_t index);
    void PopQueue();

private:
    int thread_num_ = 5;

    std::wstring input_home_path_;
    std::wstring output_home_path_;
    std::wstring output_prefix_;
    std::wstring output_suffix_;

    std::atomic<size_t> queue_read_index_;
    std::queue<std::wstring> target_queue_;
    std::mutex queue_locker_;
};
