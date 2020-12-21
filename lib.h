#pragma once

#include <string>
#include <cassert>
#include <vector>

int version();
bool compareIpVector(const std::vector<std::string>& firstIp, const std::vector<std::string>& secondIp);

template<typename Iter>
bool isMatch(Iter begin, Iter end)
{
    UNUSED(begin);
    UNUSED(end);
    return true;
}

template<typename Iter,typename T, typename... Args>
bool isMatch(Iter begin, Iter end,T arg, Args... args)
{
    assert(begin != end);
    if(!isMatch(begin+1,end,args...))
        return false;
    if(std::stoi(*begin) == arg)
        return true;
    return false;
}

