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

	unsigned int m, n;
	long long max = 0;

	fin >> m >> n;

	long long * l = new long long[m]();

	while (n--)
	{
		unsigned int a, b, k;

		fin >> a >> b >> k;

		l[a-1] += k;

		if(b < m)
		{
			l[b] -= k;
		}
	}

	for(unsigned int i = 1; i < m; ++i)
	{
		l[i] += l[i-1];

		if(l[i] > max)
		{
			max = l[i];
		}
	}

	fout << max;

	delete[] l;

    return 0;
}


