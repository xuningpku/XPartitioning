#!/bin/bash
#

#global constant
giraph="giraph-0.2-SNAPSHOT-for-hadoop-0.20.2-jar-with-dependencies.jar"
pkggraph="org.apache.giraph"
workers=27
bt="edge"
suffix="eb"
methodenum=("hash" "ldg" "hiob.5.6.1.5" "hiob.6.0.1" "hiob.6.0.01" "hiob.6.0.001" "hiob.7");

#algorithms abbr.
sssp="SingleSourceShortestPathVertex"
pr="SimpleDirectedPageRankVertex2"
tc="SimpleTriangleCount"


#input parameter
#graph for the graph type
graph=""
method="hash"
config=""
algorithm="pagerank"
environment=""
engine=""

#infer from input parameter
pnum=""
ioheter=""
defaulthash="false"
cputype=0
#sig="pr10."

#help info of this script;
usage( ) {
	echo "Usage:";
	echo "	-g required. specify the input graph type";
	echo "		amazon0312"
	echo "		soc-LiveJournal"
	echo "		web-NotreDame"
	echo "		wiki-Vote"
	echo "		twitter"
	echo "	-c required. specify the config file type";
	echo "		config filename formate: heter_config_$pnum_11_$ioconfig"
	echo "		pnum={4,8,16,26}"
	echo "		ioconfig={cpu,cpu_io, io}"
	echo "	-e engine[default]";
	echo "	-v heterogenous environment configuration, using configuration file as a parameter.";
	echo "	-a specify the algorithm[default=pagerank]";
	echo "		pagerank: standard page rank."
	echo "		tc: triangle count."
	echo "		sssp: single source shortest path."
	echo "	-m specify the partition type[default=0]";
	echo "		0: hash"
	echo "		1: ldg"
	echo "		2: hiob.5.6.1.5"
	echo "		3: hiob.6.0.1"
	echo "		4: hiob.6.0.01"
	echo "		5: hiob.6.0.001"
	echo "		6: hiob"
	echo "	-f set cpu frequenent distribution"
	echo "		0: all 2.6gh"
	echo "		1:  2.6gh, 1.8gh"
	echo "		2:  2.6gh, 0.8gh"
	echo "		3:  1.8gh, 0.8gh"
	echo "	-h print this information";
	exit;
}

setcpufrequency( ) {
	totalmachine=$1;
	part=$2;
        echo $PWD
#	echo tm=$totalmachine part=$part;
	idx=0;
	if [ $part -eq 0 ]; then
		for host in `cat validhosts`
		do
#			echo notpart: $host
			echo "./cpuset $host 2600000"
			./cpuset $host 2600000
			((idx++));
			if [ $idx -eq $totalmachine ]; then
				break;
			fi
		done
	elif [ $part -eq 1 ]; then
		mid=$(((totalmachine/2)));
		for host in `cat validhosts`
		do
#			echo part=$host
			if [ $idx -lt $mid ]; then
				echo "./cpuset $host 2600000"
				./cpuset $host 2600000
			else
				echo "./cpuset $host 1800000"
				./cpuset $host 1800000
			fi
			((idx++));
			if [ $idx -eq $totalmachine ]; then
				break;
			fi
		done
	elif [ $part -eq 2 ]; then
		mid=$(((totalmachine/2)));
		for host in `cat validhosts`
		do
#			echo part=$host
			if [ $idx -lt $mid ]; then
				echo "./cpuset $host 1800000"
				./cpuset $host 1800000
			else
				echo "./cpuset $host 1800000"
				./cpuset $host 1800000
			fi
			((idx++));
			if [ $idx -eq $totalmachine ]; then
				break;
			fi
		done
	elif [ $part -eq 3 ];then
		mid=$(((totalmachine/2)));
		for host in `cat validhosts`
		do
#			echo part=$host
			if [ $idx -lt $mid ]; then
				echo "./cpuset $host 1800000"
				./cpuset $host 1800000
			else
				echo "./cpuset $host 800000"
				./cpuset $host 800000
			fi
			((idx++));
			if [ $idx -eq $totalmachine ]; then
				break;
			fi
		done
	elif [ $part -eq 4 ];then
		mid=3;
		for host in `cat validhosts`
		do
#			echo part=$host
			if [ $idx -lt $mid ]; then
				echo "./cpuset $host 1800000"
				./cpuset $host 1800000
			else
				echo "./cpuset $host 2600000"
				./cpuset $host 2600000
			fi
			((idx++));
			if [ $idx -eq $totalmachine ]; then
				break;
			fi
		done
	fi
#	exit
}

getParameter( ) {

#	echo "process parameter ......";
	#process input parameter
	while getopts ":g:c:a:hm:e:f:v:" opt; do
		case $opt in
			g )
				graph=$OPTARG
				;;
			c )
				config=$OPTARG
				;;
			m )
#			echo "${methodenum[$OPTARG]}"
				method=${methodenum[$OPTARG]}
