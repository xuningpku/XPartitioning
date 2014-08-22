#!/bin/bash
./enablehadoop.sh
sudo cp -r clean-pack /home/hadoop/
sudo chmod 777 /home/hadoop/clean-pack/* 
ssh hadoop@localhost "cd clean-pack; ./GiraphJobClean.sh $@"
sudo rm -r /home/hadoop/clean-pack 
./disablehadoop.sh
