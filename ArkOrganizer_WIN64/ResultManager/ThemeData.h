#pragma once

class Theme
{
    Theme* instance_;
    Theme() {};

public:
    static void setIndex(int i);
    static Theme* getInstance()
    {
        return instance_;
    }
};
