#pragma once
#include "AbstractCommand.h"
#include "AbstractParsingStrategy.h"

class MacroCommand : public AbstractCommand{
public:
    MacroCommand(AbstractFileSystem *);
    virtual int execute(std::string);
    virtual void displayInfo();
    void addCommand(AbstractCommand *);
    void setParseStrategy(AbstractParsingStrategy *);
     ~MacroCommand() = default;
private:
    AbstractFileSystem * system;
    std::vector<AbstractCommand *> commands;
    AbstractParsingStrategy * strategy;
    std::string info;
};