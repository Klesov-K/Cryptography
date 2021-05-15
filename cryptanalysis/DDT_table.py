from array import *
S=array('i',[15,9,1,7,13,12,2,8,6,5,14,3,0,11,14,10])
Array_X = [0] * 16
for i in range(0,16):
    Array_X[i] = [0] * 16

print(" ","%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%5d%4d%4d%4d%4d%4d"%(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15))

for a in range(0,16):
    print('%3d' % a, end="")
    value=0
    for x in range(0,16):

        P=S[x]^S[x^a]
        Array_X[a][P]+=1


    for j in range(len(Array_X[i])):
        print ("%3d" % Array_X[a][j], end=',')
    print()