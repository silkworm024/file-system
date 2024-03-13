#pragma once
#include "mockos/AbstractCommand.h"

class RemoveCommand : public AbstractCommand{
public:
    RemoveCommand(AbstractFileSystem *);
    ~RemoveCommand() = default;
    virtual int execute(std::string);
    virtual void displayInfo();
private:
    AbstractFileSystem * system;
};