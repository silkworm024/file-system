#include "mockos/SimpleFileSystem.h"
#include "mockos/SimpleFileFactory.h"
#include "mockos/LSCommand.h"
#include "mockos/CatCommand.h"
#include "mockos/CopyCommand.h"
#include "mockos/BasicDisplayVisitor.h"
#include "mockos/DisplayCommand.h"
#include "mockos/MacroCommand.h"
#include "mockos/RemoveCommand.h"
#include "mockos/RenameParsingStrategy.h"
#include "mockos/CommandPrompt.h"
#include "mockos/TouchCommand.h"
#include "mockos/EditDisplayParsingStrategy.h"
#include "mockos/PermissionCommand.h"

int main(){
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();

    AbstractCommand * ls = new LSCommand(sfs);
    AbstractCommand * rem = new RemoveCommand(sfs);
    AbstractCommand * touch = new TouchCommand(sfs, sff);
    AbstractCommand * cat = new CatCommand(sfs);
    AbstractCommand * cop = new CopyCommand(sfs);
    AbstractCommand * dis = new DisplayCommand(sfs);
    AbstractCommand * chmod = new PermissionCommand(sfs, sff);

    AbstractParsingStrategy * rename_str = new RenameParsingStrategy;
    AbstractParsingStrategy * catds_str = new EditDisplayParsingStrategy;

    MacroCommand * rename = new MacroCommand(sfs);
    rename->addCommand(cop); rename->addCommand(rem);
    rename->setParseStrategy(rename_str);

    MacroCommand * editDisplay = new MacroCommand(sfs);
    editDisplay->addCommand(cat); editDisplay->addCommand(dis);
    editDisplay->setParseStrategy(catds_str);

    CommandPrompt prompt;

prompt.addCommand("ls", ls);
prompt.addCommand("rm", rem);
prompt.addCommand("touch", touch);
prompt.addCommand("cat", cat);
prompt.addCommand("cp", cop);
prompt.addCommand("ds", dis);
prompt.addCommand("chmod", chmod);
prompt.addCommand("rn", rename);
prompt.addCommand("catds", editDisplay);

int result = prompt.run();
while(result != quit){
    result = prompt.run();
}

delete sfs; delete sff; delete ls; delete rem; delete touch; delete cat; delete cop; delete dis;
    delete chmod; delete rename_str; delete catds_str; delete rename; delete editDisplay;

return result;

};