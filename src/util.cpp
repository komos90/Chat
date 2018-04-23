#include <iostream>
#include "util.h"

void printStreamBufLine(ba::streambuf& sb) {
    std::istream is(&sb);
    std::string s;
    std::getline(is, s);
    std::cout << s << std::endl;
}