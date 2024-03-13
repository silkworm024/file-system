# Studio 21

1. This is so that is destroys the base class that the subclass inherits from!
2. By just "injecting" the prompt class with the factory, system management, and commands, this means that the prompt can
be used for almost any system of commands. The command prompt works by literally manually creating each command name to
be a key in a map, which would work for almost any command type as long as it followed the command concrete set. If I wanted
to make a command set that related to say, video files, i could then make commands like "mute video" or "pause display" that
could then dynamically reach to the different command structures. Might be a pain to make those classes, but the command prompt
is a lot easier to change.
3. First I tested the help function as well as the quit function. The help function works well, though if there is a space before the
help function it does not list the commands expected, because it expects the user to type a second command. Then I tested the touch command
It seemed to run as expected! I built files, built a file without a .___ (which failed as expected) , built files with the same name (failed as expected)
So seems good.
Tests run:
   (Testing for basic function)
A)   $ help
   Command doesn't exist

Process finished with exit code 3

B) Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
   .
   $help
   touch
   Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
   .
   $help touch
   Touch creates a file, touch can be invoked with the command 'touch <filename>' or 'touch <filename> -p
   Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
   .
   $touch testfile
   An error occurs

Process finished with exit code 4 (fail-to-create-file)

(testing for same name as other)
C) Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$touch testfile.txt
Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that comm
and.
$touch testfile.txt
An error occurs

Process finished with exit code 1 (filename already exist in system)
(testing q)
D) Enter a command, 'q' to quit, 'help' for a list of commands, or 'help <command>' for more information about that command
.
$q

Process finished with exit code 2 (quit)

