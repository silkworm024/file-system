#pragma once
#include "AbstractCommand.h"

class CommandPrompt{
public:
    CommandPrompt();
    ~CommandPrompt() = default;
    void setFileSystem(AbstractFileSystem *);
    void setFileFactory(AbstractFileFactory *);
    int addCommand(std::string, AbstractCommand *);
    int run();
protected:
    void listCommands();
    std::string prompt();
private:
    std::map<std::string, AbstractCommand *> commands;
    AbstractFileSystem * system;
    AbstractFileFactory * factory;
};