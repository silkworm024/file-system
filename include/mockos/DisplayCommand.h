#pragma once
#include "mockos/AbstractCommand.h"

class DisplayCommand : public AbstractCommand {
public:
    DisplayCommand(AbstractFileSystem *);
    ~DisplayCommand() = default;
    virtual int execute(std::string);
    virtual void displayInfo();
private:
    AbstractFileSystem * system;
    AbstractFileFactory * factory;
};
