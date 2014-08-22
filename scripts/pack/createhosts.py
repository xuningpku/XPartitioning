import os
os.system("hadoop job -list-active-trackers > hadoopnodes")
t = os.popen("cat hadoopnodes |wc -l")
num = t.read()
f = open("./hadoopnodes","r")
fhost = open("./validhosts","w")
hhost = open("./tmp","w")
hhost.write (str(int(num)-1)+"\n")
#hhost.write()
i = 0
for line in f:
	line = line.split('_')
	server = line[1].split(':')
	if server[0]<>"changping11":
		fhost.write(server[0]+"\n")
		hhost.write(server[0]+" "+str(i)+"\n")
		i+=1
hhost.close()
fhost.close()
f.close()
os.system("hadoop fs -rm /user/simon/tmp")
os.system("hadoop fs -copyFromLocal ./tmp /user/simon/tmp")
