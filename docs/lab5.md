# Lab 5

Work Division:
Xinyuan:
- Studios 17, 19, 21
- Modified TouchCommand
- Created and Implemented CatCommand
- Created and Implemented MacroCommand/Rename
- Added additional MacroCommand
- Updating Main and testing
- Extra Credit: File Permission (Proxy)

Kaitlyn:
- Studios 16, 18, 20
- Create and implement LSCommand
- Create and implement RemoveCommand
- Create and implement DisplayCommand
- Create and implement CopyCommand
- Updating Main and testing

Errors Encountered:
- when using cpy command, can make a copy with no name. Probably should fix that.
  - Fixed by adding a new if-statement to check for an empty "fileCopy" string
- chmod does not allow read-only to be disabled.
  - After doing some wiggling about, I'm not sure we -can- undo a readonly permission, as that requires revertng the proxy
  - This is not supported by the AbstractFile interface. Plus, making an object read-only doesn't mean it's permanently lost
  - I would argue when making a "clone" of a read only file, it should be editable. But, for now I'll leave it as is.
  - From Xinyuan: I fixed the issue by adding a getter to the password proxy. It may not be the best solution but it works.
- Cat command ran into several issues when I first ran the tests as I added to many '\n' to the file.
- In general, errors occur when files are not properly closed after being called.

All possible return values:
The current main function only has one return value: quit. It happens when the user types in 'q'.
The execution of commands have many possible return values. All of them can be found in enum.h.

Additional comments:
- For password protected files, when the user do cat <filename> -a, there will be password prompt as read() is called. However, at this stage, if the user enters a wrong password, the function will proceed. Password will be prompt again in the end and determine whether or not the input will be written.
- For the additional macro command, we did editDisplay, which is a combination of cat and ds. We added a info parameter to the concrete strategy classes to store info specific to each macro command.

Memory management:
In the main function, the file system, factory and all the command objects are dynamically allocated so that their pointers can be used.
New files are all dynamically allocated so that they can be properly maintained throughout the program. They are deallocated when being removed from the system.
Both password and permission proxy call delete on the protected file, so when they are removed from the system, the memory actual file is released as well.
Visitors are declared/deallocated locally.
At the end of main function, all dynamically allocated objects are deallocated by calling delete on the pointer.
When the system is deleted, in the destructor, delete is called on each file in the map. 

Extra Credit:
We talked to Professor Shidal and decided to implement read permission on file using the proxy pattern. We created a class called PermissionProxy and the corresponding PermissionCommand.
The logic is similar to password proxy. Functions like write() and append() are not available for read-only files.
To check if the file is a permission proxy or not, we used dynamic casting, which has been approved.
The command for changing permission is chmod -r/chmod -w.

Tests:
- Under ideal circumstances, all commands function properly.
- Ran through each command, edited text files.
- Now to test image files!
- Image files are excellent.
- Attempted creating, editing, copying, and reading password proxies, all functional as expected.
- Attempted to display and open files that don't exist, proper errors occur

Results:
C:\local_repositories\oop-work-studio16_thornton_yu\cmake-build-debug\src\lab5.exe
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$help
cat
catds
chmod
cp
ds
ls
rm
rn
touch
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$help cat
Cat concatenates files, cat can be invoked with the command 'cat <filename>' or 'cat <filename> -a
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$help catds
EditDisplay command allows you to edit a file and display it immediately. It can be invoked by 'catds'. Additional op
tions: 'catds -a -d' to append and display without format, 'catds -d' to display without format
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$help chmod
Permission command change the permission of a file to read-only or undo the change. To add read-only permission, do '
chmod -r <fileName>'. To remove the permission, do 'chmod -w <fileName>'
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$help cp
Copy creates a copy of a file, copy can be invoked with the command 'cp <file_to_copy> <new_name_with_no_extension>'
Example: 'cp samplefile.txt samplecopy'
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$help ds
Display displays a file, display can be invoked with the command 'ds <filename>' or 'ds <filename> -d for non-formatt
ed
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$help ls
List (ls) lists all file names in the system to the user terminal. List can be invoked by typing 'ls' to the console
or 'ls -m' to have a mono-list.
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$help rm
Remove deletes a file, remove can be invoked with the command 'rm <filename>'
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$help rn

