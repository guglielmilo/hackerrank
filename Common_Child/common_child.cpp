/*
 * common_child.cpp
 *
 *  Created on: 8 Aug 2015
 *      Author: guillaume
 */

#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

string s0, s1;

ifstream fin ("input.txt");
ofstream fout ("output.txt");

int max_common_child(unsigned int i, unsigned int j)
{
	if(i == s0.size() && j == s1.size())
	{
		return 0;
	}
	else
	{
		unsigned int max=0;
		unsigned int imax = s0.size();
		unsigned int jmax = s1.size();

		for(unsigned int _i = i; _i < imax; ++_i)
		{
			for(unsigned int _j = j; _j < jmax; ++_j)
			{
				if(_i > 0 && _j > 0 && s0.at(_i) == s1.at(_j))
				{
					// find in the string with new coordinates
					unsigned int m = max_common_child(_i+1,_j+1) + 1;
					if(m > max) max = m;

					// define new boundaries
					imax = s0.size()-max;
					jmax = _j;
					break;
				}
			}
		}
		return max;
	}
}

int main()
{

	getline(fin, s0);
	getline(fin, s1);

	// search in the string from original coordinates
	cout << max_common_child(0, 0) << endl;

	return 0;
}





