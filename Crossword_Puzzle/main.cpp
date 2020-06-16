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

std::vector<std::string> getFitWords(const std::vector<std::string>& wv,
                                     const size_t startPos, const size_t endPos)
{
    std::vector<std::string> wf;
    const auto size {endPos - startPos + 1};
    for (const auto& w : wv)
    {
        if (w.size() == size)
        {
            wf.push_back(w);
        }
    }
    return wf;
}

bool removeWord(const std::string& w, std::vector<std::string>& wv)
{
    wv.erase(std::remove(wv.begin(), wv.end(), w), wv.end());
    return wv.empty();
}

bool putWord(std::vector<std::string>& cw, const std::string& w, 
             const size_t startPos, const size_t endPos, const bool hrtl, const size_t l, const size_t h)
{
    if (hrtl)
    {
        bool result {true};
        for (size_t i=startPos, iw=0; i<=endPos; ++i, ++iw)
        {
            if (cw[l][i] != '-' && cw[l][i] != w[iw])
            {
                result = false;
                break;
            }
        }
        if (result)
        {
            for (size_t i=startPos, iw=0; i<=endPos; ++i, ++iw)
            {
                cw[l][i] = w[iw];
            }
            return true;
        }
    }
    else
    {
        bool result {true};
        for (size_t i=startPos, iw=0; i<=endPos; ++i, ++iw)
        {
            if (cw[i][h] != '-' && cw[i][h] != w[iw])
            {
                result = false;
                break;
            }
        }
        if (result)
        {
            for (size_t i=startPos, iw=0; i<=endPos; ++i, ++iw)
            {
                cw[i][h] = w[iw];
            }
            return true;
        }
    }
    return false;
}

bool isFree(const char c)
{
    return c == '-' || (std::isupper(c) && c != 'X'); // X can be used on some testcase
}

auto getStartEndPosH(const std::vector<std::string>& cw, const size_t l, const size_t h)
{
    const size_t H {cw.back().size()};
    const auto startPos {h};
    auto endPos {h};
    auto h_loc {h + 1};
    bool result {false};
    while(h_loc <= H)
    {
        if(h_loc == H || !isFree(cw[l][h_loc]))
        {
            endPos = h_loc - 1;
            break;
        }
        if (cw[l][h_loc] == '-')
        {
            result = true;
        }
        ++h_loc;
    }
    if (!result)
    {
        endPos = startPos;
    }
    return std::make_tuple(startPos, endPos);
}

auto getStartEndPosL(const std::vector<std::string>& cw, const size_t l, const size_t h)
{
    const size_t L {cw.size()};
    const auto startPos {l};
    auto endPos {l};
    auto l_loc {l + 1};
    bool result {false};
    while(l_loc <= L)
    {
        if (l_loc == L || !isFree(cw[l_loc][h]))
        {
            endPos = l_loc - 1;
            break;
        }
        if (cw[l_loc][h] == '-')
        {
            result = true;
        }
        ++l_loc;
    }
    if (!result)
    {
        endPos = startPos;
    }
    return std::make_tuple(startPos, endPos);
}

std::tuple<bool, std::vector<std::string>> find(std::vector<std::string> cw,
                                                std::vector<std::string> wv)
{
    size_t L {cw.back().size()};
    size_t H {cw.size()};

    bool hrtl {true};
    for (size_t l=0; l<L; ++l)
    {
        for (size_t h=0; h<H;)
        {
            if (isFree(cw[l][h]))
            {
                auto [startPos, endPos] {getStartEndPosH(cw, l, h)};
                if (startPos != endPos)
                {
                    auto fw {getFitWords(wv, startPos, endPos)};
                    for (const auto& w : fw)
                    {
                        auto lcw {cw};
                        auto lwv {wv};
                        if (putWord(lcw, w, startPos, endPos, hrtl, l, h))
                        {
                            if (removeWord(w, lwv))
                            {
                                return std::make_tuple(true, lcw);
                            }
                            const auto [res, rcw] = find(lcw, lwv);
                            if (res)
                            {
                                return std::make_tuple(true, rcw);
                            }
                        }
                    }
                }
                h = endPos;
            }
            ++h;
        }
    }
    
    hrtl = false;
    for (size_t h=0; h<H; ++h)
    {
        for (size_t l=0; l<L;)
        {
            if (isFree(cw[l][h]))
            {
                auto [startPos, endPos] {getStartEndPosL(cw, l, h)};
                if (startPos != endPos)
                {
                    auto fw {getFitWords(wv, startPos, endPos)};
                    for (const auto& w : fw)
                    {
                        auto lcw {cw};
                        auto lwv {wv};
                        if(putWord(lcw, w, startPos, endPos, hrtl, l, h))
                        {
                            if (removeWord(w, lwv))
                            {
                                return std::make_tuple(true, lcw);
                            }
                            const auto [res, rcw] = find(lcw, lwv);
                            if (res)
                            {
                                return std::make_tuple(true, rcw);
                            }
                        }
                    }
                    return std::make_tuple(false, cw);
                }
                l = endPos;
            }
            ++l;
        }
    }

    return std::make_tuple(false, cw);
}

// Complete the crosswordPuzzle function below.
vector<string> crosswordPuzzle(vector<string> crossword, string words)
{
    size_t last = 0;
    size_t next = 0;
    vector<string> wordsVect;
    while ((next = words.find(';', last)) != string::npos)
    {
        wordsVect.emplace_back(words.substr(last, next-last));
        last = next + 1;
    }
    wordsVect.emplace_back(words.substr(last));
    std::tie(std::ignore, crossword) = find(crossword, wordsVect);
    return crossword;
}

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