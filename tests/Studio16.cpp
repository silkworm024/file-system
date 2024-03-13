#include "gtest/gtest.h"

#include "mockos/TextFile.h"

using namespace std;

TEST(textfile,constructor){ // checks that the file is initialized with proper name and size, expects size to be 0 and the name to match the input to the constructor
    string fileName = "FileName.txt";
    unsigned int fileSize = 0;
    TextFile t(fileName);
    ASSERT_EQ(fileName, t.getName());
    ASSERT_EQ(fileSize, t.getSize());
}

TEST(textfile,write){ // tests write, expects that the function returns success and that the size of the file is updated correctly
    string fileName = "FileName.txt";
    TextFile t(fileName);
    vector<char> v = { 'h', 'i' };
    ASSERT_EQ(0, t.write(v));
    ASSERT_EQ(static_cast<unsigned int>(v.size()), t.getSize());
}

TEST(textfile,append){ // tests append, expects the write and append functions to return 0 and the size of the file to update correctly
    string fileName = "FileName.txt";
    TextFile t(fileName);
    vector<char> v = { 'h', 'i' };
    ASSERT_EQ(0, t.write(v));
    unsigned int fileSize = t.getSize();
    ASSERT_EQ(0, t.append(v));
    ASSERT_EQ(static_cast<unsigned int>(fileSize + v.size()), t.getSize());

}

TEST(textfile,read){ // tests that the read function outputs the contents of the file
    string fileName = "FileName.txt";
    TextFile t(fileName);
    vector<char> v = { 'h', 'i' };
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

TEST(textfile,readWithAppend){ // tests that read also works with appending to a file
    string fileName = "FileName.txt";
    TextFile t(fileName);
    vector<char> v = { 'h', 'i' };
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