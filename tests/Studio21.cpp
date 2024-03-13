#include "gtest/gtest.h"

#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"
#include "mockos/SimpleFileSystem.h"
#include "mockos/SimpleFileFactory.h"
#include "mockos/BasicDisplayVisitor.h"
#include "mockos/MetadataDisplayVisitor.h"
#include "mockos/PasswordProxy.h"
#include "mockos/TouchCommand.h"
#include "mockos/CommandPrompt.h"

#include "CommandTest.h"

#include <algorithm>

using namespace std;

/*
// checks that the file is initialized with proper name and size,
// expects size to be 0 and the name to match the input to the constructor
*/
TEST(textFile,constructor){
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    std::string fileName = "FileName.txt";
    unsigned int fileSize = 0;
    TextFile t(fileName);
    ASSERT_EQ(fileName, t.getName());
    ASSERT_EQ(fileSize, t.getSize());
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(textFile, write){ // tests write, expects that the function returns success and that the size of the file is updated correctly
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    ASSERT_EQ(0, t.write(v));
    ASSERT_EQ(static_cast<unsigned int>(v.size()), t.getSize());
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(textFile,append) { // tests append, expects the write and append functions to return 0 and the size of the file to update correctly
// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    ASSERT_EQ(0, t.write(v));
    unsigned int fileSize = t.getSize();
    ASSERT_EQ(0, t.append(v));
    ASSERT_EQ(static_cast<unsigned int>(fileSize + v.size()), t.getSize());
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(textFile,read) { // tests that the read function outputs the contents of the file
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    ASSERT_EQ(0, t.write(v));
    std::vector<char> contents = t.read();
    ASSERT_EQ(v.size(), (size_t)t.getSize());
    ASSERT_EQ(v.size(), contents.size());
    for (size_t i = 0; i < contents.size(); ++i) {
        ASSERT_EQ(contents[i], v[i]);
    }
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(textFile,readWithAppend) { // tests that read also works with appending to a file
// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    ASSERT_EQ(0, t.write(v));
    ASSERT_EQ(0, t.append(v));
    std::vector<char> newExpectedV = { 'h', 'i',  'h', 'i' };
    std::vector<char> contents = t.read();
    ASSERT_EQ(static_cast<unsigned int>(newExpectedV.size()), t.getSize());
    ASSERT_EQ(newExpectedV.size(), contents.size());
    for (size_t i = 0; i < contents.size(); ++i) {
        ASSERT_EQ(contents[i], newExpectedV[i]);
    }
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(imageFile,constructor) { // checks that the file is initialized with proper name and size, expects size to be 0 and the name to match the input to the constructor
// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    ASSERT_EQ(fileName, t.getName());
    ASSERT_EQ(fileSize, t.getSize());
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(imageFile,writeValid) { // tests write with a valid vector input, expects write to return success, and the size of the contents to be equal to that of the input vector -1 (for the last index that is removed
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
    ASSERT_EQ(0, t.write(v));
    ASSERT_EQ(static_cast<unsigned int>(v.size() - 1), t.getSize());
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(imageFile,writeSizeMismatch) { // tests write with a size mismatch in the input vector, expects write to return a non-zero value and the size of the contents to remain 0
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', 4 };
    ASSERT_NE(0, t.write(v)); // non-zero error returned
    ASSERT_EQ(fileSize, t.getSize()); // contents not added
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(imageFile,writeInvalidPixel) { // tests write with an invalid pixel in the input vector, expects write to return a non-zero value and the size of the contents to remain 0
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', 3 };
    ASSERT_NE(0, t.write(v));
    ASSERT_EQ(fileSize, t.getSize()); // contents not added
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(imageFile,appendInvalid) { // tests that append returns a non-zero value (can't append to an image)
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    std::string fileName = "FileName.img";
    unsigned int fileSize = 0;
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', '3' };
    ASSERT_NE(0, t.append(v)); // can't append to image
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(imageFile,read) { // tests that read returns the contents that are written to the file
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    std::string fileName = "FileName.img";
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
    ASSERT_EQ(0, t.write(v));
    std::vector<char> contents = t.read();
    ASSERT_EQ(v.size() - 1, contents.size());
    for (size_t i = 0; i < contents.size(); ++i) {
        ASSERT_EQ(v[i], contents[i]);
    }
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileSystem,addValid) { // adds two different files to the system, expects success as return value both times
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileSystem sfs;
    SimpleFileFactory sff;
    AbstractFile* img = sff.createFile("FileName.img");
    AbstractFile* txt = sff.createFile("FileName.txt");
    ASSERT_EQ(0, sfs.addFile(img->getName(), img));
    ASSERT_EQ(0, sfs.addFile(txt->getName(), txt));
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileSystem,addNullFile) { // adds a nullptr to the filesystem, expects a non-zero return value
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileSystem sfs;
    ImageFile* img = nullptr;
    ASSERT_NE(0, sfs.addFile("FileName.img", img));
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileSystem,addFileAlreadyExists) { // adds the same file twice, the first time should return success, the second time should return a non-zero value
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileSystem sfs;
    SimpleFileFactory sff;
    AbstractFile* img = sff.createFile("FileName.img");
    ASSERT_EQ(0, sfs.addFile(img->getName(), img));
    ASSERT_NE(0, sfs.addFile(img->getName(), img));
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileSystem,deleteValid) { // deletes a valid file (a file that exists and is not open), expects 0 as a return value
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileSystem sfs;
    SimpleFileFactory sff;
    AbstractFile* img = sff.createFile("FileName.img");
    ASSERT_EQ(0, sfs.addFile(img->getName(), img));
    ASSERT_EQ(0, sfs.deleteFile(img->getName()));
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileSystem,deleteFileDoesNotExist) { // deletes a file that has not been added, expects a non-zero return value
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileSystem sfs;
    SimpleFileFactory sff;
    AbstractFile* img = sff.createFile("FileName.img");
    ASSERT_NE(0, sfs.deleteFile(img->getName()));
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileSystem,openValid) { //  opens a valid file that exists and is not already open, expect to see the same file returned
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileSystem sfs;
    SimpleFileFactory sff;
    AbstractFile* img = sff.createFile("FileName.img");
    ASSERT_EQ(0, sfs.addFile(img->getName(), img));
    AbstractFile* res1 = sfs.openFile(img->getName());
    bool sameAddress = &(*img) == &(*res1);
    ASSERT_TRUE(sameAddress);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileSystem,openFileNotAdded) { // opens a file that has not been added, expects a null pointer
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileSystem sfs;
    SimpleFileFactory sff;
    AbstractFile* img = sff.createFile("FileName.img");
    AbstractFile* res1 = sfs.openFile(img->getName());
    bool isNull = res1 == nullptr;
    ASSERT_TRUE(isNull);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileSystem,openAlreadyOpenedFile) { // opens a file twice, the first time should return the same file, the second time should return nullptr
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileSystem sfs;
    SimpleFileFactory sff;
    AbstractFile* img = sff.createFile("FileName.img");
    ASSERT_EQ(0, sfs.addFile(img->getName(), img));
    AbstractFile* firstOpen = sfs.openFile(img->getName());
    bool sameAddress = &(*img) == &(*firstOpen);
    ASSERT_TRUE(sameAddress);
    AbstractFile* secondOpen = sfs.openFile(img->getName());
    bool isNull = secondOpen == nullptr;
    ASSERT_TRUE(isNull);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileSystem,closeValid) { // closes a file that has been added and opened, expect success
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileSystem sfs;
    SimpleFileFactory sff;
    AbstractFile* img = sff.createFile("FileName.img");
    sfs.addFile(img->getName(), img);
    sfs.openFile(img->getName());
    int res1 = sfs.closeFile(img);
    ASSERT_EQ(0, res1);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileSystem,closeNotOpen) { // closes a file that has been added but not opened, expects a non-zero return value
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileSystem sfs;
    SimpleFileFactory sff;
    AbstractFile* img = sff.createFile("FileName.img");
    ASSERT_EQ(0, sfs.addFile(img->getName(), img));
    ASSERT_NE(0, sfs.closeFile(img));
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileSystem,closeNotAdded) { // closes a file that has not been added or opened, expects a non-zero return value
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileSystem sfs;
    SimpleFileFactory sff;
    AbstractFile* img = sff.createFile("FileName.img");
    ASSERT_NE(0, sfs.closeFile(img));
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileFactory,createFileValid) { // creates two files by calling create on the file factory, the calls should return the new file objects that are both not null
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileFactory sff;
    AbstractFile* res1 = sff.createFile("FileName.img");
    bool isNull1 = res1 == nullptr;
    ASSERT_FALSE(isNull1);
    AbstractFile* res2 = sff.createFile("FileName.txt");
    bool isNull2 = res2 == nullptr;
    ASSERT_FALSE(isNull2);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(simpleFileFactory,createUnknownExtension) { // when a bad extension is passed, the factory should pass back a nullptr
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());

    SimpleFileFactory sfs;
    AbstractFile* res1 = sfs.createFile("FileName.bla");
    bool isNull = res1 == nullptr;
    ASSERT_TRUE(isNull);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(basicDisplayVisitor,visitTextFile) { // tests output of basic display visitor for a text file, expects the contents of the file
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    int resWrite = t.write(v);
    // REDIRECT STD STREAM
    streambuf* backup;
    backup = cout.rdbuf();
    stringstream ss;
    cout.rdbuf(ss.rdbuf());
    AbstractFileVisitor* bdv = new BasicDisplayVisitor;
    t.accept(bdv);
    string wordShouldBe = "hi";
    string word;
    ss >> word;
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup);
    ASSERT_EQ(wordShouldBe, word);
    ASSERT_EQ(0, resWrite);
}

TEST(basicDisplayVisitor,visitImageFile) { // tests the output the basic display visitor for an image file, expects 5 Xs
    std::string fileName = "FileName.img";
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
    ASSERT_EQ(0, t.write(v));
    // REDIRECT STD STREAM
    streambuf* backup;
    backup = cout.rdbuf();
    stringstream ss;
    cout.rdbuf(ss.rdbuf());
    AbstractFileVisitor* bdv = new BasicDisplayVisitor;
    t.accept(bdv);
    string outputShouldBe = "X";
    string word;
    int count = 0;
    while (ss >> word) { // no skip ws -- wont skip white space! would have to extract one character at a time
        ASSERT_EQ(outputShouldBe, word);
        ++count;
    }
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup);
    ASSERT_EQ(5, count);
}

TEST(metadataDisplayVisitor,visitTextFile) { // tests the output of the metadata display visitor for a text file, expects the filename, type and size to be included in the print statement
    std::string fileName = "FileName.txt";
    TextFile t(fileName);
    std::vector<char> v = { 'h', 'i' };
    ASSERT_EQ(0, t.write(v));
    // REDIRECT STD STREAM
    streambuf* backup;
    backup = cout.rdbuf();
    stringstream ss;
    cout.rdbuf(ss.rdbuf());
    AbstractFileVisitor* bdv = new MetadataDisplayVisitor;
    t.accept(bdv);
    string word;
    std::vector<string> printedWords;
    while (ss >> word) {
        printedWords.push_back(word);
    }
    std::vector<string>::iterator it1;
    std::vector<string>::iterator it2;
    std::vector<string>::iterator it3;
    it1 = std::find(printedWords.begin(), printedWords.end(), fileName);
    bool notEqual1 = it1 == printedWords.end();
    ASSERT_FALSE(notEqual1);
    it2 = std::find(printedWords.begin(), printedWords.end(), to_string(t.getSize()));
    bool notEqual2 = it2 == printedWords.end();
    ASSERT_FALSE(notEqual2);
    it3 = std::find(printedWords.begin(), printedWords.end(), "text");
    bool notEqual3 = it3 == printedWords.end();
    ASSERT_FALSE(notEqual3);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup);
}

TEST(metadataDisplayVisitor,visitImageFile) { // tests the output of the metadata display visitor for an image file, expects the filename, type and size to be included in the output
    std::string fileName = "FileName.img";
    ImageFile t(fileName);
    std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
    ASSERT_EQ(0, t.write(v));
    // REDIRECT STD STREAM
    streambuf* backup;
    backup = cout.rdbuf();
    stringstream ss;
    cout.rdbuf(ss.rdbuf());
    AbstractFileVisitor* bdv = new MetadataDisplayVisitor;
    t.accept(bdv);
    string word;
    std::vector<string> printedWords;
    while (ss >> word) {
        printedWords.push_back(word);
    }
    std::vector<string>::iterator it1;
    std::vector<string>::iterator it2;
    std::vector<string>::iterator it3;
    it1 = std::find(printedWords.begin(), printedWords.end(), fileName);
    bool notEqual1 = it1 == printedWords.end();
    ASSERT_FALSE(notEqual1);
    it2 = std::find(printedWords.begin(), printedWords.end(), to_string(t.getSize()));
    bool notEqual2 = it2 == printedWords.end();
    ASSERT_FALSE(notEqual2);
    it3 = std::find(printedWords.begin(), printedWords.end(), "image");
    bool notEqual3 = it3 == printedWords.end();
    ASSERT_FALSE(notEqual3);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup);
}

TEST(passwordProxy,constructor) { // we expect the name and size of the password proxy to match that of the text file it is assigned with
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    unsigned int fileSize = 0;
    // EXPECTATIONS FOR CONSTRUCTION
    ASSERT_EQ(fileName, pp->getName());
    ASSERT_EQ(fileSize, pp->getSize());
    ASSERT_EQ(fileName, realfile->getName());
    ASSERT_EQ(fileSize, realfile->getSize());

    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}

TEST(passwordProxy,writeValidPassword) { // with a valid password, we would expect the size of the pasword proxy and realfile to be updated and return the same value (the size of the vector)
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    vector<char> v = { 'h', 'i' };
    // REDIRECT COUT STREAM
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // REDIRECT CIN STREAM
    streambuf* backup_in;
    backup_in = cin.rdbuf();
    stringstream ss_in;
    cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    ss_in << password;
    // EXPECTATIONS FOR FUNCTION -- VALID PASSWORD
    ASSERT_EQ(0, pp->write(v));
    ASSERT_EQ(static_cast<unsigned int>(v.size()), pp->getSize());
    ASSERT_EQ(static_cast<unsigned int>(v.size()), realfile->getSize());
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
    // ASSIGN CIN BACK TO STDIN
    cin.rdbuf(backup_in);
}

TEST(passwordProxy,writeInvalidPassword) { // if an incorrect password is given, write should not execute and the size of both the password proxy and the real file should remain 0
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    vector<char> v = { 'h', 'i' };
    // REDIRECT COUT STREAM
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // REDIRECT CIN STREAM
    streambuf* backup_in;
    backup_in = cin.rdbuf();
    stringstream ss_in;
    cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    string wrongPassword = "s9K3qL";
    ss_in << wrongPassword;
    // EXPECTATIONS FOR FUNCTION -- INVALID PASSWORD
    ASSERT_NE(0, pp->write(v));
    ASSERT_EQ(static_cast<unsigned int>(0), pp->getSize());
    ASSERT_EQ(static_cast<unsigned int>(0), realfile->getSize());
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
    // ASSIGN CIN BACK TO STDIN
    cin.rdbuf(backup_in);
}

TEST(passwordProxy,appendValidPassword) { // we expect that if a good password is given for write and for append, then the proxy and real file should both only have their sizes updated accordingly
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    vector<char> v = { 'h', 'i' };
    // REDIRECT COUT STREAM
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // REDIRECT CIN STREAM
    streambuf* backup_in;
    backup_in = cin.rdbuf();
    stringstream ss_in;
    cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    ss_in << password + '\n' + password;
    // EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
    ASSERT_EQ(0, pp->write(v));
    ASSERT_EQ(static_cast<unsigned int>(v.size()), pp->getSize());
    ASSERT_EQ(static_cast<unsigned int>(v.size()), realfile->getSize());
    unsigned int fileSize = pp->getSize();
    // EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
    ASSERT_EQ(0, pp->append(v));
    ASSERT_EQ(static_cast<unsigned int>(fileSize + v.size()), pp->getSize());
    ASSERT_EQ(static_cast<unsigned int>(fileSize + v.size()), realfile->getSize());
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
    // ASSIGN CIN BACK TO STDIN
    cin.rdbuf(backup_in);
}

TEST(passwordProxy,appendInvalidPassword) { //  we expect that if a good password is given for write, but an incorrect password is given for append, then the proxy and real file should both only have their sizes updated from the first write
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    vector<char> v = { 'h', 'i' };
    // REDIRECT COUT STREAM
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // REDIRECT CIN STREAM
    streambuf* backup_in;
    backup_in = cin.rdbuf();
    stringstream ss_in;
    cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    string wrongPassword = "a5lsdIK3";
    ss_in << password + '\n' + wrongPassword;
    // EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
    ASSERT_EQ(0, pp->write(v));
    ASSERT_EQ(static_cast<unsigned int>(v.size()), pp->getSize());
    ASSERT_EQ(static_cast<unsigned int>(v.size()), realfile->getSize());
    unsigned int fileSize = pp->getSize();
    // EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
    ASSERT_NE(0, pp->append(v));
    ASSERT_EQ(static_cast<unsigned int>(fileSize), pp->getSize());
    ASSERT_EQ(static_cast<unsigned int>(fileSize), realfile->getSize());
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
    // ASSIGN CIN BACK TO STDIN
    cin.rdbuf(backup_in);
}

TEST(passwordProxy,readValidPassword) { // we would expect to see the effects of writing to the proxy with a valid password in the content returned by the read function -- when a valid password is given -- this should also match the read content of the real file
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    vector<char> v = { 'h', 'i' };
    // REDIRECT COUT STREAM
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // REDIRECT CIN STREAM
    streambuf* backup_in;
    backup_in = cin.rdbuf();
    stringstream ss_in;
    cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    ss_in << password + '\n' + password;
    // EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
    ASSERT_EQ(0, pp->write(v));
    ASSERT_EQ(static_cast<unsigned int>(v.size()), pp->getSize());
    ASSERT_EQ(static_cast<unsigned int>(v.size()), realfile->getSize());
    // EXPECTATIONS FOR SECOND FUNCTION -- VALID PASSWORD
    std::vector<char> contentsPP = pp->read();
    ASSERT_EQ(v.size(), contentsPP.size());
    for (size_t i = 0; i < contentsPP.size(); ++i) {
        ASSERT_EQ(contentsPP[i], v[i]);
    }
    std::vector<char> contentsRF = realfile->read();
    ASSERT_EQ(v.size(), contentsRF.size());
    for (size_t i = 0; i < contentsRF.size(); ++i) {
        ASSERT_EQ(contentsRF[i], v[i]);
    }
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
    // ASSIGN CIN BACK TO STDIN
    cin.rdbuf(backup_in);
}

TEST(passwordProxy,readInvalidPassword) { // when an invalid password is given for the read function, then we would expect the contents vector returned to be empty, however the original file, that does not require a password to read, should be updated from the valid write call
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    vector<char> v = { 'h', 'i' };
    // REDIRECT COUT STREAM
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // REDIRECT CIN STREAM
    streambuf* backup_in;
    backup_in = cin.rdbuf();
    stringstream ss_in;
    cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    string wrongPassword = "a5lsdIK3";
    ss_in << password + '\n' + wrongPassword;
    // EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
    ASSERT_EQ(0, pp->write(v));
    ASSERT_EQ(static_cast<unsigned int>(v.size()), pp->getSize());
    ASSERT_EQ(static_cast<unsigned int>(v.size()), realfile->getSize());
    // EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
    std::vector<char> contentsPP = pp->read();
    ASSERT_EQ(static_cast<size_t>(0), contentsPP.size());
    std::vector<char> contentsRF = realfile->read();
    ASSERT_EQ(static_cast<size_t>(v.size()), contentsRF.size());
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
    // ASSIGN CIN BACK TO STDIN
    cin.rdbuf(backup_in);
}

TEST(passwordProxy,acceptValidPassword) { // we would expect "hi" -- the contents of the file -- to be printed when a valid password is given for accept
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    vector<char> v = { 'h', 'i' };
    // REDIRECT COUT STREAM
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // REDIRECT CIN STREAM
    streambuf* backup_in;
    backup_in = cin.rdbuf();
    stringstream ss_in;
    cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    ss_in << password + '\n' + password;
    // EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
    ASSERT_EQ(0, pp->write(v));
    ASSERT_EQ(static_cast<unsigned int>(v.size()), pp->getSize());
    ASSERT_EQ(static_cast<unsigned int>(v.size()), realfile->getSize());
    // EXPECTATIONS FOR SECOND FUNCTION -- VALID PASSWORD
    BasicDisplayVisitor* bdv = new BasicDisplayVisitor;
    pp->accept(bdv);
    string wordShouldBe = "hi";
    string word;
    vector<string> printedWords;
    while (ss_out >> word) {
        printedWords.push_back(word);
    }
    std::vector<string>::iterator it1;
    it1 = std::find(printedWords.begin(), printedWords.end(), wordShouldBe);
    bool isEqual = it1 == printedWords.end();
    ASSERT_FALSE(isEqual);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
    // ASSIGN CIN BACK TO STDIN
    cin.rdbuf(backup_in);
}

TEST(passwordProxy,acceptInvalidPassword) { // we do not expect "hi" (the contents of the file) to be printed when an invalid password is given for accept
    // CREATE FILE AND FILE PROXY
    std::string fileName = "file1.txt";
    AbstractFile* realfile = new TextFile(fileName);
    string password = "r4A3dg";
    PasswordProxy* pp = new PasswordProxy(realfile, password);
    vector<char> v = { 'h', 'i' };
    // REDIRECT COUT STREAM
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // REDIRECT CIN STREAM
    streambuf* backup_in;
    backup_in = cin.rdbuf();
    stringstream ss_in;
    cin.rdbuf(ss_in.rdbuf());
    // SET UP PASSWORD STREAM
    string wrongPassword = "a5lsdIK3";
    ss_in << password + '\n' + wrongPassword;
    // EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
    ASSERT_EQ(0, pp->write(v));
    ASSERT_EQ(static_cast<unsigned int>(v.size()), pp->getSize());
    ASSERT_EQ(static_cast<unsigned int>(v.size()), realfile->getSize());
    // EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
    BasicDisplayVisitor* bdv = new BasicDisplayVisitor;
    pp->accept(bdv);
    string wordShouldBe = "hi";
    string word;
    vector<string> printedWords;
    while (ss_out >> word) {
        printedWords.push_back(word);
    }
    std::vector<string>::iterator it1;
    it1 = std::find(printedWords.begin(), printedWords.end(), wordShouldBe);
    bool isEqual = it1 == printedWords.end();
    ASSERT_TRUE(isEqual);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
    // ASSIGN CIN BACK TO STDIN
    cin.rdbuf(backup_in);
}

TEST(commandPrompt,runQuit) { // ensures that the run method ends when quit by the user (entering q), we would expect a non-zero return value
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    CommandPrompt* cp = new CommandPrompt;
    cp->setFileSystem(sfs);
    cp->setFileFactory(sff);
    // REDIRECT COUT STREAM
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // REDIRECT CIN STREAM
    streambuf* backup_in;
    backup_in = cin.rdbuf();
    stringstream ss_in;
    cin.rdbuf(ss_in.rdbuf());
    // MIMC USER INPUT -- QUITTING COMMAND -- 'Q'
    string input = "q";
    ss_in << input;
    // CAPUTRE RETURN VALUE -- Q SHOULD END THE RUN LOOP
    int response = cp->run();
    ASSERT_NE(0, response);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
    // ASSIGN CIN BACK TO STDIN
    cin.rdbuf(backup_in);
}

TEST(commandPrompt,runHelp) { // we would expect help to list all of the commands that have been added, in this case only the test command should be printed
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    CommandPrompt* cp = new CommandPrompt;
    cp->setFileSystem(sfs);
    cp->setFileFactory(sff);
    // ADD COMMAND -- COMMAND TEST
    CommandTest* ct = new CommandTest(sfs);
    string commandname = "test";
    ASSERT_EQ(0, cp->addCommand(commandname, ct));
    // REDIRECT COUT STREAM
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // REDIRECT CIN STREAM
    streambuf* backup_in;
    backup_in = cin.rdbuf();
    stringstream ss_in;
    cin.rdbuf(ss_in.rdbuf());
    // MIMIC USER INPUT -- HELP & QUIT -- USE QUIT TO END RUN
    string input = "help\nq";
    ss_in << input;
    int response = cp->run();
    ASSERT_NE(0, response);
    // CAPTURE COUT DATA
    string word;
    std::vector<string> printedWords;
    while (ss_out >> word) {
        printedWords.push_back(word);
    }
    // EXPECTATION -- PROGRAM SHOULD PRINT ALL COMMANDS
    std::vector<string>::iterator it1;
    it1 = std::find(printedWords.begin(), printedWords.end(), commandname);
    bool notEqual1 = it1 == printedWords.end();
    ASSERT_FALSE(notEqual1);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
    // ASSIGN CIN BACK TO STDIN
    cin.rdbuf(backup_in);
}

TEST(commandTest,commandDisplayInfo) { // uses the CommandTest object to check that help + command name will successfully call the displayInfo() method for the correct command type
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    CommandPrompt* cp = new CommandPrompt;
    cp->setFileSystem(sfs);
    cp->setFileFactory(sff);
    // ADD COMMAND -- COMMAND TEST
    CommandTest* ct = new CommandTest(sfs);
    string commandname = "test";
    ASSERT_EQ(0, cp->addCommand(commandname, ct));
    // REDIRECT COUT STREAM
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // REDIRECT CIN STREAM
    streambuf* backup_in;
    backup_in = cin.rdbuf();
    stringstream ss_in;
    cin.rdbuf(ss_in.rdbuf());
    // MIMIC USER INPUT -- SPECIFIC HELP COMMAND
    string input = "help test\nq\n";
    ss_in << input;
    int response = cp->run();
    ASSERT_NE(0, response);
    string word;
    std::vector<string> printedWords;
    while (ss_out >> word) {
        printedWords.push_back(word);
    }
    /// EXPECTATION -- DISPLAY INFO OF OUR COMMAND TEST SHOULD BE PRINTED TO COUT
    std::vector<string>::iterator it1;
    string expectedString = "aRandomStringz"; // MATCHES GIVEN COMMAND TEST FILE
    it1 = std::find(printedWords.begin(), printedWords.end(), expectedString);
    bool notEqual1 = it1 == printedWords.end();
    ASSERT_FALSE(notEqual1);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
    // ASSIGN CIN BACK TO STDIN
    cin.rdbuf(backup_in);
}

TEST(commandTest,commandExecuteNoInfo) { //  uses the CommandTest object to check passing variables to execute - expects no inputs to be passed as the parameter in this case
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    CommandPrompt* cp = new CommandPrompt;
    cp->setFileSystem(sfs);
    cp->setFileFactory(sff);
    // ADD COMMAND
    CommandTest* ct = new CommandTest(sfs);
    string commandname = "test";
    ASSERT_EQ(0, cp->addCommand(commandname, ct));
    // REDIRECT COUT STREAM
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // REDIRECT CIN STREAM
    streambuf* backup_in;
    backup_in = cin.rdbuf();
    stringstream ss_in;
    cin.rdbuf(ss_in.rdbuf());
    // MIMIC USER INPUT -- COMMAND TEST EXECUTE
    string input = "test\nq\n";
    ss_in << input;
    // CAPTURE RUN OUTPUT
    int response = cp->run();
    ASSERT_NE(0, response);
    string word;
    std::vector<string> printedWords;
    while (ss_out >> word) {
        printedWords.push_back(word);
    }
    // EXPECTATION -- NOTHING SHOULD BE PASSED TO THE FUNCTION
    std::vector<string>::iterator it1;
    string expectedOutput = "command-test-no-info";
    it1 = std::find(printedWords.begin(), printedWords.end(), expectedOutput);
    bool notEqual1 = it1 == printedWords.end();
    ASSERT_FALSE(notEqual1);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
    // ASSIGN CIN BACK TO STDIN
    cin.rdbuf(backup_in);
}

TEST(touchCommand,execute) { // confirms that execute, when passed a valid filename, will create and add a file in the filesystem
    // REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
    streambuf* backup_out;
    backup_out = cout.rdbuf();
    stringstream ss_out;
    cout.rdbuf(ss_out.rdbuf());
    // SET UP FILE SYSTEM
    AbstractFileSystem* sfs = new SimpleFileSystem();
    AbstractFileFactory* sff = new SimpleFileFactory();
    // CREATE COMMAND
    TouchCommand* tc = new TouchCommand(sfs, sff);
    // CALL EXECUTE ON TOUCH COMMAND
    string filename = "file.txt";
    ASSERT_EQ(0, tc->execute(filename));
    // EXPECTATION -- FILE EXISTS IN THE FILE SYSTEM
    AbstractFile* file = sfs->openFile(filename);
    bool isNull = file == nullptr;
    ASSERT_FALSE(isNull);
    ASSERT_EQ(file->getName(), filename);
    // ASSIGN COUT BACK TO STDOUT
    cout.rdbuf(backup_out);
}
