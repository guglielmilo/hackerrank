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

	unsigned int n, k, i=0;
	vector<int> v;
	vector<int> r;

	fin >> n >> k;

	while(n--)
	{
		int tmp;
		fin >> tmp;
		v.push_back(tmp);
	}

	if(k > v.size())
	{
		k = v.size();
	}

	while(k--)
	{
		vector<int>::iterator max = max_element(v.begin()+i, v.end());

		if(max != v.begin()+i)
		{
			iter_swap(v.begin()+i, max);
		}
		else
		{
			k++;
		}

		if(++i+1 == v.size())
		{
			break;
		}
	}

	for(vector<int>::iterator it= v.begin(); it != v.end(); ++it)
	{
		fout << *it << " ";
	}
	fout << endl;

    return 0;
}


