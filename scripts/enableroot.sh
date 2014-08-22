#!/bin/bash
sudo cp /root/.ssh/authorized_keys /root/.ssh/.authorized_keys.backup
sudo cp /root/.ssh/authorized_keys .
sudo chmod 777 authorized_keys
sudo cat id_rsa.pub.old >> authorized_keys
sudo mv authorized_keys /root/.ssh/
sudo chmod 755 /root/.ssh/authorized_keys
