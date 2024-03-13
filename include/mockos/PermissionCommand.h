#pragma once
#include "AbstractCommand.h"

class PermissionCommand : public AbstractCommand{
public:
    virtual int execute(std::string);
    virtual void displayInfo();
    PermissionCommand(AbstractFileSystem *, AbstractFileFactory *);
    ~PermissionCommand() = default;
private:
    AbstractFileSystem * system;
    AbstractFileFactory * factory;
};