#include "../headers/analysis.h"

#include <iostream>
#include <stdlib.h>
#include "string"
#include <locale>

using namespace std;

Analysis::Analysis()
{
}
Disk disk;
Shared shrd;

void Analysis::start()
{
    system("clear");
    string end = "q";
    cout << "\033[1;36mBIENVENIDO A FILES \033[0m"
         << "\033[0;31m('" + end + "' para salir) \033[0m\n";

    while (true)
    {
        cout << "\033[1;31m~ \033[0m";
        string action;
        getline(cin, action);

        if (shrd.compare(action, end))
        {
            return;
        }

        string tkn = token(action);
        action.erase(0, tkn.length() + 1);
        cout << tkn << endl;
        execute(tkn, action);
    }
}

void Analysis::execute(string token, string body)
{

    if (shrd.compare(token, "MKDISK"))
    {
        vector<string> context = split(body, token);
        if (context.size() == 0)
        {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        disk.mkdisk(context);
    }
    else if (shrd.compare(token, "RMDISK"))
    {
        vector<string> context = split(body, token);
        if (context.size() == 0)
        {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        disk.rmdisk(context);
    }
    else if (shrd.compare(token, "FDISK"))
    {
        vector<string> context = split(body, token);
        if (context.size() == 0)
        {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        disk.fdisk(context);
    }
    else
    {
        cout << "BAD" << endl;
    }
}

string Analysis::token(string s)
{
    s.push_back(' ');
    string tkn = "";
    int status = -1;
    for (char &c : s)
    {
        if (status != -1)
        {
            if (c == ' ' || c == '-')
            {
                break;
            }

            tkn += c;
        }
        else if ((c != ' ' && status == -1))
        {
            tkn += c;
            status = 1;
        }
    }
    return tkn;
}

vector<string> Analysis::split(string s, string source)
{
    vector<string> result;
    if (s.empty())
    {
        return result;
    }

    s.push_back(' ');
    string tmp = "";
    int status = -1;
    for (char &c : s)
    {
        if (status != -1)
        {
            if (status == 3 && c == '\"')
            {
                status = 4;
            }
            else if (status == 2)
            {

                if (c == '\"')
                {
                    status = 3;
                }
                else
                {
                    status = 4;
                }
            }
            else if (status == 1)
            {
                if (c == '=')
                {
                    status = 2;
                }
                else if (c == ' ')
                {
                    continue;
                }
            }

            if ((status == 4) && c == ' ')
            {
                status = -1;
                result.push_back(tmp);
                tmp = "";
                continue;
            }
            tmp += c;
        }
        else if ((c == '-' && status == -1))
        {
            status = 1;
        }
    }

    cout << "RESULT: (BORRAR)" << endl;
    for (int i = 0; i < result.size(); i++)
    {
        std::cout << result.at(i) << endl;
    }
    return result;
}