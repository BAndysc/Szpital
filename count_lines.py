import glob, os, re
os.chdir("src/")
reg = re.compile(r'^(.*?)\(.*?\) ?\{ ?(?:\r)?\n((.|(?:\r)?\n)*?)(?:\r)?\n\}',re.M)
avg =0
count = 0
bysize = {}
byfile = {}
for file in glob.glob("*.c"):
	if not file in byfile:
		byfile[file] = {"count":0,"sum":0}
	f = open(file,"r").read()
	fal = reg.findall(f)
	for func in fal:
		lines = 0
		linx = func[1].split('\n')
		for lin in linx:
			if lin!="" and lin != "\r":
				lines+=1
		print func[0] + ": "+str(lines)
		if not lines in bysize:
			bysize[lines]=0
		bysize[lines] += 1
		count += 1
		byfile[file]['count'] += 1
		byfile[file]['sum'] += lines
		avg += lines

print "average: "+str(avg/float(count))
for lin in bysize:
	print "Funcs with "+str(lin)+" lines: "+str(bysize[lin])

for file in byfile:
	print "File "+file+" avg: "+str(byfile[file]['sum']/float(byfile[file]['count']))
