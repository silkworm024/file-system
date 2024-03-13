#include "mockos/SimpleFileSystem.h"
#include "mockos/SimpleFileFactory.h"
#include "mockos/TouchCommand.h"
#include "mockos/CommandPrompt.h"

int main(){

    SimpleFileSystem * sys = new SimpleFileSystem;
    SimpleFileFactory * fac = new SimpleFileFactory;
    TouchCommand * touch = new TouchCommand(sys,fac);

    CommandPrompt cp = CommandPrompt();
    cp.setFileFactory(fac);
    cp.setFileSystem(sys);
    cp.addCommand("touch",touch);

    int result = cp.run();

    return result;
}