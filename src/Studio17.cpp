#include "mockos/ImageFile.h"
#include "mockos/SimpleFileSystem.h"

int main() {
    std::string filename = "image";

    ImageFile image = ImageFile(filename);

    std::vector<char> input = {'X',' ','X',' ', 'X', ' ','X',' ','X','3'};

    int wresult = image.write(input);
    std::cout << wresult << std::endl;
    image.read();

    SimpleFileSystem system;
    AbstractFile * image2 = new ImageFile("image");
    system.addFile("image", image2);
    //system.createFile("image.txt");
}