#include "../headers/disk.h"

#include <iostream>
#include <stdlib.h>
#include "string"
#include <locale>

using namespace std;

Shared shared;

Disk::Disk()
{
}

void Disk::mkdisk(vector<string> context)
{
    vector<string> required = {"size", "path"};
    string size = "";
    string f = "FF";
    string u = "m";
    string path = "";

    for (int i = 0; i < context.size(); i++)
    {
        string current = context.at(i);
        string id = current.substr(0, current.find("="));
        current.erase(0, id.length() + 1);
        if (shared.compare(id, "size"))
        {
            remove(begin(required), end(required), id);
        }
        else if (shared.compare(id, "f"))
        {
        }
        else if (shared.compare(id, "u"))
        {
        }
        else if (shared.compare(id, "path"))
        {
            remove(begin(required), end(required), id);
        }
    }
}