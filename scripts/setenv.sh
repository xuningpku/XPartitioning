#!/bin/bash
./enablehadoop.sh
sudo cp -r env-pack /home/hadoop/
sudo chmod 777 /home/hadoop/env-pack/stop.sh
ssh hadoop@localhost "cd env-pack; ./stop.sh $@"
sudo rm -r /home/hadoop/env-pack 
./disablehadoop.sh
