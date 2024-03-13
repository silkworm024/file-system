
#include "mockos/SimpleFileFactory.h"
#include "mockos/SimpleFileSystem.h"
#include "mockos/ImageFile.h"
#include "mockos/TextFile.h"

int main() {
    AbstractFileSystem * basicsys = new SimpleFileSystem;
    AbstractFileFactory * basicfac = new SimpleFileFactory;

    AbstractFile * text1 = basicfac->createFile("text1.txt");
    AbstractFile * img1 = basicfac->createFile("img1.img");
    basicsys->addFile("text1.txt",text1);
    basicsys->addFile("img1.img",img1);

    std::vector<char> textCont = {'H','e','l','l', 'o', ' ','T','h','e','r','e'};
    std::vector<char> imageInput = {'X',' ','X',' ', 'X', ' ','X',' ','X','3'};

    AbstractFile * test1 = basicsys->openFile("text1.txt");
    test1->write(textCont);
    test1->read();
    basicsys->closeFile(text1);

    AbstractFile * test2 = basicsys->openFile("img1.img");
    test2->write(imageInput);
    test2->read();
    basicsys->closeFile(img1);
}
