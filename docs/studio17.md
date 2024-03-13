# Studio 17
1. The helper function should likely be private, since the user doesn't need to worry about decoding things
that we only see on our side of the interface (like the coordinate)
2. We tested the correct input. It prints out and return 0. 
2. Then we changed the size of input, so it returns the failure state for size mismatch. 
3. Also, we made the inout wrong.
4. Programming a client to an interface rather than something concrete allows for the flexibility to reuse code
and save computer memory space. A file creator that might have hard coding would need to have a special signifier
dedicated to each kind of file, meanwhile a object that inherits an interface can have functions written for it
that don't need to know what kind of object it is for it to work. This cuts down on the number of cpp files as well!
5. We would likely need to add code to the addFile function, as it would have to check for a new kind of .__ filetype
We also would need to add code to createFile, as this is where the file type is made!

