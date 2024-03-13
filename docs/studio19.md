# Studio 19
1. Given that the only change is that read() returns a vector of chars, we tested editing and writing to the file
by creating a pair of vectors and writing to them. We then called read() and transferred that information to a new array and 
printed it out manually. Then, we edited the file contents and manually printed the file contents again. Both of these were successful!
2. To describe the interaction between a file and visitor, first a file must "accept" the visitor through a public funtion.
This then calls the visitor's "visit" function with a pointer to the file being visited so that the visitor object can access
the object's private data directly. It then prints said data in whatever manner the file type should be printed, as it can
dynamically determine which type of AbstractFile the read file is at runtime.
3. The visitor utilizes delegation by allowing the specific display function to be handled by a different object. This removes
the display responsibility from the object's functionality, allowing the code to be more focused and less cluttered for the
coder's end.
4. We would have to change the accept function of each file type class, and would have to change the factory class as well.
A negative side of the visitor program is that one has to manually code each type of file display, and if one has a huge number of
file types, this in itself can become bloated and cluttered. This makes the code way less readable.