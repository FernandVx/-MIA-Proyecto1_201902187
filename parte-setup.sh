#!/bin/sh -
LAST=${1:-62}
UR=${2:-root}
sed -i 's/62\([0-9]a\)/'$LAST'\1/g' parte1.sh
sed -i 's/62\([0-9]a\)/'$LAST'\1/g' parte2.sh
sed -i 's/62\([0-9]a\)/'$LAST'\1/g' parte-montar-particiones.script
sed -i 's/62\([0-9]a\)/'$LAST'\1/g' parte-editar-particiones.script
sed -i 's/62\([0-9]a\)/'$LAST'\1/g' parte-eliminar-particiones.script
sed -i 's/62\([0-9]a\)/'$LAST'\1/g' parte-reportes-mbr.script
cp ./parte* /tmp
mkdir -p /home/parte1/particiones
mkdir -p /home/parte2/inicial
mkdir -p /home/parte2/mkdir_ind
mkdir -p /home/parte2/mkfile_ind
mkdir -p /home/parte2/rem
mkdir -p /home/parte2/mover
chown -R "$UR:$UR" /home/parte1
chown -R "$UR:$UR" /home/parte2
chown "$UR:$UR" /tmp/parte*
