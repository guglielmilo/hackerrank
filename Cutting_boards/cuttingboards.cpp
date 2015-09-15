#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

fstream fin("input.txt", ios_base::in);
fstream fout("output.txt", ios_base::out);

int main() {

	unsigned int t;

	fin >> t;

	while (t--)
	{
		unsigned int m, n;
		unsigned long long xd = 1, yd = 1;
		unsigned long long score = 0;
		vector<unsigned long long> x;
		vector<unsigned long long> y;

		fin >> m >> n;

		for (unsigned int i = 1; i < m; ++i)
		{
			unsigned long long tmp;
			fin >> tmp;
			x.push_back(tmp);
		}
		for (unsigned int i = 1; i < n; ++i)
		{
			unsigned long long tmp;
			fin >> tmp;
			y.push_back(tmp);
		}

		sort(x.begin(), x.end(), greater<unsigned long long>());
		sort(y.begin(), y.end(), greater<unsigned long long>());

		while (xd != m || yd != n)
		{
			// find max
			if(xd != m && yd != n)
			{
				vector<unsigned long long>::iterator itmx = x.begin() + xd - 1;
				vector<unsigned long long>::iterator itmy = y.begin() + yd - 1;

				if (*itmx > *itmy || (*itmx == *itmy && x.size() > y.size()))
				{
					score += *itmx * yd;
					++xd;
				}
				else
				{
					score += *itmy * xd;
					++yd;
				}
			}
			else if (yd == n)
			{
				score += *(x.begin() + xd - 1) * yd;
				++xd;
			}
			else
			{
				score += *(y.begin() + yd - 1) * xd;
				++yd;
			}
		}
		fout << score % 1000000007 << endl;
	}
    return 0;
}


