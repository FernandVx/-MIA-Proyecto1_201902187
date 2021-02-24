#include "../headers/shared.h"

#include <iostream>
#include <stdlib.h>
#include "string"
#include <locale>

#include <bits/stdc++.h>

using namespace std;

Shared::Shared()
{
}

string Shared::upper(string s)
{
    string u;
    locale loc;
    for (int i = 0; i < s.length(); i++)
    {
        u += toupper(s[i], loc);
    }
    return u;
}

bool Shared::compare(string s1, string s2)
{
    s1 = upper(s1);
    s2 = upper(s2);
    if (s1 == s2)
    {
        return true;
    }
    return false;
}

void Shared::handler(string title, string message)
{
    cout << "\033[1;31m Error: \033"
         << "\033[0;31m(" + title + ")~>\033[0m"
         << message << endl;
}