#include "gtest/gtest.h"

#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"
#include "mockos/SimpleFileSystem.h"

using namespace std;

TEST(textfile,constructor){ // checks that the file is initialized with proper name and size, expects size to be 0 and the name to match the input to the constructor
    std::string fileName = "FileName.txt";
    unsigned int fileSize = 0;
    TextFile t(fileName);
    ASSERT_EQ(fileName, t.getName());
    ASSERT_EQ(fileSize, t.getSize());
}

TEST(textfile,write){ // tests write, expects that the function returns success and that the size of the file is updated correctly
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    ASSERT_EQ(0, t.write(v));
    ASSERT_EQ(static_cast<unsigned int>(v.size()), t.getSize());
}


TEST(textfile,append){ // tests append, expects the write and append functions to return 0 and the size of the file to update correctly
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    ASSERT_EQ(0, t.write(v));
    unsigned int fileSize = t.getSize();
    ASSERT_EQ(0, t.append(v));
    ASSERT_EQ(static_cast<unsigned int>(fileSize + v.size()), t.getSize());
}

TEST(textfile,read){ // tests that the read function outputs the contents of the file
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    int resWrite = t.write(v);
    // REDIRECT STD STREAM
    streambuf* backup;
    backup = cout.rdbuf();
    stringstream ss;
    cout.rdbuf(ss.rdbuf());
    t.read();
    string wordShouldBe = "hi";
    string word;
    ss >> word;
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup);
    ASSERT_EQ(wordShouldBe, word);
    ASSERT_EQ(0, resWrite);
}

TEST(textfile,readwithAppend){ // tests that read also works with appending to a file
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    ASSERT_EQ(0, t.write(v));
    unsigned int fileSize = t.getSize();
    ASSERT_EQ(0, t.append(v));
    ASSERT_EQ(static_cast<unsigned int>(fileSize + v.size()), t.getSize());
    // REDIRECT STD STREAM
    streambuf* backup;
    backup = cout.rdbuf();
    stringstream ss;
    cout.rdbuf(ss.rdbuf());
    t.read();
    string wordShouldBe = "hihi";
    string word;
    ss >> word;
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup);
    ASSERT_EQ(wordShouldBe, word);
}

TEST(imagefile,constructor) { // checks that the file is initialized with proper name and size, expects size to be 0 and the name to match the input to the constructor
    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    ASSERT_EQ(fileName, t.getName());
    ASSERT_EQ(fileSize, t.getSize());
}

TEST(imagefile,writeValid) { // tests write with a valid vector input, expects write to return success, and the size of the contents to be equal to that of the input vector -1 (for the last index that is removed
    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
    ASSERT_EQ(0, t.write(v));
    ASSERT_EQ(static_cast<unsigned int>(v.size() - 1), t.getSize());
}

TEST(imagefile,writeSizeMismatch) { // tests write with a size mismatch in the input vector, expects write to return a non-zero value and the size of the contents to remain 0
    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '4' };
    ASSERT_NE(0, t.write(v)); // non-zero error returned
    ASSERT_EQ(fileSize, t.getSize()); // contents not added
}

TEST(imagefile,writeInvalidPixel) { // tests write with an invalid pixel in the input vector, expects write to return a non-zero value and the size of the contents to remain 0
    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', '3' };
    ASSERT_NE(0, t.write(v));
    ASSERT_EQ(fileSize, t.getSize()); // contents not added
}

TEST(imagefile,appendInvalid) { // tests that append returns a non-zero value (can't append to an image)
    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', '3' };
    ASSERT_NE(0, t.append(v)); // can't append to image
}

TEST(imagefile,read) { // tests that read prints out the contents that are written to the file
    std::string fileName = "FileName.img";
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
    ASSERT_EQ(0, t.write(v));
    // REDIRECT STD STREAM
    streambuf* backup;
    backup = cout.rdbuf();
    stringstream ss;
    cout.rdbuf(ss.rdbuf());
    t.read();
    string outputShouldBe = "X";
    string word;
    int count = 0;
    while (ss >> word) {
        ASSERT_EQ(outputShouldBe, word);
        ++count;
    }
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup);
    ASSERT_EQ(5, count);
}

TEST(simpleFileSystem,createFileValid){ // creates a valid (unused) file and expects 0 (success) as a return value
    SimpleFileSystem sfs;
    ASSERT_EQ(0, sfs.createFile("FileName.img"));
    ASSERT_EQ(0, sfs.createFile("FileName.txt"));
}

