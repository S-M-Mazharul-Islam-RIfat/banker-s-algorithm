#include <bits/stdc++.h>
using namespace std;
int main()
{
    // Take input
    int p;
    cout << "How many process ? ";
    cin >> p;
    int r;
    cout << "How many resources ? ";
    cin >> r;
    cout << '\n';
    int nxt = 1;
    cout << "Enter the allocation value : " << '\n';
    for (char ch = 'A';; ch++)
    {
        if (nxt > r)
            break;
        cout << ch << " ";
        nxt++;
    }
    cout << '\n';

    vector<vector<int>> va(p, vector<int>(r));
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            cin >> va[i][j];

    cout << '\n';
    cout << "Enter the max value : " << '\n';
    nxt = 1;
    for (char ch = 'A';; ch++)
    {
        if (nxt > r)
            break;
        cout << ch << " ";
        nxt++;
    }
    cout << '\n';
    vector<vector<int>> vm(p, vector<int>(r));
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            cin >> vm[i][j];

    cout << '\n';

    cout << "Enter the available value : " << '\n';
    nxt = 1;
    for (char ch = 'A';; ch++)
    {
        if (nxt > r)
            break;
        cout << ch << " ";
        nxt++;
    }
    cout << '\n';
    vector<int> avaiable(r);
    for (int i = 0; i < r; i++)
        cin >> avaiable[i];

    cout << '\n';

    // Calculating need value;
    vector<vector<int>> need(p, vector<int>(r));
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = (vm[i][j] - va[i][j]);

    vector<bool> finish(p);

    // Apply the safety algo
    vector<string> rem, safe;
    for (int i = 0; i < p; i++)
    {
        bool ok = true;
        for (int j = 0; j < r; j++)
        {
            if (need[i][j] <= avaiable[j])
                ok = true;
            else
            {
                ok = false;
                break;
            }
        }
        if (!ok)
        {
            string t = "P";
            t.push_back(static_cast<char>(i + '0'));
            rem.push_back(t);
        }
        else
        {
            finish[i] = true;
            string t = "P";
            t.push_back(static_cast<char>(i + '0'));
            safe.push_back(t);
            for (int k = 0; k < p; k++)
                avaiable[k] += va[i][k];
        }
    }

    vector<string> temp;
    int idx = 0, stillRem = (int)rem.size(), cnt = 0;
    while (count(finish.begin(), finish.end(), true) != p)
    {
        if (cnt == stillRem)
        {
            cout << "Unsafe State" << '\n';
            exit(0);
        }
        if (idx == (int)rem.size())
        {
            rem = temp;
            idx = 0;
        }
        int pos = (rem[idx][1] - '0');
        for (int i = 0; i < p; i++)
        {
            if (pos == i)
            {
                bool ok = true;
                for (int j = 0; j < r; j++)
                {
                    if (need[i][j] <= avaiable[j])
                        ok = true;
                    else
                    {
                        ok = false;
                        break;
                    }
                }
                if (!ok)
                {
                    string t = "P";
                    t.push_back(static_cast<char>(i + '0'));
                    temp.push_back(t);
                }
                else
                {
                    finish[i] = true;
                    string t = "P";
                    t.push_back(static_cast<char>(i + '0'));
                    safe.push_back(t);
                    for (int k = 0; k < p; k++)
                        avaiable[k] += va[i][k];
                }
            }
        }
        idx++;
        cnt++;
    }

    cout << "Safe State Sequence : ";
    for (int i = 0; i < (int)safe.size(); i++)
    {
        if (i < (int)safe.size() - 1)
            cout << safe[i] << "->";
        else
            cout << safe[i];
    }
    cout << '\n';
    return 0;
}
