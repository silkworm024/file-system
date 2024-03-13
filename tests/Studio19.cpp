#include "gtest/gtest.h"

#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"
#include "mockos/SimpleFileSystem.h"
#include "mockos/SimpleFileFactory.h"
#include "mockos/BasicDisplayVisitor.h"
#include "mockos/MetadataDisplayVisitor.h"

#include <iostream>
#include <sstream>
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
    //cout << (t == nullptr) << endl;
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
