#include "mockos/MacroCommand.h"

 MacroCommand::MacroCommand(AbstractFileSystem * sfs)
 :system(sfs), strategy(nullptr){}

void MacroCommand::displayInfo() {
    strategy->setInfo();
    std::cout << strategy->get_info() << std::endl;
}

int MacroCommand::execute(std::string name) {
std::vector<std::string> input = strategy->parse(name);
for(unsigned int i = 0; i < commands.size(); ++i){
    int result = commands[i]->execute(input[i]);
    if(result != success){
        return result;
    }
}
return success;
}

void MacroCommand::addCommand(AbstractCommand * command) {
    commands.push_back(command);
}

void MacroCommand::setParseStrategy(AbstractParsingStrategy * str) {
    strategy = str;
}

