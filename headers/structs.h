#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

using namespace std;

class Structs
{
public:
    Structs();
    typedef struct _Partition
    {
        char part_status;
        char part_type;
        char part_fit;
        int part_start;
        int part_size;
        char part_name[16];
    } Partition;

    typedef struct _MBR
    {
        int mbr_tamano;
        char mbr_fecha_creacion[20]; //pendiente
        int mbr_disk_signature;
        char disk_fit;
        Partition mbr_Partition_1;
        Partition mbr_Partition_2;
        Partition mbr_Partition_3;
        Partition mbr_Partition_4;
    } MBR;

    typedef struct _EBR
    {
        char part_status;
        char part_fit;
        int part_start;
        int part_size;
        int part_next;
        char part_name[16];
    } EBR;
};

#endif // END OF DECLARATION
