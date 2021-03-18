#CONFIGURACION INICIAL
mkdisk -size=112 -u=M -path=/home/parte2/disco.dk
fdisk -type=P -u=M -name=Part1 -size=25 -path=/home/parte2/disco.dk  
fdisk -type=P -u=M -name=Part2 -size=25 -path=/home/parte2/disco.dk
fdisk -type=P -u=M -name=Part3 -size=25 -path=/home/parte2/disco.dk
fdisk -type=P -u=M -name=Part4 -size=25 -path=/home/parte2/disco.dk
mount -path=/home/parte2/disco.dk   -name=Part1
mount -path=/home/parte2/disco.dk   -name=Part2
mount -path=/home/parte2/disco.dk   -name=Part3
mount -path=/home/parte2/disco.dk   -name=Part4

#MKFS A PARTICIONES
mkfs -type=fast -id=621a
mkfs -type=full -id=621c -fs=3fs

#REPORTES INICIALES
rep -id=621a -Path="/home/parte2/inicial/ext2_sb_1.pdf" -name=sb
rep -id=621a -Path="/home/parte2/inicial/ext2_tree_1.pdf" -name=tree

rep -id=621c -Path="/home/parte2/inicial/ext3_sb_1.pdf" -name=sb
rep -id=621c -Path="/home/parte2/inicial/ext3_tree_1.pdf" -name=tree
