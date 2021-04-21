#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <bits/stdc++.h>
#include "../headers/shared.h"
#include "../headers/structs.h"
#include "../headers/disk.h"
#include "../headers/mount.h"
#include "../headers/filemanager.h"

using namespace std;

class Report {
public:
    Report();

    void generate(vector<string> context, Mount m);

    void mbr(string p, string id);

    void disk(string p, string id);

    void inode(string p, string id);

    void block(string p, string id);

    void bminode(string p, string id);

    void bmblock(string p, string id);

    void sb(string p, string id);

    void tree(string p, string id);

    void journaling(string p, string id);


private:
    Shared shared;
    Disk dsk;
    Mount mount;
    FileManager fileManager;
};

#endif // END OF DECLARATION