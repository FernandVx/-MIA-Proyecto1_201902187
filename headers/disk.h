#ifndef DISK_H
#define DISK_H

#include <string>
#include <algorithm>
#include "../headers/shared.h"
#include "../headers/structs.h"

using namespace std;

class Disk
{
public:
    Disk();
    void mkdisk(vector<string> context);
    void generatedisk(string s, string f, string u, string p);
    void rmdisk(vector<string> context);
    void removedisk(string p);
    void fdisk(vector<string> context);
    void generatepartition(string s, string u, string p, string t, string f, string n, string a);
};

#endif // END OF DECLARATION