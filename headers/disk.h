#ifndef DISK_H
#define DISK_H

#include <string>
#include <algorithm>
#include "../headers/shared.h"
#include "../headers/structs.h"

using namespace std;

class Disk {
public:
    Disk();

    typedef struct _Transition {
        int partition;
        int start;
        int end;
        int before;
        int after;
    } Transition;

    void mkdisk(vector<string> context);

    void rmdisk(vector<string> context);

    void fdisk(vector<string> context);

    void generatedisk(string s, string f, string u, string p);

    void removedisk(string p);

    void generatepartition(string s, string u, string p, string t, string f, string n, string a);

    void deletepartition(string d, string p, string n);

    void addpartition(string add, string u, string n, string p);

    vector<Structs::Partition> getPartitions(Structs::MBR disk);

    Structs::MBR
    adjust(Structs::MBR mbr, Structs::Partition p, vector<Transition> t, vector<Structs::Partition> ps, int u);

    Structs::Partition findby(Structs::MBR mbr, string name, string path);

    void logic(Structs::Partition partition, Structs::Partition ep, string p);

    vector<Structs::EBR> getlogics(Structs::Partition partition, string p);


private:
    Shared shared;
};

#endif // END OF DECLARATION