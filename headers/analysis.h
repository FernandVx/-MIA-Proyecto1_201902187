#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <string>
#include "../headers/disk.h"
#include "../headers/mount.h"
#include "../headers/shared.h"
#include "../headers/filesystem.h"
#include "../headers/admin.h"

using namespace std;

class Analysis {
public:
    Analysis();

    void start();

    void execute(string token, string body);

    string token(string s);

    vector<string> split(string s, string source);

private:
    Mount mount;
    Disk disk;
    Shared shrd;
    FileSystem fileSystem = FileSystem(mount);
    Admin admin;

    bool isLogged = false;
};

#endif // END OF DECLARATION