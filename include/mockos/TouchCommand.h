#pragma once
#include <sstream>
#include "AbstractCommand.h"

class TouchCommand : public AbstractCommand{
public:
    TouchCommand(AbstractFileSystem *, AbstractFileFactory *);
    ~TouchCommand() = default;
    virtual int execute(std::string);
    virtual void displayInfo();
private:
    AbstractFileSystem * system;
    AbstractFileFactory * factory;
};