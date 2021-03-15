#include "../headers/report.h"

#include <iostream>
#include <stdlib.h>
#include "string"
#include <locale>

using namespace std;

Report::Report() {}

void Report::generate(vector<string> context, Mount m) {
    mount = m;
    vector<string> required = {"name", "path", "id"};
    string name;
    string path;
    string id;

    for (int i = 0; i < context.size(); i++) {
        string current = context.at(i);
        string id_ = current.substr(0, current.find("="));
        current.erase(0, id_.length() + 1);
        if (current.substr(0, 1) == "\"") {
            current = current.substr(1, current.length() - 2);
        }

        if (shared.compare(id_, "name")) {
            if (count(required.begin(), required.end(), id_)) {
                auto itr = find(required.begin(), required.end(), id_);
                required.erase(itr);
                name = current;
            }
        } else if (shared.compare(id_, "path")) {
            if (count(required.begin(), required.end(), id_)) {
                auto itr = find(required.begin(), required.end(), id_);
                required.erase(itr);
                path = current;
            }
        } else if (shared.compare(id_, "id")) {
            if (count(required.begin(), required.end(), id_)) {
                auto itr = find(required.begin(), required.end(), id_);
                required.erase(itr);
                id = current;
            }
        }
    }

    if (required.size() != 0) {
        shared.handler("REPORT", "requiere ciertos parámetros obligatorios");
        return;
    }
    if (shared.compare(name, "MBR")) {
        mbr(path, id);
    } else {
    }
}

