#pragma once
#include <sstream>
#include <iterator>
#include "AbstractCommand.h"

class CatCommand : public AbstractCommand{
public:
    CatCommand(AbstractFileSystem *);
    ~CatCommand() = default;
    virtual int execute(std::string);
    virtual void displayInfo();
private:
    AbstractFileSystem * system;
    AbstractFileFactory * factory;
};