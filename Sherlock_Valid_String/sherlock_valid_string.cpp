#include <bits/stdc++.h>

using namespace std;

// Complete the isValid function below.
std::string isValid(std::string &&s)
{
    unsigned freq_letters[26] = {0};
    for (char c : s)
    {
        freq_letters[c - 'a'] += 1;
    }

    // frequency, number of letters
    std::pair<unsigned, unsigned> freq[2] = {std::make_pair(freq_letters[0], 0), std::make_pair(0, 0)};

    for (unsigned i = 0; i < 26; ++i)
    {
        auto freq_letter{freq_letters[i]};
        if (freq_letter > 0)
        {
            if (freq_letter == freq[0].first)
            {
                ++freq[0].second;
            }
            else if (freq_letter == freq[1].first)
            {
                ++freq[1].second;
            }
            else if (freq[1].first == 0)
            {
                freq[1] = std::make_pair(freq_letter, 1);
            }
            else // 3 different letter frequencies
            {
                return "NO";
            }
        }
    }

    if ((freq[0].second == 0 || freq[1].second == 0) ||
        (freq[0].second == 1 && (freq[0].first == 1 || freq[0].first - 1 == freq[1].first)) ||
        (freq[1].second == 1 && (freq[1].first == 1 || freq[1].first - 1 == freq[0].first)))
    {
        return "YES";
    }

    return "NO";
}

int main()
{

    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(std::move(s));

    fout << result << "\n";

    fout.close();

    return 0;
}