#				echo "$method"
				;;
			a )
				algorithm=$OPTARG
				;;
			e )
				engine=$OPTARG
				;;
			v )
				environment=$OPTARG
				;;
			f )
				cputype=$OPTARG
				;;
			? )
				echo "Invalid parameter"
				usage;
				;;
		esac
	done

	if [ -z "$graph" -o -z "$config" -o -z "$environment" ]; then
		echo "Lack required option"
		usage;
	fi

	#infer other parameter
	tmp=${environment#*config_};
	pnum=${tmp%%_*}


	#set io heterogenous
	tmp=${tmp#*_}
	nb=${tmp%%_*}
	ioheter=""

	if [ $nb -eq 13 ]; then
		ioheter="-nl 1:3 -mr 1:1"
	elif [ $nb -eq 15 ]; then
		ioheter="-nl 1:5 -mr 1:1"
	elif [ $nb -eq 110 ]; then
		ioheter="-nl 1:10 -mr 1:1"
	fi

	#detect partition type
	tmp=$(echo `expr match $config homo.*`);
#	sig="pr10."
	if [ $tmp -ne 0 ]; then
		sig=""
	fi

#	tmp=$(echo `expr match $config .*_io.*`);
#	if [ $tmp -ne 0 ]; then
#		ioheter="-nl 1:3  -mr 1:1";
#	else
#		ioheter="";
#	fi

#	echo "configuring CPU hetergeneous..."
#	tmp=$(echo `expr match $config .*_cpu.*`);
   setcpufrequency $pnum $cputype
#	echo "end configuration.";
exit

	echo -e "\e[1;32mgraph=$graph config=$config method=$method algorithm=$algorithm pnum=$pnum ioheter=$ioheter engine=$engine cputype=$cputype\e[0m";
}

runSingleInstance( ) {
	echo "Begin to run a single test instance ...";
	cnt=`cat index`;
	case $algorithm in
		"pagerank" )
			echo "hadoop jar $giraph $pkggraph.MyAppRunner $pkggraph.myapp.$pr -of $pkggraph.myapp.$pr\$${pr}OutputFormat -ca mapred.child.java.opts=-Xmx10240m -if $pkggraph.myapp.$pr\$${pr}InputFormat -ip /user/simon/$graph/graph/ -op /user/simon/$graph/result/${graph}${cnt} -w $workers -rw $pnum $ioheter -pm /user/simon/$graph/partitionmap/new-expr/${graph}_$config.$suffix.$method.${sig}part -e $engine >& ${graph}_$environment.$suffix.$method.${sig}result"
			hadoop jar $giraph $pkggraph.MyAppRunner $pkggraph.myapp.$pr -of $pkggraph.myapp.$pr\$${pr}OutputFormat -ca mapred.child.java.opts=-Xmx10240m -if $pkggraph.myapp.$pr\$${pr}InputFormat -ip /user/simon/$graph/graph/ -op /user/simon/$graph/result/${graph}${cnt} -w $workers -rw $pnum $ioheter -pm /user/simon/$graph/partitionmap/new-expr/${graph}_$config.$suffix.$method.${sig}part -e $engine >& ${graph}_$environment.$suffix.$method.${sig}result
			;;
		"sssp" )
			echo "hadoop jar $giraph $pkggraph.MyAppRunner $pkggraph.myapp.$sssp -of $pkggraph.myapp.$sssp\$${sssp}OutputFormat -if $pkggraph.myapp.$sssp\$${sssp}InputFormat -ip /user/simon/$graph/graph/ -op /user/simon/$graph/result/${graph}$cnt -w $workers -rw $pnum $ioheter -pm /user/simon/$graph/partitionmeta/$graph/${graph}_$config.$suffix.$method.part >& ${graph}_$config.$suffix.$method.result"
			hadoop jar $giraph $pkggraph.MyAppRunner $pkggraph.myapp.$sssp -of $pkggraph.myapp.$sssp\$${sssp}OutputFormat -if $pkggraph.myapp.$sssp\$${sssp}InputFormat -ip /user/simon/$graph/graph/ -op /user/simon/$graph/result/${graph}$cnt -w $workers -rw $pnum $ioheter -pm /user/simon/$graph/partitionmap/expr-stream/${graph}_undir_$config.$suffix.$method.part >& ${graph}_undir_$config.$suffix.$method.result
			;;
		"tc" )
			echo "hadoop jar $giraph $pkggraph.MyAppRunner $pkggraph.myapp.$tc -of $pkggraph.myapp.$tc\$${tc}OutputFormat -if $pkggraph.myapp.$tc\$${tc}InputFormat -ip /user/simon/$graph/graph/ -op /user/simon/$graph/result/${graph}$cnt -w $workers -rw $pnum $ioheter -pm /user/simon/$graph/partitionmeta/$graph/${graph}_$config.$suffix.$method.part >& ${graph}_$config.$suffix.$method.result"
		    hadoop jar $giraph $pkggraph.MyAppRunner $pkggraph.myapp.$tc -of $pkggraph.myapp.$tc\$${tc}OutputFormat -if $pkggraph.myapp.$tc\$${tc}InputFormat -ip /user/simon/$graph/graph/ -op /user/simon/$graph/result/${graph}$cnt -w $workers -rw $pnum $ioheter -pm /user/simon/$graph/partitionmeta/$graph/${graph}_$config.$suffix.$method.part >& ${graph}_$config.$suffix.$method.result
			;;
	esac
	((cnt++));
	echo $cnt > index;
}

#main body
#getParameter $@
#exit;
#runSingleInstance

setcpufrequency $@
#end main body
