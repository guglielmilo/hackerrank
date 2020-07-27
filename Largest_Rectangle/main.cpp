#include <cstdio>
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>
#include <ctime>
#include <cstring>
#include <unordered_map>
#include <set>
#include <tuple>
#include <memory>

#include "bench.hpp"

using namespace std;

vector<string> split_string(string input_string)
{
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

void print(stack<std::tuple<unsigned, unsigned>> s)
{
    while(!s.empty())
    {
        auto x = s.top();
        s.pop();
        cout << std::get<0>(x) << "|" << std::get<1>(x) << " ";
    }
 }

// Complete the largestRectangle function below.
long largestRectangle(vector<int> h) {

    long rectMax {0};
    std::stack<std::tuple<unsigned, unsigned>> hlStack;

    for (unsigned i=0; i < h.size(); ++i)
    {
        auto height {h[i]};
        auto orig {i};
        if (!hlStack.empty())
        {
            auto& stackTop {hlStack.top()};
            auto stackTopHeight {std::get<0>(stackTop)};
            
            while (height < stackTopHeight)
            {
                const auto stackTopOrig {std::get<1>(stackTop)};
                const auto stackTopLength {i - stackTopOrig};
                const long rect {stackTopHeight * stackTopLength};
                if (rect > rectMax)
                {
                    rectMax = rect;
                }
                hlStack.pop();
                orig = stackTopOrig;
                if (hlStack.empty())
                {
                    break;
                }
                stackTop = hlStack.top();
                stackTopHeight = std::get<0>(stackTop);
            }
        }

        hlStack.push(std::make_tuple(height, orig));
    }

    while (!hlStack.empty())
    {
        auto& stackTop {hlStack.top()};
        const unsigned stackTopHeight {std::get<0>(stackTop)};
        const unsigned stackTopOrig {std::get<1>(stackTop)};
        const unsigned stackTopLength {static_cast<unsigned>(h.size()) - stackTopOrig};
        const long rect {stackTopHeight * stackTopLength};
        if (rect > rectMax)
        {
            rectMax = rect;
        }
        hlStack.pop();
    }

    return rectMax;
}

int main()
{  
    try
    {
        Bench bench("in.txt", "out.txt", "expected.txt");
        bench.start();        
        { 
            //************* CODE HERE *************//
            int n;
            bench >> n;
            
            vector<int> h;
            h.reserve(n);
            while (n-- > 0)
            {
                int ht;
                bench >> ht;
                h.emplace_back(ht);
            }

            long result = largestRectangle(h);

            bench << result;
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