TEST(simpleFileSystem,createFileAlreadyExists){ // creates a file that has already been created, expects a non-zero return value
    SimpleFileSystem sfs;
    ASSERT_EQ(0, sfs.createFile("FileName.img"));
    ASSERT_NE(0, sfs.createFile("FileName.img")); // accepts any non-zero value
}

TEST(simpleFileSystem,createUnknownExtension){ // creates a file with an unknown extension, expects a non-zero return value
    SimpleFileSystem sfs;
    ASSERT_NE(0, sfs.createFile("FileName.bla"));
}

TEST(simpleFileSystem,addValid){ // adds two different files to the system, expects success as return value both times
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    TextFile* txt = new TextFile("FileName.txt");
    ASSERT_EQ(0, sfs.addFile(img->getName(), img));
    ASSERT_EQ(0, sfs.addFile(txt->getName(), txt));
}

TEST(simpleFileSystem,addNullFile){ // adds a nullptr to the filesystem, expects a non-zero return value
    SimpleFileSystem sfs;
    ImageFile* img = nullptr;
    ASSERT_NE(0, sfs.addFile("FileName.img", img));
}

TEST(simpleFileSystem,addFileAlreadyExists){ // adds the same file twice, the first time should return success, the second time should return a non-zero value
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    ASSERT_EQ(0, sfs.addFile(img->getName(), img));
    ASSERT_NE(0, sfs.addFile(img->getName(), img));
}

TEST(simpleFileSystem,deleteValid){ // deletes a valid file (a file that exists and is not open), expects 0 as a return value
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    ASSERT_EQ(0, sfs.addFile(img->getName(), img));
    ASSERT_EQ(0, sfs.deleteFile(img->getName()));
}

TEST(simpleFileSystem,deleteFileDoesNotExist){ // deletes a file that has not been added, expects a non-zero return value
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    ASSERT_NE(0, sfs.deleteFile(img->getName()));
}

TEST(simpleFileSystem,openValid){ //  opens a valid file that exists and is not already open -- checked using add and create methods
    SimpleFileSystem sfs;
    // check using add -- expect to see the same file returned
    AbstractFile* img = new ImageFile("FileName.img");
    ASSERT_EQ(0, sfs.addFile(img->getName(), img));
    AbstractFile* res1 = sfs.openFile(img->getName());
    bool sameAddress = &(*img) == &(*res1);
    ASSERT_TRUE(sameAddress);

    // check using create -- a quick check to see that create adds successfully and open finds the file by returning a pointer that  is not null
    ASSERT_EQ(0, sfs.createFile("FileName.txt"));
    AbstractFile* res2 = sfs.openFile("FileName.txt");
    bool nullCheck = res2 == nullptr;
    ASSERT_FALSE(nullCheck);
}

TEST(simpleFileSystem,openFileNotAdded){ // opens a file that has not been added, expects a null pointer
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    AbstractFile* res1 = sfs.openFile(img->getName());
    bool isNull = res1 == nullptr;
    ASSERT_TRUE(isNull);
}

TEST(simpleFileSystem,openAlreadyOpenedFile){ // opens a file twice, the first time should return the same file, the second time should return nullptr
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    ASSERT_EQ(0, sfs.addFile(img->getName(), img));
    AbstractFile* firstOpen = sfs.openFile(img->getName());
    bool sameAddress = &(*img) == &(*firstOpen);
    ASSERT_TRUE(sameAddress);
    AbstractFile* secondOpen = sfs.openFile(img->getName());
    bool isNull = secondOpen == nullptr;
    ASSERT_TRUE(isNull);
}

TEST(simpleFileSystem,closeValid){ // closes a file that has been added and opened, expect success
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    sfs.addFile(img->getName(), img);
    sfs.openFile(img->getName());
    int res1 = sfs.closeFile(img);
    ASSERT_EQ(0, res1);
}

TEST(simpleFileSystem,closeNotOpen){ // closes a file that has been added but not opened, expects a non-zero return value
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    ASSERT_EQ(0, sfs.addFile(img->getName(), img));
    ASSERT_NE(0, sfs.closeFile(img));
}

TEST(simpleFileSystem,closeNotAdded){ // closes a file that has not been added or opened, expects a non-zero return value
    SimpleFileSystem sfs;
    ImageFile* img = new ImageFile("FileName.img");
    ASSERT_NE(0, sfs.closeFile(img));
}