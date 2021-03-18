#-----------------
# Parte 2 - SISTEMA DE ARCHIVOS
#----------------

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

#INICIO DE SESION

Login -pwd=567 -usr=roca -id=621a  #Debe dar error porque no existe el usuario roca
logout #debe dar error porque no existe nada activo

Login -pwd=123 -usr=root -id=621a

pause

#CREACION DE GRUPOS
mkgrp -naMe=Archivos
mkgrp -NamE=Arqui
mkgrp -name="Orga"

Cat -file=/users.txt            #validar cambios en el archivo


#ELIMINACION DE GRUPOS
rmgrp -name=Arqui

Cat -file=/users.txt            #validar cambios en el archivo

#CREACION DE USUARIOS
Mkusr -usr="user1" -grp=root -pwd=user1
Mkusr -usr="user2" -grp="Compi 2" -pwd=user2
Mkusr -usr="user3" -grp="Compi 2" -pwd=user3
Mkusr -usr="user4" -grp="Compi 2" -pwd=user4

Cat -file=/users.txt             #validar cambios en el archivo

#ELIMINACION DE USUARIOS
rmusr -usr=user3

Cat -file=/users.txt             #validar cambios en el archivo

#CAMBIAR USUARIO DE GRUPO
chgrp -usr=user4 -grp=Archivos

Cat -file=/users.txt             #validar cambios en el archivo

pause

#CREACION DE CARPETAS
Mkdir -P  -path=/home/archivos/mia/fase2
Mkdir -P  -path=/home/archivos/mia/carpeta2
Mkdir -P  -path=/home/archivos/mia/z
Mkdir -P  -path=/home/archivos/mia/carpeta3/carpeta7/carpeta8/carpeta9/carpeta10/carpeta11
Mkdir -P  -path=/home/archivos/mia/carpeta4/carpeta7/carpeta8/carpeta9/carpeta10/carpeta11/carpeta7/carpeta8/carpeta9/carpeta10/carpeta11
Mkdir  -path=/home/archivos/mia/carpeta2/a1
Mkdir  -path=/home/archivos/mia/carpeta2/a2
Mkdir  -path=/home/archivos/mia/carpeta2/a3
Mkdir  -path=/home/archivos/mia/carpeta2/a4
Mkdir  -path=/home/archivos/mia/carpeta2/a5
Mkdir  -path=/home/archivos/mia/carpeta2/a6
Mkdir  -path=/home/archivos/mia/carpeta2/a7
Mkdir  -path=/home/archivos/mia/carpeta2/a8
Mkdir  -path=/home/archivos/mia/carpeta2/a9
Mkdir  -path=/home/archivos/mia/carpeta2/a10
Mkdir  -path=/home/archivos/mia/fase2/a1
Mkdir  -path=/home/archivos/mia/fase2/a2
Mkdir  -path=/home/archivos/mia/fase2/a3
Mkdir  -path=/home/archivos/mia/fase2/a4
Mkdir  -path=/home/archivos/mia/fase2/a5
Mkdir  -path=/home/archivos/mia/fase2/a6
Mkdir  -path=/home/archivos/mia/fase2/a7
Mkdir  -path=/home/archivos/mia/fase2/a8
Mkdir  -path=/home/archivos/mia/fase2/a9
Mkdir  -path=/home/archivos/mia/fase2/a10
Mkdir  -path=/home/archivos/mia/fase2/a11
Mkdir  -path=/home/archivos/mia/fase2/a12
Mkdir  -path=/home/archivos/mia/fase2/a13
Mkdir  -path=/home/archivos/mia/fase2/a14
Mkdir  -path=/home/archivos/mia/fase2/a15
Mkdir  -path=/home/archivos/mia/fase2/a16
Mkdir  -path=/home/archivos/mia/fase2/a17
Mkdir  -path=/home/archivos/mia/fase2/a18
Mkdir  -path=/home/archivos/mia/fase2/a19
Mkdir  -path=/home/archivos/mia/fase2/a20
Mkdir  -path=/home/archivos/mia/fase2/a21
Mkdir  -path=/home/archivos/mia/fase2/a22
Mkdir  -path=/home/archivos/mia/fase2/a23
Mkdir  -path=/home/archivos/mia/fase2/a24
Mkdir  -path=/home/archivos/mia/fase2/a25
Mkdir  -path=/home/archivos/mia/fase2/a26
Mkdir  -path=/home/archivos/mia/fase2/a27
Mkdir  -path=/home/archivos/mia/fase2/a28
Mkdir  -path=/home/archivos/mia/fase2/a29
Mkdir  -path=/home/archivos/mia/fase2/a30
Mkdir  -path=/home/archivos/mia/fase2/a31
Mkdir  -path=/home/archivos/mia/fase2/a32
Mkdir  -path=/home/archivos/mia/fase2/a33
Mkdir  -path=/home/archivos/mia/fase2/a34
Mkdir  -path=/home/archivos/mia/fase2/a35
Mkdir  -path=/home/archivos/mia/fase2/a36
Mkdir  -path=/home/archivos/mia/fase2/a37
Mkdir  -path=/home/archivos/mia/fase2/a38
Mkdir  -path=/home/archivos/mia/fase2/a39
Mkdir  -path=/home/archivos/mia/fase2/a40
Mkdir  -path=/home/archivos/mia/fase2/a41
Mkdir  -path=/home/archivos/mia/fase2/a42
Mkdir  -path=/home/archivos/mia/fase2/a43
Mkdir  -path=/home/archivos/mia/fase2/a44
Mkdir  -path=/home/archivos/mia/fase2/a45
Mkdir  -path=/home/archivos/mia/fase2/a46
#Debe dar error porque ya existe a46
Mkdir  -path=/home/archivos/mia/fase2/a46

