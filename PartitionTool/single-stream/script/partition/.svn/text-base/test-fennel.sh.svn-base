prefix=livejournal
path=/home/hadoop/simon/dataset/LJ/soc-LiveJournal.undir.elist.rand
pnum=26

fc=([0]=0.7 [1]=7 [2]=70);
gama=([0]=1 [1]=1.25 [2]=1.5 [3]=2);


for((i = 0; i < 3; i++)) do
	for((j=0; j<= 3; j++)) do
		tmp_fc=${fc[$i]};
		tmp_gama=${gama[$j]};
	echo "./gknifedemo -p $pnum -c config/$1 -o $prefix\_$1.hiob.5.fc$tmp_fc.gama$tmp_gama.part -g $path -f elist -m hiob -b edge -uf true -fc $tmp_fc -gama $tmp_gama > $prefix\_$1.hiob.5.fc$tmp_fc.gama$tmp_gama.result"
	./gknifedemo -p $pnum -c config/$1 -o $prefix\_$1.hiob.5.fc$tmp_fc.gama$tmp_gama.part -g $path -f elist -m hiob -b edge -uf true -fc $tmp_fc -gama $tmp_gama > $prefix\_$1.hiob.5.fc$tmp_fc.gama$tmp_gama.result
	done
done
