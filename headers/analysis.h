#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <string>
#include "../headers/disk.h"
#include "../headers/mount.h"
#include "../headers/shared.h"
#include "../headers/filesystem.h"
#include "../headers/admin.h"
#include "../headers/report.h"
#include "../headers/filemanager.h"

using namespace std;

class Analysis {
public:
    Analysis();

    void start();

    void execute(string token, string body);

    string token(string s);

    vector<string> split(string s, string source);

    void execute(vector<string> context);

    void execute(string p);

private:
    Mount mount;
    Disk disk;
    Shared shrd;
    FileSystem fileSystem = FileSystem(mount);
    Admin admin;
    Report report;
    FileManager fileManager;

    bool isLogged = false;
};

#endif // END OF DECLARATION