Rename command renames a file. Rename command can be invoked by 'rn <existing_file> <new_name_with_no_extension>'
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$  Command doesn't exist
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$help rn
Rename command renames a file. Rename command can be invoked by 'rn <existing_file> <new_name_with_no_extension>'
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$help touch
Touch creates a file, touch can be invoked with the command 'touch <filename>' or 'touch <filename> -p
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ls

Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$touch textfile.txt
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that comm
and.
$touch textfile
Fail to create file
An error occurs
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$touch textfile1.txt
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that comm
and.
$cat textfile.txt hello there
Enter the data you would like to write to the file
hello there
:wq
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ds textfile.txt
hello there
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ds -m textfile.txt
Fail to open file
An error occurs
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ds-m textfile.txt
Command doesn't exist
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ds textfile.txt -d
hello there
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ls -m
textfile.txt text 11
textfile1.txt text 0
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$cat textfile.txt -a
hello there
Enter the data you would like to append to the file
bud
:wq
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ds textfile.txt
hello there bud
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$touch texxxxxxxxxxxxxxxxxxxxxxxxxtfile.txt
File name is too long
An error occurs
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$catds textfile1.txt
Enter the data you would like to write to the file
Does this work?
:wq
Does this work?
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$catds textfile1.txt -a -d
Does this work?
Enter the data you would like to append to the file
How about this?
:wq
Does this work?How about this?
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$cp textfile1.txt
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that comm
and.
$ls
.txt        textfile.txt
textfile1.txt
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$rm .txt
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that comm
and.
$ls
textfile.txt       textfile1.txt

Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$chmod textfile.txt
Wrong command format
An error occurs
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$chmod -r textfile.txt
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that comm
and.
$cat textfile.txt
Enter the data you would like to write to the file
whoops
:wq
This is a read_only_file
An error occurs
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ds textfile.txt
hello there bud
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$rn textfile.txt newname
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that comm
and.
$ls
newname.txt       textfile1.txt

Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$chmod -w newname.txt
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that comm
and.
$cat newname.txt
Enter the data you would like to write to the file
Alright, attempt two
:wq
This is a read_only_file
An error occurs
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$q

Process finished with exit code 2

// Attempt to write to an image file
C:\local_repositories\oop-work-studio16_thornton_yu\cmake-build-debug\src\lab5.exe
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$touch file.img
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that comm
and.
$cat file.img
Enter the data you would like to write to the file
X X X X X3
:wq
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ds file.img
X X
X
X X
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$cat file.img -a
X X X X X
Enter the data you would like to append to the file
X X X X4
:wq
Append is not supported for image file
An error occurs
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$q

Process finished with exit code 2
// Now attempting to make a password proxy
C:\local_repositories\oop-work-studio16_thornton_yu\cmake-build-debug\src\lab5.exe
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$touch filetext.txt -p
What is the password?
sesame
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$cat filetext.txt
Enter the data you would like to write to the file
Greetings
:wq
Please enter the file's password.
sesame
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ds filetext.txt
Please enter the file's password.
sesame
Greetings
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$cp filetext.txt passwordfile
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that comm
and.
$ls
filetext.txt    passwordfile.txt

Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$cat passwordfile.txt -a
Please enter the file's password.
sesame
Greetings
Enter the data you would like to append to the file
from the code
:wq
Please enter the file's password.
sesame
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ds passwordfile.txt
Please enter the file's password.
sesame
Greetings from the code
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ds filetext.txt
Please enter the file's password.
sesame
Greetings
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ls
filetext.txt    passwordfile.txt

Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ls -m
Please enter the file's password.
sesame
filetext.txt text 9
Please enter the file's password.
sesame
passwordfile.txt text 23
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$q

Process finished with exit code 2

// Testing DS in detail
C:\local_repositories\oop-work-studio16_thornton_yu\cmake-build-debug\src\lab5.exe
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$touch filetext.txt
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that comm
and.
$ds fileshape.txt
Fail to open file
An error occurs
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ds fileshape
Fail to open file
An error occurs
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$q

Process finished with exit code 2
// fixed Copy
C:\local_repositories\oop-work-studio16_thornton_yu\cmake-build-debug\src\lab5.exe
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$touch text.txt
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that comm
and.
$cp text.txt
Copy failed. Copy being deleted.
An error occurs
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$ls
text.txt
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$
//
