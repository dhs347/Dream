

f=[0]*100000
g=[0]*100000
f[1]=f[2]=1
g[1]=g[2]=1
p1=10**9+7
p2=10**9+9
for i in range(3,20000):
	f[i]=(f[i-1]+f[i-2])%p1
	g[i]=(g[i-1]+g[i-2])%p2

for i in range(35):
	if (f[i]>500000):
		print(i)
		break
	




T=int(input())
while T>0:
	T=T-1
	ans=[]
	ret=[]
	n=int(input())
	op=0
	for i in range(1<<15):
		if ((i>>1&1)==1): continue 
		s1=s2=0
		for j in range(15):
			if ((i>>j)&1):
				s1+=f[f[f[j+1]]]
				s1%=p1
				s2+=g[g[g[j+1]]]
				s2%=p2
		
		
ans=[]	
if s1==n%p1 and s2==n%p2:
	for j in range(8):
		if ((i>>j)&1):
			ans.append(f[j+1])
	if len(ret)==0:
		ret=ans.copy()
	elif ans<ret:
		ret=ans.copy()
	op=1



	if op==0: print(-1) 
	else:
		t=len(ret)
		for j in range(t-1): print(ret[j],end=' ')
		print(ret[t-1])




