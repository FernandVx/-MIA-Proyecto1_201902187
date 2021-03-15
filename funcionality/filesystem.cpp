#include "../headers/filesystem.h"

#include <iostream>
#include <stdlib.h>
#include "string"
#include <locale>

using namespace std;

FileSystem::FileSystem(Mount m) {
    mount = m;
}

void FileSystem::mkfs(vector<string> context) {
    vector<string> required = {"id"};
    string id;
    string type = "Full";
    string fs = "2fs";

    for (int i = 0; i < context.size(); i++) {
        string current = context.at(i);
        string id_ = current.substr(0, current.find("="));
        current.erase(0, id_.length() + 1);
        if (current.substr(0, 1) == "\"") {
            current = current.substr(1, current.length() - 2);
        }

        if (shared.compare(id_, "id")) {
            auto itr = find(required.begin(), required.end(), id_);
            required.erase(itr);
            id = current;
        } else if (shared.compare(id_, "type")) {
            type = current;
        } else if (shared.compare(id_, "fs")) {
            fs = current;
        }
    }
    if (required.size() != 0) {
        shared.handler("MKFS", "requiere ciertos parámetros obligatorios");
        return;
    }
    mkfs(id, type, fs);
}

void FileSystem::mkfs(string id, string t, string fs) {
    try {

        if (!(shared.compare(t, "fast") || shared.compare(t, "full"))) {

            throw runtime_error("-type necesita valores específicos");
        } else if (!(shared.compare(fs, "2fs") || shared.compare(fs, "3fs"))) {

            throw runtime_error("-fs necesita valores específicos");
        }

        string p;
        Structs::Partition partition = mount.getmount(id, &p);

        int n = (shared.compare(fs, "2fs")) ? floor((partition.part_size - sizeof(Structs::Superblock)) /
                                                    (4 + sizeof(Structs::Inodes) + 3 * sizeof(Structs::Fileblock))) :
                floor((partition.part_size - sizeof(Structs::Superblock)) /
                      (4 + sizeof(Structs::Inodes) + 3 * sizeof(Structs::Fileblock) + sizeof(Structs::Journaling)));

        char datetime[20];

        time_t t = time(0);
        struct tm *tm = localtime(&t);
        strftime(datetime, 20, "%d/%m/%Y %H:%M:%S", tm);

        Structs::Superblock spr;
        spr.s_inodes_count = spr.s_free_inodes_count = n;
        spr.s_blocks_count = spr.s_free_blocks_count = 3 * n;
        strcpy(spr.s_mtime, datetime);
        strcpy(spr.s_umtime, datetime);
        spr.s_mnt_count = 1;
        if (shared.compare(fs, "2fs")) {
            spr.s_filesystem_type = 2;
            ext2(spr, partition, n, p);
        } else {
            spr.s_filesystem_type = 3;
        }

        shared.response("MKFS","formateo realizado con éxito");
    }
    catch (invalid_argument &e) {
        shared.handler("MKFS", "identificador de disco incorrecto, debe ser entero");
        return;
    }
    catch (exception &e) {
        shared.handler("MKFS", e.what());
        return;
    }
}

