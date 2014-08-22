#!/bin/bash
sudo cp /home/hadoop/.ssh/authorized_keys /home/hadoop/.ssh/.authorized_keys.backup
sudo cp /home/hadoop/.ssh/authorized_keys .
sudo chmod 777 authorized_keys
sudo cat id_rsa.pub.old >> authorized_keys
sudo mv authorized_keys /home/hadoop/.ssh/
sudo chmod 755 /home/hadoop/.ssh/authorized_keys
