#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <bits/stdc++.h>
#include "../headers/shared.h"
#include "../headers/structs.h"
#include "../headers/mount.h"

using namespace std;

class Admin {
public:
    Admin();

    typedef struct _User {
        string user;
        string password;
        string id;
        int uid;
    } User;

    bool login(vector<string> context, Mount m);

    bool login(string u, string p, string id);

    bool logout();

    void grp(vector<string> context, string action);

    void usr(vector<string> context, string action);

    void mkgrp(string n);

    void rmgrp(string n);

    void mkusr(string usr, string pwd, string grp);

    void rmusr(string usr);

    vector<string> getElements(string txt, char c);

private:
    Shared shared;
    User logged;
    Mount mount;
};

#endif // END OF DECLARATION