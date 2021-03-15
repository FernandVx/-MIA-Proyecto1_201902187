cmake_minimum_required(VERSION 3.17)
project(_MIA_Proyecto1_201902187)

set(CMAKE_CXX_STANDARD 14)

include_directories(headers)

add_executable(_MIA_Proyecto1_201902187
        funcionality/analysis.cpp
        funcionality/disk.cpp
        funcionality/filesystem.cpp
        funcionality/mount.cpp
        funcionality/shared.cpp
        headers/analysis.h
        headers/disk.h
        headers/filesystem.h
        headers/mount.h
        headers/shared.h
        headers/structs.h
        main.cpp headers/admin.h funcionality/admin.cpp)