void FileSystem::ext2(Structs::Superblock spr, Structs::Partition p, int n, string path) {
    spr.s_bm_inode_start = p.part_start + sizeof(Structs::Superblock);
    spr.s_bm_block_start = spr.s_bm_inode_start + n;
    spr.s_inode_start = spr.s_bm_block_start + (3 * n);
    spr.s_block_start = spr.s_bm_inode_start + (n * sizeof(Structs::Inodes));

    FILE *bfile = fopen(path.c_str(), "rb+");
    fseek(bfile, p.part_start, SEEK_SET);
    fwrite(&spr, sizeof(Structs::Superblock), 1, bfile);

    char zero = '0';
    fseek(bfile, spr.s_bm_inode_start, SEEK_SET);
    for (int i = 0; i < n; i++) {
        fwrite(&zero, sizeof(zero), 1, bfile);
    }

    fseek(bfile, spr.s_bm_block_start, SEEK_SET);
    for (int i = 0; i < (3 * n); i++) {
        fwrite(&zero, sizeof(zero), 1, bfile);
    }

    Structs::Inodes inode;
    fseek(bfile, spr.s_bm_inode_start, SEEK_SET);
    for (int i = 0; i < n; i++) {
        fwrite(&inode, sizeof(Structs::Inodes), 1, bfile);
    }

    Structs::Folderblock folder;
    fseek(bfile, spr.s_bm_block_start, SEEK_SET);
    for (int i = 0; i < (3 * n); i++) {
        fwrite(&folder, sizeof(Structs::Folderblock), 1, bfile);
    }
    fclose(bfile);

    Structs::Superblock recuperado;
    FILE *archivo = fopen(path.c_str(), "rb");
    fseek(archivo, p.part_start, SEEK_SET);
    fread(&recuperado, sizeof(Structs::Superblock), 1, archivo);
    fclose(archivo);
    cout << endl;
    cout << "Tipo de sistema: " << recuperado.s_filesystem_type << endl;
    cout << "Numero de inodos: " << recuperado.s_inodes_count << endl;
    cout << "Numero de bloques: " << recuperado.s_blocks_count << endl;
    cout << "Fecha montado: " << recuperado.s_mtime << endl;
    cout << "inicio de los bloques " << recuperado.s_block_start << endl;
    cout << "inicio de los bloques " << n << endl;
    cout << endl;

    inode.i_uid = 1;
    inode.i_uid = 1;
    inode.i_size = 0;
    strcpy(inode.i_atime, spr.s_umtime);
    strcpy(inode.i_ctime, spr.s_umtime);
    strcpy(inode.i_mtime, spr.s_umtime);
    inode.i_type = '0';
    inode.i_perm = 664;
    inode.i_block[0] = 0;

    Structs::Folderblock fb;
    strcpy(fb.b_content[0].b_name, ".");
    strcpy(fb.b_content[1].b_name, "..");
    strcpy(fb.b_content[2].b_name, "user.txt");
    fb.b_content[2].b_inodo = 1;

    string data= "1,G,root\n1,U,root,root,123\n";
    Structs::Inodes inodetmp;
    inodetmp.i_uid = 1;
    inodetmp.i_uid = 1;
    inodetmp.i_size = 0;
    strcpy(inodetmp.i_atime, spr.s_umtime);
    strcpy(inodetmp.i_ctime, spr.s_umtime);
    strcpy(inodetmp.i_mtime, spr.s_umtime);
    inodetmp.i_type = sizeof(data.c_str());
    inodetmp.i_perm = 664;
    inodetmp.i_block[0] = 1;

    Structs::Fileblock fileb;
    strcpy(fileb.b_content, data.c_str());

    FILE *bfiles = fopen(path.c_str(), "rb+");
    fseek(bfiles, spr.s_bm_inode_start, SEEK_SET);
    char caracter = '1';
    fwrite(&caracter, sizeof(caracter), 1, bfiles);
    fwrite(&caracter, sizeof(caracter), 1, bfiles);
    fseek(bfiles, spr.s_bm_block_start, SEEK_SET);
    fwrite(&caracter, sizeof(caracter), 1, bfiles);
    fwrite(&caracter, sizeof(caracter), 1, bfiles);

    fseek(bfiles, spr.s_inode_start, SEEK_SET);
    fwrite(&inode, sizeof(Structs::Inodes), 1, bfiles);
    fwrite(&inodetmp, sizeof(Structs::Inodes), 1, bfiles);

    fseek(bfiles, spr.s_block_start, SEEK_SET);
    fwrite(&fb, sizeof(Structs::Folderblock), 1, bfiles);
    fwrite(&fileb, sizeof(Structs::Fileblock), 1, bfiles);
    fclose(bfiles);
}
