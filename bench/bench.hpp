#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdio>

class Bench
{
public:
    explicit Bench(std::ifstream& in, std::ofstream& out)
        : _in(in), _out(out), _cinbuf(std::cin.rdbuf()), _coutbuf(std::cout.rdbuf())
    {}

    void start()
    { 
        if (_in.good())
            std::cin.rdbuf(_in.rdbuf());
        else
            std::cout << "input file not found, using default std::cin stream buffer" << std::endl;

        std::cout.rdbuf(_out.rdbuf());

        _startClock = std::clock();
    }

    void stop()
    { 
        if (_in.good())
            std::cin.rdbuf(_cinbuf); 

        std::cout.rdbuf(_coutbuf);

        _duration = (std::clock() - _startClock) / (double) CLOCKS_PER_SEC;
    }

    // return the test duration in seconds
    double getDuration() const { return _duration; }

    bool isValid(std::ifstream& expectedFile) const
    {
        if (!_out.good())
            return false;

        if (!expectedFile.good())
        {
            std::cout << "expected file not found" << std::endl;
            return false;
        }
        
        std::ifstream outFile("out.txt");

        bool valid = true;
        outFile.seekg(0, std::ios::beg);
        std::string output, expected;
        while(std::getline(outFile, output) && std::getline(expectedFile, expected))
        {
            if(output.compare(expected))
            {
                valid = false;
                break;
            }
        }

        if (outFile.eof() && !expectedFile.eof())
        {
            while(std::getline(expectedFile, expected) && expected.size());
            valid = true;
        }
        else if (!outFile.eof() && expectedFile.eof())
        {
            while(std::getline(outFile, output) && output.size());
            valid = true;
        }

        return valid;
    }

private:
    double          _duration;
    std::clock_t    _startClock;

    std::ifstream&  _in;
    std::ofstream&  _out;

    std::streambuf* const _cinbuf;
    std::streambuf* const _coutbuf;
};