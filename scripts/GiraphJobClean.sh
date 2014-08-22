#!/bin/bash
for host in `cat hosts`
do
   echo "ssh $host /mnt/disk1/simon0227/simon/GiraphTaskClean.sh $1"
   ssh $host /mnt/disk1/simon0227/simon/GiraphTaskClean.sh $1
   echo ""
done
