
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
    std::vector<char> content = test1->read();
    for(int i = 0; i < content.size(); ++i){
        std::cout << content[i];
    }
    std::cout << std::endl;
    content = {'H','e','l','l', 'o'};
    test1->write(content);
    content = test1->read();

    for(int i = 0; i < content.size(); ++i){
                std::cout << content[i];
            }
    std::cout << std::endl;
    // basicsys->closeFile(text1);


    AbstractFile * test2 = basicsys->openFile("img1.img");
    test2->write(imageInput);
    std::vector<char> content1 = test2->read();
    content1 = {'X','X','X','X', 'X', 'X','X','X','X','3'};
    test2->write(content1);

    for(int i = 2; i >= 0; --i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << content1[3 * i + j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    basicsys->closeFile(img1);
}
