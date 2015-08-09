/*
 * common_child.cpp
 *
 *  Created on: 9 Aug 2015
 *      Author: Guillaume Militello
 */

#include <cmath>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

ifstream fin ("input.txt");
ofstream fout ("output.txt");

int main() {

	string s0, s1;
	getline(fin, s0);
	getline(fin, s1);

	int** mat = new int*[s1.size() + 1];
	for (unsigned int i = 0; i < s1.size() + 1; ++i)
	{
		mat[i] = new int[s0.size() + 1]();
	}

    // fill a matrix of s0 s1 matches
    for(unsigned int i = 0; i < s0.size(); ++i)
	{
		for(unsigned int j = 0; j < s1.size(); ++j)
		{
			if(s0.at(i) == s1.at(j))
			{
				// add the match to the next match
				mat[i+1][j+1] = mat[i][j] + 1;
			}
			else
			{
				// get the maximum previous paths
				mat[i+1][j+1] = max(mat[i][j+1], mat[i+1][j]);
			}
		}
	}

	fout << mat[s0.size()][s1.size()];

	for (unsigned int i = 0; i < s1.size() + 1; ++i)
	{
		delete[] mat[i];
	}
	delete[] mat;

    return 0;
}