#Primer indirecto
mkdir  -path="/home/archivos/mia/fase2/b1"
mkdir  -path="/home/archivos/mia/fase2/b2"
mkdir  -path="/home/archivos/mia/fase2/b3"
mkdir  -path="/home/archivos/mia/fase2/b4"
mkdir  -path="/home/archivos/mia/fase2/b5"
mkdir  -path="/home/archivos/mia/fase2/b6"
mkdir  -path="/home/archivos/mia/fase2/b7"
mkdir  -path="/home/archivos/mia/fase2/b8"
mkdir  -path="/home/archivos/mia/fase2/b9"
mkdir  -path="/home/archivos/mia/fase2/b10"
mkdir  -path="/home/archivos/mia/fase2/b11"
mkdir  -path="/home/archivos/mia/fase2/b12"
mkdir  -path="/home/archivos/mia/fase2/b13"
mkdir  -path="/home/archivos/mia/fase2/b14"
mkdir  -path="/home/archivos/mia/fase2/b15"
mkdir  -path="/home/archivos/mia/fase2/b16"
mkdir  -path="/home/archivos/mia/fase2/b17"
mkdir  -path="/home/archivos/mia/fase2/b18"
mkdir  -path="/home/archivos/mia/fase2/b19"
mkdir  -path="/home/archivos/mia/fase2/b20"
mkdir  -path="/home/archivos/mia/fase2/b21"
mkdir  -path="/home/archivos/mia/fase2/b22"
mkdir  -path="/home/archivos/mia/fase2/b23"
mkdir  -path="/home/archivos/mia/fase2/b24"
mkdir  -path="/home/archivos/mia/fase2/b25"
mkdir  -path="/home/archivos/mia/fase2/b26"
mkdir  -path="/home/archivos/mia/fase2/b27"
mkdir  -path="/home/archivos/mia/fase2/b28"
mkdir  -path="/home/archivos/mia/fase2/b29"
mkdir  -path="/home/archivos/mia/fase2/b30"
mkdir  -path="/home/archivos/mia/fase2/b31"
mkdir  -path="/home/archivos/mia/fase2/b32"
mkdir  -path="/home/archivos/mia/fase2/b33"
mkdir  -path="/home/archivos/mia/fase2/b34"
mkdir  -path="/home/archivos/mia/fase2/b35"
mkdir  -path="/home/archivos/mia/fase2/b36"
mkdir  -path="/home/archivos/mia/fase2/b37"
mkdir  -path="/home/archivos/mia/fase2/b38"
mkdir  -path="/home/archivos/mia/fase2/b39"
mkdir  -path="/home/archivos/mia/fase2/b40"
mkdir  -path="/home/archivos/mia/fase2/b41"
mkdir  -path="/home/archivos/mia/fase2/b42"
mkdir  -path="/home/archivos/mia/fase2/b43"
mkdir  -path="/home/archivos/mia/fase2/b44"
mkdir  -path="/home/archivos/mia/fase2/b45"
mkdir  -path="/home/archivos/mia/fase2/b46"
mkdir  -path="/home/archivos/mia/fase2/b47"
mkdir  -path="/home/archivos/mia/fase2/b48"
mkdir  -path="/home/archivos/mia/fase2/b49"
mkdir  -path="/home/archivos/mia/fase2/b50"

