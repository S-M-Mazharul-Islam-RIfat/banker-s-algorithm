#include <bits/stdc++.h>
using namespace std;
int p, r;
void updatedTable(vector<vector<int>> va, vector<vector<int>> need, vector<int> avaiable)
{
    cout << '\n'
         << '\n';
    cout << "Allocation Value -> " << '\n';
    int nxt = 1;
    for (char ch = 'A';; ch++)
    {
        if (nxt > r)
            break;
        cout << ch << " ";
        nxt++;
    }
    cout << '\n';
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
            cout << va[i][j] << " ";
        cout << '\n';
    }

    cout << '\n';
    cout << "Need Value -> " << '\n';
    nxt = 1;
    for (char ch = 'A';; ch++)
    {
        if (nxt > r)
            break;
        cout << ch << " ";
        nxt++;
    }
    cout << '\n';
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
            cout << need[i][j] << " ";
        cout << '\n';
    }
    cout << '\n';

    cout << '\n';
    cout << "Available Value -> " << '\n';
    nxt = 1;
    for (char ch = 'A';; ch++)
    {
        if (nxt > r)
            break;
        cout << ch << " ";
        nxt++;
    }
    cout << '\n';
    for (int i = 0; i < r; i++)
        cout << avaiable[i] << " ";
    cout << '\n'
         << '\n';
}
int main()
{
    // Take input
    cout << "How many process ? ";
    cin >> p;
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
    vector<vector<int>> need(p, vector<int>(r));

    // Calculating need value;
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = (vm[i][j] - va[i][j]);

    // Resource Request Algo Input
    int req;
    cout << "How many request ? ";
    cin >> req;

    map<string, vector<int>> mp;
    for (int i = 0; i < req; i++)
    {
        string s;
        cout << "Enter the process value : ";
        cin >> s;
        cout << "Enter the resource value : ";
        for (int j = 0; j < r; j++)
        {
            int in;
            cin >> in;
            mp[s].push_back(in);
        }
    }

    // Applying Resource Request Algo Input
    vector<string> safe;
    vector<bool> stp1(p), stp2(p);
    fill(stp1.begin(), stp1.end(), true);
    fill(stp2.begin(), stp2.end(), true);
    for (auto it : mp)
    {
        string pp = it.first;
        vector<int> v = it.second;

        // Check the two steps of resource request algo
        bool step1 = false, step2 = false;
        for (int i = 0; i < (int)v.size(); i++)
        {
            if (v[i] <= need[pp[1] - '0'][i])
                step1 = true;
            else
            {
                step1 = false;
                stp1[i] = false;
                break;
            }
        }
        if (step1)
        {
            for (int i = 0; i < (int)v.size(); i++)
            {
                if (v[i] <= avaiable[i])
                    step2 = true;
                else
                {
                    step2 = false;
                    stp2[i] = false;
                    break;
                }
            }

            // Update 3 value(Available,Allocation,Need)
            for (int i = 0; i < r; i++)
            {
                avaiable[i] -= v[i];
                va[pp[1] - '0'][i] += v[i];
                need[pp[1] - '0'][i] -= v[i];
            }

            cout << '\n'
                 << "Print the updated table : " << '\n';
            updatedTable(va, need, avaiable);

            // Apply the safety algo
            vector<bool> finish(p);
            vector<string> rem;
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

            // Process remaining value
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
        }
        cout << '\n';
        if (!stp1[pp[1] - '0'])
            cout << "Process has exceeded its maximum claim." << '\n';
        else if (!stp2[pp[1] - '0'])
            cout << "Resources are not available." << '\n';
        else
        {
            // Print the safe state sequence
            cout << "Safe State Sequence : ";
            for (int i = 0; i < (int)safe.size(); i++)
            {
                if (i < (int)safe.size() - 1)
                    cout << safe[i] << "->";
                else
                    cout << safe[i];
            }
            cout << '\n'
                 << '\n';
        }
    }
    return 0;
}
