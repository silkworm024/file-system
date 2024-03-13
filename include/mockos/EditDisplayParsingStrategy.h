#pragma once
#include "AbstractParsingStrategy.h"

class EditDisplayParsingStrategy : public AbstractParsingStrategy{
    virtual std::vector<std::string> parse(std::string);
    virtual void setInfo();
    virtual std::string get_info();
private:
    std::string info;
};

