#include <cstdio>
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>
#include <ctime>
#include <cstring>
#include <unordered_map>

#include "bench.hpp"

using namespace std;

int main()
{  
    try
    {
        Bench bench("in.txt", "out.txt", "expected.txt");
        bench.start();        
        { 
            //************* CODE HERE *************//
            vector<string> crossword(10);

            for (int i = 0; i < 10; i++) {
                string crossword_item;
                bench >> crossword_item;
                // getline(inFile, crossword_item); // cin

                crossword[i] = crossword_item;
            }

            string words;
            bench >> words;

            vector<string> result = crosswordPuzzle(crossword, words);

            for (int i = 0; i < result.size(); i++) {
                bench << result[i];

                if (i != result.size() - 1) {
                    bench << "\n";
                }
            }
            //************* CODE HERE *************//
        }
        bench.stop();
        bench.compareResults();
    }
    catch(const std::exception& e_)
    {
        std::cerr << e_.what() << '\n';
    }
    return 0;
}