pause

#REPORTES PARA VERIFICAR INDIRECTOS
rep -id=621a -Path="/home/parte2/mkdir_ind/ext2_sb_1.pdf" -name=sb
rep -id=621a -Path="/home/parte2/mkdir_ind/ext2_tree_1.pdf" -name=tree
#CREACION DE ARCHIVOS
logout
loGin -usr=user1 -pwd=user1 -id=621a  #cambiamos de usuario para despues validar chown y chmod
#Archivo 
mkfile -path="/home/b1.txt" -size=75
#Debe dar error ruta no existe
mkfile -path="/home/Noexiste/b1.txt" -size=75
#Debe dar error size negativo
mkfile -path="/home/b1.txt" -size=-45
#indirectos
mkfile -path="/home/b1_1.txt" -size=10000
#archivo con archivo de la pc
mkfile -cont="/home/entrada.txt" -path="/home/bcont.txt"

#REPORTES PARA VERIFICAR INDIRECTOS
rep -id=621a -Path="/home/parte2/mkfile_ind/ext2_sb_1.pdf" -name=sb
rep -id=621a -Path="/home/parte2/mkfile_ind/ext2_tree_1.pdf" -name=tree

pause

#ELIMINACION DE CONTENIDO
#Carpeta Directos
rem -path=/home/archivos/mia/fase2/a46
#Carpeta indirectos
rem -path="/home/archivos/mia/fase2/b1"

#REPORTES PARA VERIFICAR CAMBIOS
rep -id=621a -Path="/home/parte2/rem/ext2_sb_1.pdf" -name=sb
rep -id=621a -Path="/home/parte2/rem/ext2_tree_1.pdf" -name=tree

pause

#MOVER CONTENIDO
mv -path="/home/archivos/mia/fase2/b50" -dest="/home"

#REPORTES PARA VERIFICAR CAMBIOS
rep -id=621a -Path="/home/parte2/mover/ext2_sb_1.pdf" -name=sb
rep -id=621a -Path="/home/parte2/mover/ext2_tree_1.pdf" -name=tree

pause

#REPORTES ANTES DE LA PERDIDA
#Ultimo reporte antes de la perdida
rep -id=621a -Path="/home/archivos/antes_perdida/users.txt" -ruta="/users.txt" -name=file
rep -id=621a -Path="/home/archivos/antes_perdida/ls.pdf" -ruta="/" -name=ls
rep -id=621a -Path="/home/archivos/antes_perdida/reporte5_621a_sb.pdf" -name=sb
rep -id=621a -Path="/home/archivos/antes_perdida/reporte5_621a_tree.jpg" -name=tree
rep -id=621a -Path="/home/archivos/antes_perdida/reporte5_621a_inode.pdf" -name=inode
rep -id=621a -Path="/home/archivos/antes_perdida/reporte5_621a_block.pdf" -name=block
rep -id=621a -Path="/home/archivos/antes_perdida/reporte5_621a_bm_inode.pdf" -name=bm_inode
rep -id=621a -Path="/home/archivos/antes_perdida/reporte5_621a_bm_block.pdf" -name=bm_block
rep -id=621a -Path="/home/archivos/antes_perdida/reporte5_621a_journaling.pdf" -name=journaling

pause

#PERDIDA
Loss -id=621a


rep -id=621a -Path="/home/archivos/despues_perdida/reporte6_621a_sb.pdf" -name=sb
rep -id=621a -Path="/home/archivos/despues_perdida/reporte6_621a_tree.jpg" -name=tree
rep -id=621a -Path="/home/archivos/despues_perdida/reporte6_621a_inode.pdf" -name=inode
rep -id=621a -Path="/home/archivos/despues_perdida/reporte6_621a_block.pdf" -name=block
rep -id=621a -Path="/home/archivos/despues_perdida/reporte6_621a_bm_inode.pdf" -name=bm_inode
rep -id=621a -Path="/home/archivos/despues_perdida/reporte6_621a_bm_block.pdf" -name=bm_block
rep -id=621a -Path="/home/archivos/despues_perdida/reporte6_621a_journaling.pdf" -name=journaling

