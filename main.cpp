#include <iostream>
#include <fstream>
#include "hello.hpp"

#define CSV_FILENAME "BBox_List_2017.csv"

int main(int argc, char **argv)
{
    hello::say_hello();
    std::fstream ifs;
    ifs.open(CSV_FILENAME, std::fstream::in);

    char c = ifs.get();

    while (ifs.good())
    {
        std::cout << c;
        c = ifs.get();
    }

    ifs.close();
    return 0;
} // end of main function code block
