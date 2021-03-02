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
            auto itr = find(required.begin(), required.end(), id);
            required.erase(itr);
            size = current;
        }
        else if (shared.compare(id, "f"))
        {
            f = current;
        }
        else if (shared.compare(id, "u"))
        {
            u = current;
        }
        else if (shared.compare(id, "path"))
        {
            auto itr = find(required.begin(), required.end(), id);
            required.erase(itr);
            path = current;
        }
    }
    if (required.size() != 0)
    {
        shared.handler("MKDISK", "requiere ciertos parámetros obligatorios");
        return;
    }
    generatedisk(size, f, u, path);
}

void Disk::generatedisk(string s, string f, string u, string p)
{
    Structs::MBR disk;
    try
    {
        int i = stoi(s);

        if (i <= 0)
        {
            throw runtime_error("-size debe ser mayor que 0");
        }

        if (shared.compare(f, "bf") || shared.compare(f, "ff") || shared.compare(f, "wf"))
        {
            f = f.substr(0, 1);
        }
        else
        {
            throw runtime_error("-f necesita valores específicos");
        }

        if (shared.compare(u, "k") || shared.compare(u, "m"))
        {

            i *= (shared.compare(u, "k")) ? 1024 : 1024 * 1024;
        }
        else
        {
            throw runtime_error("-u necesita valores específicos");
        }

        char datetime[20];

        time_t t = time(0);
        struct tm *tm = localtime(&t);
        strftime(datetime, 20, "%d/%m/%Y %H:%M:%S", tm);

        disk.mbr_tamano = i;
        strcpy(disk.mbr_fecha_creacion, datetime);
        disk.disk_fit = toupper(f[0]);
        disk.mbr_disk_signature = rand() % 8999 + 1000;

        FILE *validate = fopen(p.c_str(), "r");
        if (validate != NULL)
        {
            fclose(validate);
            shared.handler("MKDISK", "el disco ya existe");
            return;
        }
        cout << "Nuevo disco: ***********************\nSize: " << disk.mbr_tamano << "\ndate: " << disk.mbr_fecha_creacion << "\nFit: " << disk.disk_fit << "\nDisk_Signature: " << disk.mbr_disk_signature << endl;
        cout << "Bits del MBR: " << sizeof(Structs::MBR) << endl;

        cout << "Path: " << p << endl;

        if (p.substr(0, 1) == "\"")
        {
            p = p.substr(1, p.length() - 2);
        }

        FILE *file = fopen(p.c_str(), "w+b");
        // if (file != NULL)
        // {
        //     fwrite("\0", 1, 1, bfile);
        //     fseek(bfile, numSize - 1, SEEK_SET);
        //     fwrite("\0", 1, 1, bfile);
        //     rewind(bfile);
        //     fwrite(&disco, sizeof(Structs::MBR), 1, bfile);
        //     mkDisk::crearRaid(&disco, path);
        // }
        // else
        // {
        cout << "Path creado exitosamente" << endl;
        //Creo la carpeta de la direccion.
        // string comando1 = "mkdir -p \"" + p + "\"";
        // string comando2 = "rmdir \"" + path + "\"";
        // system(comando1.c_str());
        // system(comando2.c_str());

        fwrite("\0", 1, 1, file);
        fseek(file, i - 1, SEEK_SET);
        fwrite("\0", 1, 1, file);
        rewind(file);
        fwrite(&disk, sizeof(Structs::MBR), 1, file);
        // mkDisk::crearRaid(&disco, path);
        // }
        fclose(file);
        // }

        shared.response("MKDISK", "disco creado correctamente");
    }
    catch (invalid_argument &e)
    {
        shared.handler("MKDISK", "-size debe ser un entero");
        return;
    }
    catch (exception &e)
    {
        shared.handler("MKDISK", e.what());
        return;
    }
}

