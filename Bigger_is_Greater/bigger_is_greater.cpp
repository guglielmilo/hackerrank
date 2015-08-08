/*
 * bigger_is_great.cpp
 *
 *  Created on: 8 Aug 2015
 *      Author: Guillaume Militello
 */

#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

ifstream fin ("input.txt");
ofstream fout ("output.txt");

int main() {

    unsigned int n;
    string ns;

    getline(fin, ns);
    n = atoi(ns.c_str());

    while (n--)
	{
    	string s;
		getline(fin, s);

        //Find the first index who is lexographically greater in reverse
        int index = 0;

		for (int i = s.size() - 1; i > 0; --i)
		{
			if (s.at(i - 1) < s.at(i))
			{
				index = i;
				break;
			}
		}

		// Already lexographically sorted
		if (index < 1)
		{
			fout << "no answer" << endl;
			continue;
		}

		// Find the smallest character greater than s.at(index)
		int index_min = index;

		for (unsigned int j = index + 1; j < s.size(); ++j)
		{
			if (s.at(j) > s.at(index - 1) && s.at(j) < s.at(index_min))
			{
				index_min = j;
			}
		}

		// Swap index and index_min
		swap(s[index - 1], s[index_min]);

		// Sort lexographically the new portion and actualize s
		string sub = s.substr(index, s.size() - index);
		sort(sub.begin(), sub.end());
		s = s.substr(0, index) + sub;

		fout << s << endl;
	}
    return 0;
}


