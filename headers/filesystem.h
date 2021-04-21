#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <bits/stdc++.h>
#include <math.h>

#include "../headers/shared.h"
#include "../headers/structs.h"
#include "../headers/mount.h"

using namespace std;

class FileSystem {
public:
    FileSystem(Mount m);

    void mkfs(vector<string> context);

    void mkfs(string id, string t, string fs);

    void ext2(Structs::Superblock spr, Structs::Partition p, int n, string path);

    void ext3(Structs::Superblock spr, Structs::Partition p, int n, string path);

private:
    Mount mount;
    Shared shared;
};

#endif // END OF DECLARATION