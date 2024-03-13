#pragma once
#include <iostream>
#include <map>
#include <sstream>
#include "mockos/enums.h"
#include "mockos/AbstractFileSystem.h"
#include "mockos/AbstractFileFactory.h"
#include "AbstractParsingStrategy.h"

class AbstractCommand{
public:
    virtual int execute(std::string) = 0;
    virtual void displayInfo() = 0;
    virtual ~AbstractCommand() = default;
};