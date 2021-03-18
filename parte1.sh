#Calificacion MIA 2021 - Parte 1

#CREACION DE DISCOS

mkdisk -size=75 -u=M -path=/tmp/d1.dk               #disco con primer ajuste
mkdisk -u=K -path=/tmp/d2.dk -f=BF -size=10240      #tamaño de 10mb
mkdisk -size=101 -path=/tmp/d3.dk -f=WF             #debe crear disco en MB
mkdisk -size=1 -path="/tmp/eliminar 1.dk"
mkdisk -size=1 -path="/tmp/eliminar 2.dk"

#ELIMINACION DE DISCOS

rmdisk -path="/home/a eliminar disco/no_existo.dk"                #debe de mostrar error por no existir
rmdisk -path="/tmp/eliminar 1.dk"                                 #verificar mensaje de eliminacion darle si
rmdisk -path="/tmp/eliminar 2.dk"                                 #verificar mensaje de eliminacion darle si

#CREACION DE PARTICIONES PRIMARIAS Y EXTENDIDAS

#Crear particiones d1.dk
fdisk -type=P -u=M -name=Part1 -size=25 -path=/tmp/d1.dk
fdisk -type=P -u=M -name=Part2 -size=25 -path=/tmp/d1.dk
fdisk -type=P -u=M -name=Part3 -size=25 -path=/tmp/d1.dk

#Crear particiones d2.dk
fdisk -type=L -u=M -name=Part6 -size=25 -path=/tmp/d2.dk  #error, no existe extendida
fdisk -type=E -u=M -name=Part1 -size=9 -path=/tmp/d2.dk  -f=FF    #ocupa los 10MB del disco
fdisk -type=E -u=M -name=Part7 -size=25 -path=/tmp/d2.dk  -f=WF    #error, ya existe una extendida
fdisk -type=L -u=B -name=Part2 -size=1024 -path=/tmp/d2.dk 
fdisk -type=L -u=B -name=Part3 -size=1024 -path=/tmp/d2.dk
fdisk -type=L -u=B -name=Part4 -size=1024 -path=/tmp/d2.dk

#Crear particiones d3.dk
fdisk -type=E -u=M -name=Part1 -size=25 -path=/tmp/d3.dk  -f=BF
fdisk -type=P -u=M -name=Part2 -size=25 -path=/tmp/d3.dk  -f=BF
fdisk -type=P -u=M -name=Part3 -size=25 -path=/tmp/d3.dk  -f=BF
fdisk -type=P -u=M -name=Part4 -size=25 -path=/tmp/d3.dk  -f=BF
fdisk -type=P -u=M -name=Part1 -size=25 -path=/tmp/d3.dk  -f=BF #error, ya existen 4 particiones
fdisk -type=L -u=K -name=Part5 -size=1024 -path=/tmp/d3.dk  -f=BF
fdisk -type=L -u=K -name=Part6 -size=1024 -path=/tmp/d3.dk  -f=BF

#MOUNT CARNET DE EJEMPLO 201709362
mount -path=/tmp/d1.dk -name=Part1 #621a
mount -path=/tmp/d2.dk -name=Part1 #622a
mount -path=/tmp/d3.dk -name=Part1 #623a

########reporte disk del estado inicial de las particiones
rep -id=621a -Path=/home/parte1/particiones/d1.jpg -name=disk
rep -id=622a -Path=/home/parte1/particiones/d2.jpg -name=disk
rep -id=623a -Path=/home/parte1/particiones/d3.jpg -name=disk

pause

#ELIMINACION DE PARTICIONES PRIMARIAS
fdisk -delete=full -name=Part2 -path=/tmp/d1.dk

#ELIMINACION DE PARTICIONES EXTENDIDAS
fdisk -delete=fast -name=Part1 -path=/tmp/d3.dk

#ELIMINACION DE PARTICIONES LOGICAS
fdisk -delete=full -name=Part3 -path=/tmp/d2.dk

#reporte disk despues de eliminar
rep -id=621a -Path=/home/parte1/particiones/d1.jpg -name=disk
rep -id=622a -Path=/home/parte1/particiones/d2.jpg -name=disk
rep -id=623a -Path=/home/parte1/particiones/d3.jpg -name=disk

pause

#CAMBIO DE TAMAÑO  DE PARTICIONES
fdisk -add=-30 -unit=m -name=Part1 -path=/tmp/d1.dk #error, solo tiene 25mb de size
fdisk -add=45 -unit=m -name=Part3 -path=/tmp/d1.dk #error, no hay espacio 
fdisk -add=-20 -unit=m -name=Part1 -path=/tmp/d1.dk
fdisk -add=45 -unit=m -name=Part3 -path=/tmp/d1.dk 

#reporte disk despues de cambiar tamaños
rep -id=621a -Path=/home/parte1/particiones/d1.jpg -name=disk
rep -id=622a -Path=/home/parte1/particiones/d2.jpg -name=disk
rep -id=623a -Path=/home/parte1/particiones/d3.jpg -name=disk

pause

#REPORTES MBR
rep -id=621a -Path=/home/parte1/mbr1.jpg -name=mbr
rep -id=622a -Path=/home/parte1/mbr2.jpg -name=mbr
rep -id=623a -Path=/home/parte1/mbr3.jpg -name=mbr

#UNMOUNT
unmount -id=621a

rep -id=621a -Path=/home/parte1/mbr3.jpg -name=mbr #debe dar error porque ya no esta montada la particion

#cerrar el programa para validar
pause
rep -id=622a -Path=/home/parte1/mbr3.jpg -name=mbr #debe dar error porque no deberia estar montado nada
