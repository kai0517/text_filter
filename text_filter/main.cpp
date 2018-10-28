#include "text_filter.h"
#include <fstream>
#include <Windows.h>
#include <iostream>

std::string read_text_file(char const* fname);

int main(void) {
    SetConsoleOutputCP(CP_UTF8);
    text_filter filter(read_text_file("test.txt"), read_text_file("filter.txt"));
    system("pause");
}

std::string read_text_file(char const* fname) {
    std::ifstream fin(fname);
    fin.seekg(0, fin.end);
    size_t length = static_cast<size_t>(fin.tellg());
    fin.seekg(0, fin.beg);
    char* buffer = new char[length];
    fin.read(buffer, length);
    std::string ret(buffer, length);
    delete[] buffer;
    return ret;
}