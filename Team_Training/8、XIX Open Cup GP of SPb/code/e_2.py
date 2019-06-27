#from math import gcd


def gcd(x, y):
    if y==0:
        return x
    return gcd(y, x%y)


def getVector():
    return list(map(int, input().split()))


def dotMul(A, B):
    ret=0
    for i in range(len(A)):
        ret+=A[i]*B[i]
    return ret


def mul(a, B):
    ret=[0]*len(B)
    for i in range(len(B)):
        ret[i]=a*B[i]
    return ret


def getLen(A):
    ret=0
    for i in range(len(A)):
        ret+=A[i]*A[i]
    return ret


def minus(A, B):
    n=len(A)
    ret=[0]*n
    for i in range(n):
        ret[i]=B[i]-A[i]
    return ret


def add(A, B):
    n=len(A)
    ret=[0]*n
    for i in range(n):
        ret[i]=B[i]+A[i]
    return ret


n=int(input())
A=getVector()
B=getVector()
C=getVector()
D=getVector()

EE=minus(A, B)
FF=minus(C, D)
if getLen(EE)*getLen(FF)==dotMul(EE,FF)**2:
    S=minus(D,A)
    T=minus(D,C)
    tmp=dotMul(S,T)
    p=getLen(S)*getLen(T)-tmp**2
    q=getLen(T)
    t = gcd(p, q)
    p //= t
    q //= t
    if p<0:
        p=-p
    if q<0:
        q=-q
    print(p, q, sep='/')
    quit(0)

AB=minus(B, A)
CD=minus(D, C)

p=[0]*5
q=[0]*5
p[1]=dotMul(A, AB)
p[2]=dotMul(B, AB)
p[3]=-dotMul(C, AB)
p[4]=-dotMul(D, AB)
q[1]=dotMul(A, CD)
q[2]=dotMul(B, CD)
q[3]=-dotMul(C, CD)
q[4]=-dotMul(D, CD)

s=[0]*4
t=[0]*4
s[1]=p[1]-p[2]
s[2]=p[3]-p[4]
s[3]=-p[2]-p[4]
t[1]=q[1]-q[2]
t[2]=q[3]-q[4]
t[3]=-q[2]-q[4]

p=s[2]*t[1]-s[1]*t[2]
r1=s[2]*t[3]-s[3]*t[2]
r2=s[3]*t[1]-s[1]*t[3]

ret=minus(add(mul(r1,A),mul((p-r1),B)),add(mul(r2,C),mul((p-r2),D)))
ret=getLen(ret)
p=p**2
q=ret
p, q=q, p

if q==0:
    p=X[6]
    q=1
else:
    t = gcd(p, q)
    p //= t
    q //= t

if q<0:
    p=-p
    q=-q

print(p,q,sep='/')
