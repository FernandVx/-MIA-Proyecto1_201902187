#include "../headers/analysis.h"

#include <iostream>
#include <stdlib.h>
#include "string"
#include <locale>

using namespace std;

Analysis::Analysis() {
}


void Analysis::start() {
    system("clear");
    string end = "q";
    cout << "\033[1;36mBIENVENIDO A FILES \033[0m"
         << "\033[0;31m('" + end + "' para salir) \033[0m\n";

    while (true) {
        cout << "\033[1;31m~ \033[0m";
        string action;
        getline(cin, action);

        if (shrd.compare(action, end)) {
            return;
        } else if (action.rfind('#', 0) == 0) {
            continue;
        } else if (shrd.compare(action, "pause")) {
            string tmp;
            getline(cin, tmp);
            continue;
        }

        string tkn = token(action);
        action.erase(0, tkn.length() + 1);
        execute(tkn, action);
    }
}

void Analysis::execute(string token, string body) {

    if (shrd.compare(token, "MKDISK")) {
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        disk.mkdisk(context);
    } else if (shrd.compare(token, "RMDISK")) {
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        disk.rmdisk(context);
    } else if (shrd.compare(token, "FDISK")) {
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        disk.fdisk(context);
    } else if (shrd.compare(token, "MOUNT")) {
        vector<string> context = split(body, token);
        mount.mount(context);
    } else if (shrd.compare(token, "UNMOUNT")) {
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        mount.unmount(context);
    } else if (shrd.compare(token, "MKFS")) {
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        fileSystem = FileSystem(mount);
        fileSystem.mkfs(context);
    } else if (shrd.compare(token, "LOGIN")) {
        if (isLogged) {
            shrd.handler(token, "necesita hacer un logout primero");
            return;
        }
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        isLogged = admin.login(context, mount);
    } else if (shrd.compare(token, "LOGOUT")) {
        if (!isLogged) {
            shrd.handler(token, "necesita un usuario activo");
            return;
        }
        isLogged = admin.logout();
    } else if (shrd.compare(token, "MKGRP")) {
        if (!isLogged) {
            shrd.handler(token, "login para continuar");
            return;
        }
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        admin.grp(context, "MK");
    } else if (shrd.compare(token, "RMGRP")) {
        if (!isLogged) {
            shrd.handler(token, "login para continuar");
            return;
        }
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        admin.grp(context, "RM");
    } else if (shrd.compare(token, "MKUSR")) {
        if (!isLogged) {
            shrd.handler(token, "login para continuar");
            return;
        }
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        admin.usr(context, "MK");
    } else if (shrd.compare(token, "RMUSR")) {
        if (!isLogged) {
            shrd.handler(token, "login para continuar");
            return;
        }
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        admin.usr(context, "RM");
    } else if (shrd.compare(token, "RMDISK")) {
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        disk.rmdisk(context);
    } else if (shrd.compare(token, "MKDIR")) {
        if (!isLogged) {
            shrd.handler(token, "login para continuar");
            return;
        }
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        string p;
        Structs::Partition partition = mount.getmount(admin.logged.id, &p);
        fileManager.mkdir(context, partition, p);
    } else if (shrd.compare(token, "REP")) {
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        report.generate(context, mount);
    } else if (shrd.compare(token, "EXEC")) {
        vector<string> context = split(body, token);
        if (context.size() == 0) {
            shrd.handler(token, "requiere parámetros");
            return;
        }
        execute(context);
    } else {
        shrd.handler("CONSOLE", "comando no reconocido");
    }
}

string Analysis::token(string s) {
    s.push_back(' ');
    string tkn = "";
    int status = -1;
    for (char &c : s) {
        if (status != -1) {
            if (c == ' ' || c == '-') {
                break;
            }

            tkn += c;
        } else if ((c != ' ' && status == -1)) {
            tkn += c;
            status = 1;
        }
    }
    return tkn;
}

vector<string> Analysis::split(string s, string source) {
    vector<string> result;
    if (s.empty()) {
        return result;
    }

    s.push_back(' ');
    string tmp = "";
    int status = -1;
    for (char &c : s) {
        if (status != -1) {
            if (status == 3 && c == '\"') {
                status = 4;
            } else if (status == 2) {

                if (c == '\"') {
                    status = 3;
                } else {
                    status = 4;
                }
            } else if (status == 1) {
                if (c == '=') {
                    status = 2;
                } else if (c == ' ') {
                    continue;
                }
            }

            if ((status == 4) && c == ' ') {
                status = -1;
                result.push_back(tmp);
                tmp = "";
                continue;
            }
            tmp += c;
        } else if ((c == '-' && status == -1)) {
            status = 1;
        }
    }
//
//    cout << "RESULT: (BORRAR)" << endl;
//    for (int i = 0; i < result.size(); i++) {
//        std::cout << result.at(i) << endl;
//    }
    return result;
}

void Analysis::execute(vector<string> context) {
    vector<string> required = {"path"};
    string path;
    for (auto current : context) {
        string id = shrd.lower(current.substr(0, current.find('=')));
        current.erase(0, id.length() + 1);
        if (current.substr(0, 1) == "\"") {
            current = current.substr(1, current.length() - 2);
        }

        if (shrd.compare(id, "path")) {
            if (count(required.begin(), required.end(), id)) {
                auto itr = find(required.begin(), required.end(), id);
                required.erase(itr);
                path = current;
            }
        }
    }
    if (!required.empty()) {
        shrd.handler("EXEC", "requiere un parámetro obligatorio");
        return;
    }
    execute(path);
}

void Analysis::execute(string p) {

    FILE *rfile = fopen(p.c_str(), "rb+");
    if (rfile == NULL) {
        shrd.handler("EXEC", "archivo no existente");
        return;
    }
    fclose(rfile);

    ifstream file(p);
    string str;

    string end = "q";
    while (std::getline(file, str)) {


        string action = str;
        if (shrd.compare(action, end)) {
            return;
        } else if (action.rfind('#', 0) == 0 || action == "\n" || action.empty()) {
            continue;
        } else if (shrd.compare(action, "pause")) {
            string tmp;
            cout << "\033[1;31m~ \033[0m" << "PAUSE" << endl;

            getline(cin, tmp);
            continue;
        }

        string tkn = token(action);
        action.erase(0, tkn.length() + 1);

        string prnt = tkn;
        vector<string> context = split(action, tkn);
        if (context.size() != 0) {
            for (string tm: context) {
                prnt += " " + tm;
            }
        }

        cout << "\033[1;31m~ \033[0m" << prnt << endl;
        execute(tkn, action);
        cout << endl;
    }
}
