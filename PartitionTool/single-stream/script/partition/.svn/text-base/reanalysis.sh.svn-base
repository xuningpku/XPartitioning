#!/bin/bash
dir="partition/LJ/vertexbalance"
for file in `ls $dir`; 
do 
	suffix=${file:(-4)}; 
	if [ $suffix = "part" ]; then 
	#	echo $suffix; 
		echo $file
#		expr index $file "1030"
		sig=$(echo `expr substr "$file" 32 4`)
		echo $sig
		if [ $sig = "1030" ]; then
			./gknifedemo -p 26 -g /home/hadoop/simon/dataset/LJ/soc-LiveJournal.undir.elist -pm $dir/$file -hp true -m hash -c config/heter_config_26_11_1030 > $file.26_11_1030
		else
			./gknifedemo -p 26 -g /home/hadoop/simon/dataset/LJ/soc-LiveJournal.undir.elist -pm $dir/$file -hp true -m hash -c config/heter_config_26_11_100300 > $file.26_11_100300
		fi
		echo ;
	fi; 
done
