#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <ctime>
using namespace std;

fstream fin("in.txt", ios_base::in);
fstream fout("out.txt", std::ios_base::in | std::ios_base::out);
fstream fexpected("expected.txt", ios_base::in);

void printKMax(int arr[], int n, int k){
    //Write your code here.
    deque<int> dq;

    auto print_dq = [&dq](int i){ cout << "i:" << i << " dq:"; for (int i: dq) cout << i << " "; cout << endl; };

    for (int i = 0; i < k; ++i)
    {
        print_dq(i);

        while (!dq.empty())
        {
            // Remove all elements smaller than the currently
            if (arr[i] >= arr[dq.back()])
                dq.pop_back();
            else
                break;
        }

        dq.push_back(i);
    }

    fout << arr[dq.front()] << " ";

    for (int i = k; i < n; ++i)
    {
        print_dq(i);
    
        while (!dq.empty())
        {
            // Remove out of range elements
            if (dq.front() <= i - k)
                dq.pop_front();
            else
                break;
        }

        while (!dq.empty())
        {
            // Remove all elements smaller than the currently
            if (arr[i] >= arr[dq.back()])
                dq.pop_back();
            else
                break;
        }

        dq.push_back(i);

        // Largest element is always at the front of the queue
        fout << arr[dq.front()] << " ";
    }
}

int main() {

    ofstream outfile;
    outfile.open ("out.txt");

    double duration;
    std::clock_t start = std::clock();
    
    /***********************************************************/
    
    ios_base::sync_with_stdio(false);
    fin.tie(0);

    int t;
    fin >> t;
    while(t>0) {
        int n,k;
        fin >> n >> k;
        int i;
        int arr[n];
        for(i=0;i<n;i++)
            fin >> arr[i];
        printKMax(arr, n, k);
        t--;
    }
    
    /***********************************************************/

    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    fout.clear();
    fout.seekg(0, ios::beg);

    bool valid = true;
    string output, expected;
    while(getline(fout, output) && getline(fexpected, expected))
        if(output.compare(expected) != 0)
            valid = false;

    if (!fout.eof() || !fexpected.eof())
        valid = false;

    cout << (valid ? "ok" : "fail") << " " << duration << "s" << endl;
        
    return 0;
}