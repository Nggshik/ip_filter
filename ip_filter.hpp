#pragma once

#include <string>
#include <vector>

using ipList = std::vector<std::vector<std::string>>;
using ipAddress = std::vector<std::string>;

ipAddress split(const std::string &str, char d);
bool compareIpVector(const ipAddress& firstIp, const ipAddress& secondIp);