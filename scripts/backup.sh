#!/bin/bash
# move simon directly
for host in `cat hosts`
do
     echo processing $host
     ssh $host "if [ -L /home/hadoop/simon ]; then echo link;
                 elif [ -d /home/hadoop/simon ]; then
                      echo directory;
                      chown -R simon0227 /home/hadoop/simon
                 fi"
done
