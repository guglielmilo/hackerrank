#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <regex>
#include <fstream>
#include <ctime>
using namespace std;

fstream fin("in.txt", ios_base::in);
fstream fout("out.txt", ios_base::in | ios_base::out);
fstream fexpected("expected.txt", ios_base::in);

void solve(vector <int> arr, int money) {
    // Complete this function
    map<int, unsigned> m;

    int arrSize = arr.size();
    for (int i=0; i <= arrSize; ++i)
    {
        int n = arr[i];
        if (n >= money)
            continue;

        int f = money - n;
        
        // look if it a corresponding flavor
        auto mi = m.find(n);
        if (mi == m.end())
        {
            m[f] = i; // save the corresponding index
        }
        else
        {
            fout << m[n] + 1 << " " << i + 1 << endl;
            break;
        }
    }
}

int main() {

    ofstream outfile;
    outfile.open ("out.txt");

    double duration;
    clock_t start = clock();
    
    /***********************************************************/
    
    ios_base::sync_with_stdio(false);
    fin.tie(0);

    int t;
    fin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int money;
        fin >> money;
        int n;
        fin >> n;
        vector<int> arr(n);
        for(int arr_i = 0; arr_i < n; arr_i++){
           fin >> arr[arr_i];
        }
        solve(arr, money);
    }
    
    /***********************************************************/

    duration = (clock() - start) / (double) CLOCKS_PER_SEC;

    fout.clear();
    fout.seekg(0, ios::beg);

    bool valid = true;
    string output, expected;
    while(getline(fout, output) && getline(fexpected, expected))
    {
        if(output.compare(expected) != 0)
        {
            valid = false;
            break;
        }
    }

    if (fout.eof() && !fexpected.eof())
    {
        valid = false;
    }

    cout << (valid ? "ok" : "fail") << " " << duration << "s" << endl;
        
    return 0;
}