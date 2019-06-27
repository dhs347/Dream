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

x=[0]*11
X=[0]*7

x[1]=dotMul(A, A)
x[2]=dotMul(B, B)
x[3]=dotMul(C, C)
x[4]=dotMul(D, D)

x[5]=dotMul(A, B)
x[6]=dotMul(C, D)
x[7]=dotMul(A, C)
x[8]=dotMul(B, D)
x[9]=dotMul(B, C)
x[10]=dotMul(A, D)

X[1]=x[1]+x[2]-2*x[5]
X[2]=2*x[5]+2*x[8]-2*x[10]-2*x[2]
X[3]=x[3]+x[4]-2*x[6]
X[4]=2*x[6]+2*x[8]-2*x[9]-2*x[4]
X[5]=2*x[9]+2*x[10]-2*x[7]-2*x[8]
X[6]=x[2]+x[4]-2*x[8]

p=-X[2]*X[2]*X[3]-X[1]*X[4]*X[4]+X[2]*X[4]*X[5]+4*X[1]*X[3]*X[6]-X[5]*X[5]*X[6]
q=4*X[1]*X[3]-X[5]*X[5]

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
