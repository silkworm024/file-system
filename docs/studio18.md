# Studio 18
1. It would be difficult because we would have to redefine everything, but easier than if we were working from scratch
since we still have inheritance from AbstractFileSystem. In order to make a new file type we would have to change the
createFile function, which is just getting bigger and less efficient. 
2. By using the abstract file system and factory, it becomes easier to create an interface for more complicated systems. It also
makes for cleaner code since each class does a single thing. However, this does take up more memory space, I think.
A new factory class should be made when the file type gets more complicated and needs specific generation or multiple
file types within the same file. (ex, a gif needs multiple image files). The same factory can be used for both systems
if their implementation is the same. It could be done for two systems if they manage different file types, but it would 
likely be bad practice since it would require a lot of workarounds. Plus, they would just make the same file types. It's
better to have two implementations so that the code can dynamically determine which factory to use at run time.
3. I made two vector<char> and created the systems and factories respectively. Then, I wrote the vectors to the system
with the following code, and the following output:
Code:
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
Output:
Hello There
X X
 X
X X
4. It now only depends on abstract file interface, since there are no simple files actually used in the code.
5. 