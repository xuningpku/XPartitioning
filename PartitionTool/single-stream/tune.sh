#!/bin/bash

if [ $# -ne 5 ]; then
	echo "graph path, prefix, config, method, pnum, [scoretype], [delta]"
	exit
fi

#input variable
path=$1
prefix=$2
config=$3
method=$4

#constant
pnum=$5
bt="edge"
suffix="eb"


#hash
if [ $method = "hash" ]; then
	echo "./gknifedemo -p $pnum -c config/expr-config/homo/$config -o $prefix\_$config.$suffix.$method.part -g $path -b $bt -m $method > $prefix\_$config.$suffix.$method.result"
	./gknifedemo -p $pnum -c config/expr-config/homo/$config -o $prefix\_$config.$suffix.$method.part -g $path -b $bt -m $method > $prefix\_$config.$suffix.$method.result
fi

#ldg
if [ $method = "ldg" ]; then
	echo "./gknifedemo -p $pnum -c config/expr-config/$config -o partition/LJ/new-expr/$prefix\_$config.$suffix.$method.part -g $path -b $bt -m dg -w linear > partition/LJ/new-expr/$prefix\_$config.$suffix.$method.result"
	./gknifedemo -p $pnum -c config/expr-config/$config -o partition/LJ/new-expr/$prefix\_$config.$suffix.$method.part -g $path -b $bt -m dg -w linear > partition/LJ/new-expr/$prefix\_$config.$suffix.$method.result
fi

#hiob
if [ $method = "hiob" ]; then
	if [ $# -lt 5 ]; then
		echo "need scoretype"
		exit
	fi
	#st=$5
	st=7
	iof=1
	#sig="pr10"
	
	echo "./gknifedemo -p $pnum -c config/expr-config/$config -o $prefix\_$config.$suffix.$method.$st.$sig.part -g $path -b $bt -m $method -s $st > partition/LJ/new-expr/$prefix\_$config.$suffix.$method.$st.$sig.result"
	./gknifedemo -p $pnum -c config/expr-config/$config -o $prefix\_$config.$suffix.$method.$st.$sig.part -g $path -b $bt -m $method -s $st > partition/LJ/new-expr/$prefix\_$config.$suffix.$method.$st.$sig.result
#	./gknifedemo -p $pnum -c config/expr-config/$config -o $prefix\_$config.$suffix.$method.$st.part -g $path -b $bt -m $method -s $st > partition/LJ/new-expr/$prefix\_$config.$suffix.$method.$st.result
#	./gknifedemo -p $pnum -c config/$config -o $prefix\_$config.$suffix.$method.$st.part -g $path -b $bt -m $method -s $st -fc $iof > $prefix\_$config.$suffix.$method.$st.result

	exit	
	if [ $st -ne 5 -a $st -ne 6 ]; then
		if [ $# -eq 6 ]; then
			iof=$6
		fi	
		echo "./gknifedemo -p $pnum -c config/$config -o $prefix\_$config.$suffix.$method.$st.part -g $path -b $bt -m $method -s $st -fc $iof > $prefix\_$config.$suffix.$method.$st.result"
		./gknifedemo -p $pnum -c config/$config -o $prefix\_$config.$suffix.$method.$st.part -g $path -b $bt -m $method -s $st -fc $iof > $prefix\_$config.$suffix.$method.$st.result
	fi

	if [ $st -eq 5 ]; then
		if [ $# -ne 7 ]; then
			echo "need fc, and gama value"
			exit
		fi
		ifc=$6
		gama=$7
		echo "./gknifedemo -p $pnum -c config/$config -o $prefix\_$config.$suffix.$method.$st.$fc.$gama.part -g $path -b $bt -m $method -s $st -fc $ifc -gama $gama -uf true > $prefix\_$config.$suffix.$method.$st.$ifc.$gama.result"
		./gknifedemo -p $pnum -c config/$config -o $prefix\_$config.$suffix.$method.$st.$ifc.$gama.part -g $path -b $bt -m $method -s $st -fc $ifc -gama $gama -uf true > $prefix\_$config.$suffix.$method.$st.$ifc.$gama.result
	fi

	if [ $st -eq 6 ]; then
		if [ $# -lt 6 ]; then
			echo "need delta value"
			exit
		fi
		step=$6;
		#delta=$6;
		#for((i=1; i<=10; i++))
		#do
			#step=$(echo "$step+$delta" | bc)
			#echo step: $step, delta: $delta;
			echo "./gknifedemo -g $path -o $prefix\_$config.$suffix.$method.$st.$step.part -m $method -s $st -b $bt -bf $step -c config/$config -p 26 > $prefix\_$config.$suffix.$method.$st.$step.result"
			./gknifedemo -g $path -o $prefix\_$config.$suffix.$method.$st.$step.part -m $method -s $st -b $bt -bf $step -c config/$config -p 26 > $prefix\_$config.$suffix.$method.$st.$step.result
		#done
		exit
	fi
fi
