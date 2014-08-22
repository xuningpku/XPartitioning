#!/bin/bash
prefix=$1
dir=$2
for file in `ls $dir`; 
do 
	suffix=${file:(-4)}; 
	if [ $suffix = "part" ]; then 
	#	echo $suffix; 
		echo $file
#		expr index $file "1030"
#		sig=$(echo `expr substr "$file" 32 4`)
		tmp_config=${file#$prefix};
	#	echo $tmp_config;
		config=${tmp_config%.eb*}
		echo $config
	#	echo $sig
	#	if [ $sig = "1030" ]; then
			echo "./gknifedemo -p 26 -g /home/hadoop/simon/dataset/LJ/soc-LiveJournal.undir.elist.rand -pm $dir/$file -hp true -m hash -c config/$config > $file.reanalysis"
	#	else
	#		./gknifedemo -p 26 -g /home/hadoop/simon/dataset/LJ/soc-LiveJournal.undir.elist -pm $dir/$file -hp true -m hash -c config/heter_config_26_11_100300 > $file.26_11_100300
	#	fi
	#	echo ;
	fi; 
done
