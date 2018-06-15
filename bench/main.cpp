#include <cstdio>
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>
#include <ctime>
#include <limits.h>
#include <cstring>

#include "bench.hpp"

std::ifstream inFile("in.txt");
std::ofstream outFile("out.txt");
std::ifstream expectedFile("expected.txt");

Bench bench(inFile, outFile);

int main()
{
    bench.start();

    int T;
    std::cin >> T;
    std::cout << T;

    // ... code here
    
    bench.stop();
    std::cout << (bench.isValid(expectedFile) ? "ok" : "fail") << " " << bench.getDuration() << "s" << std::endl;      
    return 0;
}