void Disk::rmdisk(vector<string> context)
{
    vector<string> required = {"path"};
    string path;
    for (int i = 0; i < context.size(); i++)
    {
        string current = context.at(i);
        string id = current.substr(0, current.find("="));
        current.erase(0, id.length() + 1);

        if (shared.compare(id, "path"))
        {
            auto itr = find(required.begin(), required.end(), id);
            required.erase(itr);
            path = current;
        }
    }
    if (required.size() != 0)
    {
        shared.handler("RMDISK", "requiere un parámetro obligatorio");
        return;
    }
    removedisk(path);
}

void Disk::removedisk(string p)
{
    if (p.substr(0, 1) == "\"")
    {
        p = p.substr(1, p.length() - 2);
    }

    FILE *validate = fopen(p.c_str(), "r");
    if (validate != NULL)
    {
        fclose(validate);
        if (shared.confirmation("RMDISK", "desea eliminar el disco"))
        {
            if (remove(p.c_str()) == 0)
            {
                shared.response("RMDISK", "disco eliminado correctamente");
                return;
            }
        }
    }
    shared.handler("RMDISK", "el disco no existe");
}

void Disk::fdisk(vector<string> context)
{
    bool dlt = false;
    for (string current : context)
    {
        string id = current.substr(0, current.find("="));
        current.erase(0, id.length() + 1);

        if (shared.compare(id, "delete"))
        {
            dlt = true;
        }
    }
    if (!dlt)
    {
        vector<string> required = {"size", "path", "name"};
        string size = "";
        string u = "k";
        string path = "";
        string type = "P";
        string f = "WF";
        string name = "";
        string add = "";

        for (string current : context)
        {
            string id = current.substr(0, current.find("="));
            current.erase(0, id.length() + 1);

            if (shared.compare(id, "size"))
            {
                auto itr = find(required.begin(), required.end(), id);
                required.erase(itr);
                size = current;
            }
            else if (shared.compare(id, "u"))
            {
                u = current;
            }
            else if (shared.compare(id, "path"))
            {
                auto itr = find(required.begin(), required.end(), id);
                required.erase(itr);
                path = current;
            }
            else if (shared.compare(id, "type"))
            {
                type = current;
            }
            else if (shared.compare(id, "f"))
            {
                f = current;
            }
            else if (shared.compare(id, "name"))
            {
                auto itr = find(required.begin(), required.end(), id);
                required.erase(itr);
                name = current;
            }
            else if (shared.compare(id, "add"))
            {
                add = current;
            }
        }
        generatepartition(size, u, path, type, f, name, add);
    }
    else
    {
        vector<string> required = {"path", "name"};
        string _delete = "";
        string path = "";
        string name = "";
    }
}

void Disk::generatepartition(string s, string u, string p, string t, string f, string n, string a)
{
    Structs::Partition partition;
    try
    {
        int i = stoi(s);

        if (i <= 0)
        {
            throw runtime_error("-size debe ser mayor que 0");
        }

        if (shared.compare(u, "b") || shared.compare(u, "k") || shared.compare(u, "m"))
        {

            if (!shared.compare(u, "b"))
            {
                i *= (shared.compare(u, "k")) ? 1024 : 1024 * 1024;
            }
        }
        else
        {
            throw runtime_error("-u necesita valores específicos");
        }

        if (p.substr(0, 1) == "\"")
        {
            p = p.substr(1, p.length() - 2);
        }

        if (!(shared.compare(t, "p") || shared.compare(t, "e") || shared.compare(t, "l")))
        {
            throw runtime_error("-t necesita valores específicos");
        }

        if (!(shared.compare(f, "bf") || shared.compare(f, "ff") || shared.compare(f, "wf")))
        {
            throw runtime_error("-f necesita valores específicos");
        }
    }
    catch (invalid_argument &e)
    {
        shared.handler("MKDISK", "-size debe ser un entero");
        return;
    }
    catch (exception &e)
    {
        shared.handler("MKDISK", e.what());
        return;
    }
}