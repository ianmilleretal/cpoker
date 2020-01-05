#include "reader.hpp"
#include <string>
#include <fstream>


void Reader::open(const std::string &path)
{
    if (this->_ifile.is_open())
        this->_ifile.close();
    this->_ifile.open(path);
    this->_eof = false;
}

void Reader::close()
{
    this->_ifile.close();
    this->_eof = true;
}
