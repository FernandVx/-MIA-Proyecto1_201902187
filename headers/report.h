#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <bits/stdc++.h>
#include "../headers/shared.h"
#include "../headers/structs.h"
#include "../headers/disk.h"
#include "../headers/mount.h"

using namespace std;

class Report {
public:
    Report();

    void generate(vector<string> context, Mount m);

    void mbr(string p, string id);


private:
    Shared shared;
    Mount mount;
};

#endif // END OF DECLARATION