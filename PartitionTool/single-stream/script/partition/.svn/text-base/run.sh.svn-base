prefix=twitter
path=/home/hadoop/simon/dataset/twitter/twitter_rv.rand.elist
pnum=26
method=$2
if [ $method = "hash" ]; then
echo "./gknifedemo -p $pnum -c config/$1 -o $prefix\_$1.hash.part -g $path -f elist -m hash  > $prefix\_$1.vb.hash.result"
./gknifedemo -p $pnum -c config/$1 -o $prefix\_$1.hash.part -g $path -f elist -m hash > $prefix\_$1.vb.hash.result
fi

if [ $method = "ldg" ]; then
echo "./gknifedemo -p $pnum -c config/$1 -o $prefix\_$1.ldg.part -g $path -f elist -m dg -w linear > $prefix\_$1.vb.ldg.result"
./gknifedemo -p $pnum -c config/$1 -o $prefix\_$1.ldg.part -g $path -f elist -m dg -w linear  > $prefix\_$1.vb.ldg.result
fi

if [ $method = "hiob" ]; then
echo "./gknifedemo -p $pnum -c config/$1 -o $prefix\_$1.hiob.$3.part -g $path -f elist -m hiob -s $3 > $prefix_$1.vb.hiob.$3.result"
./gknifedemo -p $pnum -c config/$1 -o $prefix\_$1.hiob.$3.part -g $path -f elist -m hiob -s $3 > $prefix\_$1.vb.hiob.$3.result
fi