pause

#Recovery
Recovery -id=621a

rep -id=621a -Path="/home/archivos/recuperacion/reporte7_621a_sb.pdf" -name=sb
rep -id=621a -Path="/home/archivos/recuperacion/reporte7_621a_tree.jpg" -name=tree
rep -id=621a -Path="/home/archivos/recuperacion/reporte7_621a_inode.pdf" -name=inode
rep -id=621a -Path="/home/archivos/recuperacion/reporte7_621a_block.pdf" -name=block
rep -id=621a -Path="/home/archivos/recuperacion/reporte7_621a_bm_inode.pdf" -name=bm_inode
rep -id=621a -Path="/home/archivos/recuperacion/reporte7_621a_bm_block.pdf" -name=bm_block
rep -id=621a -Path="/home/archivos/reporecuperacionrts2/reporte7_621a_journaling.pdf" -name=journaling
pause

logout
Login -pwd=123 -usr=root -id=621a

#Chmod
chmod -path=/home/archivos/mia/carpeta2 -ugo=001 -R
chmod -path="/home/b1.txt" -ugo=001
logout
loGin -usr=user1 -pwd=user1 -id=621a
#No debe dejar por permisos de escritura
Mkdir -P  -path=/home/archivos/mia/carpeta2/Esta/no/se/debe/crear/por/permisos
#No debe dejar por permisos de lectura
cat -file1="/home/b1.txt"
logout
pause

#Renombrar
Login -pwd=123 -usr=root -id=621a
ren -path=/home/archivos/mia/fase1 -name=fase1renombre
ren -path="/home/archivos/mia/fase2/b1" -name=renindirecto
logout
loGin -usr=user1 -pwd=user1 -id=621a
#Este debe fallar por permisos de escritura
ren -path="/home/b1.txt" -name=brenombre.txt
logoUt
#Pausa para el renombrar
pause

Login -pwd=123 -usr=root -id=621a

#Indirectos dobles
mkfile -path="/home/b2ble.txt" -size=18000
#Indirectos triples
mkfile -path="/home/b3ple.txt" -size=280000
#Reporte 8
rep -id=621a -Path="/home/archivos/reports2/reporte8_621a_tree.jpg" -name=tree
pause 

#Copiar
#Debe dar error porque destino no existe
cp -path=/home/archivos/mia/carpeta3 -dest=/home/archivos/mia/yo/no/existo
cp -path=/home/archivos/mia/carpeta3 -dest=/home/archivos/mia/carpeta2
#Copiar indirectos
cp -path=/home/archivos/mia/fase2 -dest=/home/archivos/mia/carpeta2
#Reporte 9
rep -id=621a -Path="/home/archivos/reports2/reporte9_621a_tree.jpg" -name=tree
pause 

#FIND
find -Path="/" -name=*
pause
find -Path="/" -name="?.*"
#Debe dar error porque no exxiste path
find -Path="/no/existo" -name=?
pause

#EDIT
edit -path="/home/b3ple.txt" -size=50
edit -path="/home/b2ble.txt" -size=280000
#Reporte 10
rep -id=621a -Path="/home/archivos/reports2/reporte10_621a_tree.jpg" -name=tree

#CHGRP
chgrp -usr=user1 -grp="Compi 2"
rep -id=621a -Path="/home/archivos/reports2/usersCHGRP.txt" -ruta="/users.txt" -name=file
logout
loGin -usr=user1 -pwd=user1 -id=621a
#Debe marcar error porque no es root
chgrp -usr=user1 -grp=Archivos
logout
pause

#CHOWN
Login -pwd=123 -usr=root -id=621a
chown -path="/home/archivos/mia/fase2" -usr=user -R
rep -id=621a -Path="/home/archivos/reports2/lsCHOWN.pdf" -ruta="/home/archivos/mia/fase2" -name=ls
pause

chmod -path=/ -ugo=000 -R
rep -id=621a -Path="/home/archivos/reports2/lsULTIMO.pdf" -ruta="/" -name=ls
pause
