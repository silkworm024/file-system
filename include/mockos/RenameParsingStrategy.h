#pragma once
#include "AbstractParsingStrategy.h"
#include "enums.h"
#include <sstream>
#include <vector>

class RenameParsingStrategy : public AbstractParsingStrategy{
public:
    virtual std::vector<std::string> parse(std::string);
    virtual void setInfo();
    virtual std::string get_info();
private:
    std::string info;
};