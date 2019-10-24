#pragma once

#include<string>
class error
{
    std::string s;
    public:
        error(std::string p):s(p){}
        std::string what()
        {
            return s;
        }
};