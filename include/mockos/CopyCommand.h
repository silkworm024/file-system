#pragma once
#include "mockos/AbstractCommand.h"

class CopyCommand: public AbstractCommand {
public:
    CopyCommand(AbstractFileSystem * sys);
    ~CopyCommand() = default;
    virtual int execute(std::string name);
    virtual void displayInfo();
private:
    AbstractFileSystem * system;
    AbstractFileFactory * factory;
};