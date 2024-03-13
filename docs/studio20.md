# Studio 20

4. Code run for tests, and result!
Code:
   AbstractFile * fp = new TextFile("Hello.txt");
   auto * pp = new PasswordProxy(fp,"sesame");

   // write test
   std::vector<char> input = {'h','i',' ','t','h','e','r','e'};
   int resultw = pp->write(input);
   std::cout << resultw << std::endl;

   //read test
   std::vector<char> read = pp->read();
   for (unsigned int i = 0;i < read.size();i++){
   std::cout << read[i];
   }
   std::cout << std::endl;

   // append test
   std::vector<char> input2 = {' ','b','u','d','d','y'};
   int resulta = pp->append(input2);
   std::cout << resulta << std::endl;
   // read again to check
   std::vector<char> newread = pp->read();
   for (unsigned int i = 0;i < newread.size();i++){
   std::cout << newread[i];
   }
   std::cout << std::endl;

   //display test
   BasicDisplayVisitor * bv = new BasicDisplayVisitor;
   pp->accept(bv);
Result(all correct passwords):
   Please enter the file's password.
   sesame
   0
   Please enter the file's password.
   sesame
   hi there
   Please enter the file's password.
   sesame
   0
   Please enter the file's password.
   sesame
   hi there buddy
   Please enter the file's password.
   sesame
   hi there buddy
Result(incorrect passwords):
   C:\local_repositories\oop-work-studio16_thornton_yu\cmake-build-debug\src\studio20.exe
   Please enter the file's password.
   hi
   Error. Password does not match.5
   Please enter the file's password.
   hi
   Error. Password does not match.
   Please enter the file's password.
   hi
   Error. Password does not match.6
   Please enter the file's password.
   hi
   Error. Password does not match.
   Please enter the file's password.
   hi
   Error. Password does not match.
   Process finished with exit code 0
Results (correct on write and append, false on read())
   Please enter the file's password.
   sesame
   0
   Please enter the file's password.
   hi
   Error. Password does not match.
   Please enter the file's password.
   sesame
   0
   Please enter the file's password.
   hi
   Error. Password does not match.
   Please enter the file's password.
   sesame
   hi there buddy
Results (false on write and append, true on read and display)
   Please enter the file's password.
   hi
   Error. Password does not match.5
   Please enter the file's password.
   sesame

Please enter the file's password.
hi
Error. Password does not match.6
Please enter the file's password.
sesame

Please enter the file's password.
sesame


Process finished with exit code 0