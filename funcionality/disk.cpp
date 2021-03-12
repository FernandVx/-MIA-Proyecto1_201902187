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

        Structs::Partition transition;
        transition.part_status = '1';
        transition.part_size = 650;
        transition.part_type = toupper('P');
        transition.part_fit = toupper('W');
        strcpy(transition.part_name, "TEST");
        transition.part_start = sizeof(disk) + 1;

        Structs::Partition transition2;
        transition2.part_status = '1';
        transition2.part_size = 714;
        transition2.part_type = toupper('P');
        transition2.part_fit = toupper('W');
        strcpy(transition2.part_name, "TEST");
        transition2.part_start = 70000;

        Structs::Partition pr;
        disk.mbr_Partition_1 = transition;
        disk.mbr_Partition_2 = transition2;
        disk.mbr_Partition_3 = pr;
        disk.mbr_Partition_4 = pr;

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

        Structs::MBR disk;
        cout << sizeof(disk) << endl;
        FILE *iFile = fopen(p.c_str(), "rb+");
        if (iFile != NULL)
        {
            rewind(iFile);
            fread(&disk, sizeof(disk), 1, iFile);
        }
        else
        {
            shared.handler("FDISK", "disco no existente");
            return;
        }
        fclose(iFile);

        cout << "Disco Leido:\nSize: " << disk.mbr_tamano << "\nDate: " << disk.mbr_fecha_creacion << "\nFit: " << disk.disk_fit << endl;
        vector<Structs::Partition> partitions = getPartitions(disk);
        vector<Structs::Transition> between;
        
        int used = 0;
        int ext = 0;
        int c = 1;
        int base = sizeof(disk) + 1;
        for (Structs::Partition prttn : partitions)
        {
            if (prttn.part_status == '1')
            {
                Structs::Transition trn;
                trn.partition = c;
                trn.start = prttn.part_start;
                trn.end = prttn.part_start + prttn.part_size;

                trn.before = trn.start - base;
                base = trn.end + 1;
                if (used != 0)
                {
                    between.at(used - 1).after = trn.start - (between.at(used - 1).end + 1);
                }

                between.push_back(trn);
                used++;
            }
            else if (prttn.part_type == 'E')
            {
                ext++;
            }

            if (used == 4)
            {
                throw runtime_error("ya no hay particiones libres");
            }
            else if (ext == 1 && shared.compare(t, "e"))
            {
                throw runtime_error("ya no se pueden crear más partciones extendidas");
            }

            c++;
        }

        if (used != 0)
        {
            between.at(between.size() - 1).after = disk.mbr_tamano - between.at(between.size() - 1).end;
        }
        Structs::Partition transition;
        transition.part_status = '1';
        transition.part_size = i;
        transition.part_type = toupper(t[0]);
        transition.part_fit = toupper(f[0]);
        strcpy(transition.part_name, n.c_str());
        cout << used << endl;
        adjust(disk, transition, between, partitions, used);

        if (shared.compare(t, "p"))
        {
        }
    }
    catch (invalid_argument &e)
    {
        shared.handler("FDISK", "-size debe ser un entero");
        return;
    }
    catch (exception &e)
    {
        shared.handler("FDISK", e.what());
        return;
    }
}

vector<Structs::Partition> Disk::getPartitions(Structs::MBR disk)
{
    vector<Structs::Partition> v;
    v.push_back(disk.mbr_Partition_1);
    v.push_back(disk.mbr_Partition_2);
    v.push_back(disk.mbr_Partition_3);
    v.push_back(disk.mbr_Partition_4);
    return v;
}

