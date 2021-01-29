#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

bool rotate(vector<int> &A, int i, int n)
{
    if (i + 2 >= A.size())
    {
        return false;
    }

    // move i0, i1, i2
    if (n == A[i])
    {
        return true;
    }

    int tmp0 = A[i], tmp1 = A[i + 1];
    A[i] = A[i + 2];
    A[i + 1] = tmp0;
    A[i + 2] = tmp1;

    if (n == A[i])
    {
        return true;
    }

    int tmp0 = A[i], tmp1 = A[i + 1];
    A[i] = A[i + 2];
    A[i + 1] = tmp0;
    A[i + 2] = tmp1;

    if (n == A[i])
    {
        return true;
    }

    return false;
}

// Complete the larrysArray function below.
string larrysArray(vector<int> A)
{

    for (int i = 0; i < A.size(); ++i)
    {
        int n = i + 1;
        if (n == A[i])
        {
            continue;
        }

        // look for n
        for (int j = i; j < A.size(); ++j)
        {
            if (n == A[j])
            {
                // find i_min : first of three item to rotate
                int i_min = max(i, j - 2);

                // rotate until we are close enough
                while (i_min > i)
                {
                    if (!rotate(A, i_min, n))
                    {
                        return "NO";
                    }
                    i_min = max(i, i_min - 2);
                }

                if (!rotate(A, i_min, n))
                {
                    return "NO";
                }
            }
        }
    }
    return "YES";
}

int main()
{

    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++)
    {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string A_temp_temp;
        getline(cin, A_temp_temp);

        vector<string> A_temp = split_string(A_temp_temp);

        vector<int> A(n);

        for (int i = 0; i < n; i++)
        {
            int A_item = stoi(A_temp[i]);

            A[i] = A_item;
        }

        string result = larrysArray(A);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string)
{
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ')
    {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos)
    {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
