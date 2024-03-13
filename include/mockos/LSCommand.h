#pragma once
#include "AbstractCommand.h"

class LSCommand : public AbstractCommand{
public:
    LSCommand(AbstractFileSystem *);
    ~LSCommand() = default;
    virtual int execute(std::string);
    virtual void displayInfo();
private:
    AbstractFileSystem * system;
    AbstractFileFactory * factory;
};