Structs::MBR Disk::adjust(Structs::MBR mbr, Structs::Partition p, vector<Structs::Transition> t, vector<Structs::Partition> ps, int u)
{
    cout << "TESTTTTTTTT" << endl;
    for (Structs::Transition tr : t)
    {
        cout << tr.partition << ") (" << tr.start << " <-> " << tr.end << ") " << tr.before << "," << tr.after << endl;
    }

    if (u == 0)
    {
        p.part_start = sizeof(mbr) + 1;
        mbr.mbr_Partition_1 = p;
    }
    else
    {
        Structs::Transition toUse;
        int c = 0;
        for (Structs::Transition tr : t)
        {
            if (c == 0)
            {
                toUse = tr;
                c++;
                continue;
            }

            if (toupper(mbr.disk_fit) == 'F')
            {
                cout << "PRIMER" << endl;

                if (toUse.before >= p.part_size || toUse.after >= p.part_size)
                {
                    break;
                }
                toUse = tr;
            }
            else if (toupper(mbr.disk_fit) == 'B')

            {
                cout << "MEJOR" << endl;

                if (!(toUse.before >= p.part_size) || !(toUse.after >= p.part_size))
                {
                    toUse = tr;
                }
                else
                {

                    if (tr.before >= p.part_size || tr.after >= p.part_size)
                    {
                        int b1 = toUse.before - p.part_size;
                        int a1 = toUse.after - p.part_size;
                        int b2 = tr.before - p.part_size;
                        int a2 = tr.after - p.part_size;

                        if ((b1 < b2 && b1 < a2) || (a1 < b2 && a1 < a2))
                        {
                            c++;
                            continue;
                        }
                        toUse = tr;
                    }
                }
            }
            else if (toupper(mbr.disk_fit) == 'W')
            {
                {
                    cout << "PEOR" << endl;
                }

                if (!(toUse.before >= p.part_size) || !(toUse.after >= p.part_size))
                {
                    toUse = tr;
                }
                else
                {

                    if (tr.before >= p.part_size || tr.after >= p.part_size)
                    {
                        int b1 = toUse.before - p.part_size;
                        int a1 = toUse.after - p.part_size;
                        int b2 = tr.before - p.part_size;
                        int a2 = tr.after - p.part_size;

                        if ((b1 > b2 && b1 > a2) || (a1 > b2 && a1 > a2))
                        {
                            c++;
                            continue;
                        }
                        toUse = tr;
                    }
                }
            }
            c++;
        }
        if (toUse.before >= p.part_size || toUse.after >= p.part_size)
        {
            if (toupper(mbr.disk_fit) == 'F')
            {

                if (toUse.before >= p.part_size)
                {
                    p.part_start = (toUse.start - toUse.before);
                }
                else
                {
                    p.part_start = toUse.end + 1;
                }
            }
            else if (toupper(mbr.disk_fit) == 'B')
            {

                int b1 = toUse.before - p.part_size;
                int a1 = toUse.after - p.part_size;

                if ((toUse.before >= p.part_size && b1 < a1) || !(toUse.after >= p.part_start))
                {
                    p.part_start = (toUse.start - toUse.before);
                }
                else
                {
                    p.part_start = toUse.end + 1;
                }
            }
            else if (toupper(mbr.disk_fit) == 'W')
            {
                int b1 = toUse.before - p.part_size;
                int a1 = toUse.after - p.part_size;

                if ((toUse.before >= p.part_size && b1 > a1) || !(toUse.after >= p.part_start))
                {
                    p.part_start = (toUse.start - toUse.before);
                }
                else
                {
                    p.part_start = toUse.end + 1;
                }
            }

            cout << p.part_name << ") (" << p.part_start << " <-> " << p.part_size << ") " << p.part_status << " , " << p.part_type << endl;
            int c = 0;
            cout<<c<<endl;
            for (Structs::Partition pp : ps)
            {
                if (pp.part_status == '0')
                {
                    c++;
                    break;
                }
                c++;
            }
            cout<<c<<endl;
            ps.at(c) = p;

            Structs::Partition aux;
            for (int i = 3; i >= 0; i--)
            {
                for (int j = 0; j < i; j++)
                {
                    if ((ps.at(j).part_start > ps.at(j + 1).part_start) && ps.at(j + 1).part_status != '0')
                    {
                        aux = ps.at(j + 1);
                        ps.at(j + 1) = ps.at(j);
                        ps.at(j + 1) = aux;
                    }
                }
            }

            for (Structs::Partition pp : ps)
            {
                cout << pp.part_status << ") (" << pp.part_start << " <-> " << pp.part_size << ") " << pp.part_status << " , " << pp.part_type << endl;
            }
        }
        else
        {
            throw runtime_error("no hay espacio suficiente");
        }
    }
}