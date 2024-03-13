#include "mockos/enums.h"
#include "mockos/TextFile.h"
#include "mockos/BasicDisplayVisitor.h"
#include "mockos/PasswordProxy.h"

int main(){

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

    return 0;
}