void Report::mbr(string p, string id) {
    try {
        string path;
        Structs::Partition partition = mount.getmount(id, &path);

        FILE *file = fopen(path.c_str(), "rb+");
        if (file == NULL) {
            throw runtime_error("disco no existente");
        }

        Structs::MBR disk;
        rewind(file);
        fread(&disk, sizeof(Structs::MBR), 1, file);
        fclose(file);

        string pd = path.substr(0, path.find("."));
        pd += ".dot";
        FILE *doc = fopen(pd.c_str(), "r");
        if (doc == NULL) {
            string cmm = "mkdir -p \"" + pd + "\"";
            system(cmm.c_str());
            cmm = "rmdir \"" + pd + "\"";
            system(cmm.c_str());
        } else {
            fclose(doc);
        }

        string content;
        content = "digraph G{\n"
                  "rankdir=TB;\n"
                  "forcelabels= true;\n"
                  "node [shape = plaintext];\n"
                  "general [label = <table>\n"
                  "<tr><td COLSPAN = '2'>MBR</td></tr>\n"
                  "<tr><td>NOMBRE</td><td>VALOR</td></tr>\n"
                  "<tr>\n"
                  "<td>mbr_tamaño</td>\n"
                  "<td>" +
                  to_string(disk.mbr_tamano) + "</td>\n"
                                                "</tr>\n"
                                                "<tr>\n"
                                                "<td>mbr_fecha_creacion</td>\n"
                                                "<td>" +
                  string(disk.mbr_fecha_creacion) + "</td>\n"
                                                     "</tr>\n"
                                                     "<tr>\n"
                                                     "<td>mbr_disk_signature</td>\n"
                                                     "<td>" +
                  to_string(disk.mbr_disk_signature) + "</td>\n"
                                                        "</tr>\n"
                                                        "<tr>\n"
                                                        "<td>Disk_fit</td>\n"
                                                        "<td>" +
                  string(1, disk.disk_fit) + "</td>\n"
                                              "</tr>\n"
                                              "<tr>\n"
                                              "<td>part_status_1</td>\n"
                                              "<td>" +
                  string(1, disk.mbr_Partition_1.part_status) + "</td>\n"
                                                                 "</tr>\n"
                                                                 "<tr>\n"
                                                                 "<td>part_type_1</td>\n"
                                                                 "<td>" +
                  string(1, disk.mbr_Partition_1.part_type) + "</td>\n"
                                                               "</tr>\n"
                                                               "<tr>\n"
                                                               "<td>part_fit_1</td>\n"
                                                               "<td>" +
                  string(1, disk.mbr_Partition_1.part_fit) + "</td>\n"
                                                              "</tr>\n"
                                                              "<tr>\n"
                                                              "<td>part_start_1</td>\n"
                                                              "<td>" +
                  to_string(disk.mbr_Partition_1.part_start) + "</td>\n"
                                                                "</tr>\n"
                                                                "<tr>\n"
                                                                "<td>part_size_1</td>\n"
                                                                "<td>" +
                  to_string(disk.mbr_Partition_1.part_size) + "</td>\n"
                                                               "</tr>\n"
                                                               "<tr>\n"
                                                               "<td>part_name_1</td>\n"
                                                               "<td>" +
                  string(disk.mbr_Partition_1.part_name) + "</td>\n"
                                                            "</tr>\n"
                                                            "<tr>\n"
                                                            "<td>part_status_2</td>\n"
                                                            "<td>" +
                  string(1, disk.mbr_Partition_2.part_status) + "</td>\n"
                                                                 "</tr>\n"
                                                                 "<tr>\n"
                                                                 "<td>part_type_2</td>\n"
                                                                 "<td>" +
                  string(1, disk.mbr_Partition_2.part_type) + "</td>\n"
                                                               "</tr>\n"
                                                               "<tr>\n"
                                                               "<td>part_fit_2</td>\n"
                                                               "<td>" +
                  string(1, disk.mbr_Partition_2.part_fit) + "</td>\n"
                                                              "</tr>\n"
                                                              "<tr>\n"
                                                              "<td>part_start_2</td>\n"
                                                              "<td>" +
                  to_string(disk.mbr_Partition_2.part_start) + "</td>\n"
                                                                "</tr>\n"
                                                                "<tr>\n"
                                                                "<td>part_size_2</td>\n"
                                                                "<td>" +
                  to_string(disk.mbr_Partition_2.part_size) + "</td>\n"
                                                               "</tr>\n"
                                                               "<tr>\n"
                                                               "<td>part_name_2</td>\n"
                                                               "<td>" +
                  string(disk.mbr_Partition_2.part_name) + "</td>\n"
                                                            "</tr>\n"
                                                            "<tr>\n"
                                                            "<td>part_status_3</td>\n"
                                                            "<td>" +
                  string(1, disk.mbr_Partition_3.part_status) + "</td>\n"
                                                                 "</tr>\n"
                                                                 "<tr>\n"
                                                                 "<td>part_type_3</td>\n"
                                                                 "<td>" +
                  string(1, disk.mbr_Partition_3.part_type) + "</td>\n"
                                                               "</tr>\n"
                                                               "<tr>\n"
                                                               "<td>part_fit_3</td>\n"
                                                               "<td>" +
                  string(1, disk.mbr_Partition_3.part_fit) + "</td>\n"
                                                              "</tr>\n"
                                                              "<tr>\n"
                                                              "<td>part_start_3</td>\n"
                                                              "<td>" +
                  to_string(disk.mbr_Partition_3.part_start) + "</td>\n"
                                                                "</tr>\n"
                                                                "<tr>\n"
                                                                "<td>part_size_3</td>\n"
                                                                "<td>" +
                  to_string(disk.mbr_Partition_3.part_size) + "</td>\n"
                                                               "</tr>\n"
                                                               "<tr>\n"
                                                               "<td>part_name_3</td>\n"
                                                               "<td>" +
                  string(disk.mbr_Partition_3.part_name) + "</td>\n"
                                                            "</tr>\n"
                                                            "<tr>\n"
                                                            "<td>part_status_4</td>\n"
                                                            "<td>" +
                  string(1, disk.mbr_Partition_4.part_status) + "</td>\n"
                                                                 "</tr>\n"
                                                                 "<tr>\n"
                                                                 "<td>part_type_4</td>\n"
                                                                 "<td>" +
                  string(1, disk.mbr_Partition_4.part_type) + "</td>\n"
                                                               "</tr>\n"
                                                               "<tr>\n"
                                                               "<td>part_fit_4</td>\n"
                                                               "<td>" +
                  string(1, disk.mbr_Partition_4.part_fit) + "</td>\n"
                                                              "</tr>\n"
                                                              "<tr>\n"
                                                              "<td>part_start_4</td>\n"
                                                              "<td>" +
                  to_string(disk.mbr_Partition_4.part_start) + "</td>\n"
                                                                "</tr>\n"
                                                                "<tr>\n"
                                                                "<td>part_size_4</td>\n"
                                                                "<td>" +
                  to_string(disk.mbr_Partition_4.part_size) + "</td>\n"
                                                               "</tr>\n"
                                                               "<tr>\n"
                                                               "<td>part_name_4</td>\n"
                                                               "<td>" +
                  string(disk.mbr_Partition_4.part_name) + "</td>\n"
                                                            "</tr>\n"
                                                            "</table>>];\n";;
    } catch (exception &e) {
        shared.handler("REPORT", e.what());
    }
}
