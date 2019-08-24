#ifndef READER_PAYOFFS
#define READER_PAYOFFS


#include "../card_cons.hpp"
#include <string>
#include <fstream>


class Reader
{
protected:
    std::ifstream _ifile;
    bool _eof;

public:
    Reader() : _ifile(), _eof(true) {}
    Reader(const std::string &path) : _ifile(path), _eof(false) {}

    void open(const std::string &path);
    void close();

    bool eof()
        {return this->_eof;}
    bool peek_eof()
        {return this->_ifile.peek() == EOF;}

        template<typename T>
    void bin(T* store);
        template<typename T>
    void one(T &yield);
};


template<typename T>
void Reader::one(T &yield)
{
    this->_ifile.read((char*) &yield, sizeof(yield));
    if (this->_ifile.peek() == EOF) {
        this->_ifile.close();
        this->_eof = true;
    }
}


#include <iostream>
#include <bitset>
template<typename T>
void Reader::bin(T* store)
{
    T buffer;
    int i=0;
    while(this->_ifile.peek() != EOF) {
        this->_ifile.read((char*) &buffer, sizeof(buffer));
        store[i] = buffer;
        i++;
    }
    this->close();
}


#endif
