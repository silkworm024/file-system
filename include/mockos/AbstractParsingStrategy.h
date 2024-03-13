#pragma once
#include <iostream>
#include <vector>

class AbstractParsingStrategy{
public:
    virtual std::vector<std::string> parse(std::string) = 0;
    virtual void setInfo() = 0;
    virtual std::string get_info() = 0;
    virtual ~AbstractParsingStrategy() = default;
};