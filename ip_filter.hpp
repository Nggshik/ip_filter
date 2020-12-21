#pragma once

#include <string>
#include <vector>


#define UNUSED(x) (void)(x)

using ipAddress = std::vector<std::string>;
using ipList = std::vector<ipAddress>;


ipAddress split(const std::string &str, char d);
bool compareIpVector(const ipAddress& firstIp, const ipAddress& secondIp);
