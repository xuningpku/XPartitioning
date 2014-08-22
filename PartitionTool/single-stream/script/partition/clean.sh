#!/bin/bash

dir=$1

for file in `ls $dir`
do
	suffix=${file##*.}
#	echo $suffix
    suffix=$suffix
	if [ $suffix = "reanalysis" ]; then
		ebf=0;
		maxio=0
		maxcpu=0
		ecr=0
		totio=0
		mixcost=0
		while read line
		do
			#echo $line
			#process ecr
			idx=$(echo `expr match "$line"  '.*EdgeCuts.*'`)
			#echo $idx
			if [ $idx -gt 0 ]; then
				ecr=${line##*=}
				continue;
			fi

			#process ebf
			idx=$(echo `expr match "$line" '.*Edge_BF.*'`)
			#echo $idx
			if [ $idx -gt 0 ]; then
				tmp=${line##*Edge_BF=}
				ebf=${tmp%,*}
				continue;
			fi
			#process totio
			idx=$(echo `expr match "$line" '.*TotalMinIoCost.*'`)
			#echo $idx
			if [ $idx -gt 0 ]; then
				tmp=${line##*TotalMinIoCost=}
				totio=${tmp%[*}
				continue;
			fi
			#process mixcost
			idx=$(echo `expr match "$line" '.*MaxEdgeTotalMixCost.*'`)
			#echo $idx
			if [ $idx -gt 0 ]; then
				mixcost=${line##*MixCost=}
				continue;
			fi
			#maxcpu
			idx=$(echo `expr match "$line" '.*MaxEdgeCpuCost.*'`)
			#echo $idx
			if [ $idx -gt 0 ]; then
				maxcpu=${line##*MaxEdgeCpuCost=}
				continue;
			fi
			
			#maxio
			idx=$(echo `expr match "$line" '.*MaxIoCost.*'`)
			#echo $idx
			if [ $idx -gt 0 ]; then
				tmp=${line##*MaxIoCost =}
				maxio=${tmp%%, *}
				continue;
			fi
		done < <(cat $dir/$file)
		echo $file $ebf $ecr $maxio $maxcpu $totio $mixcost
	fi
done
