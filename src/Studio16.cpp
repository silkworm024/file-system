#include "mockos/TextFile.h"

int main() {
    std::string filename = "guy";

    TextFile guy = TextFile(filename);

    std::vector<char> text = {'H', 'E', 'L', 'L', 'O'};

    guy.write(text);
    guy.read();
}

