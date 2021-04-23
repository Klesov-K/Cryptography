from array import *
S=array('i',[15,9,1,7,13,12,2,8,6,5,14,3,0,11,4,10])
M=array('i',[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15])

Array_X = [0] * 16
for i in range(0,16):
    Array_X[i] = [0] * 16

print(" ","%4d%4d%4d%4d%4d%4d%4d%4d%4d%4d%5d%4d%4d%4d%4d%4d"%(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15))

for x in range(0,16):
    print ('%3d'%x,end="")
    x1= x%2
    if (x1==1):
        X1=x1
    else:
        X1 = 0

    x2= (x // 2) % 2
    if (x2==1):
        X2 = x2
    else:
        X2 = 0


    x3=(x//4) % 2
    if (x3==1):
        X3 = x3
    else:
        X3= 0


    x4= x // 8
    if (x4==1):
        X4 = x4
    else:
        X4=0

    for j in range(0, 16):

        value=X4*(M[j]//8   ) ^ X3*( (M[j]//4)%2 ) ^ X2*( (M[j]// 2) % 2) ^ X1*( M[j]%2)
        Array_X[x][j]=value

    for y in range(0, 16):
            Sovpadenie = 0
            y1 = y % 2
            if (y1 == 1):
                Y1 = y1
            else:
                Y1 = 0

            y2 = (y // 2) % 2
            if (y2 == 1):
                Y2 = y2
            else:
                Y2 = 0

            y3 = (y // 4) % 2
            if (y3 == 1):
                Y3 = y3
            else:
                Y3 = 0

            y4 = y // 8
            if (y4 == 1):
                Y4 = y4
            else:
                Y4 = 0

            for i in range(0, 16):

                P = Y4 * (S[i] // 8) ^ Y3 * ((S[i] // 4) % 2) ^ Y2 * ((S[i] // 2) % 2) ^ Y1 * (S[i] % 2)
                if (P == Array_X[x][i]):
                    Sovpadenie += 1
            print("%3d" % (Sovpadenie-8),end=",")
    print('')








#for i in range (len(Array_X)):
#    for j in range(len(Array_X[i])):
#        print (Array_X[i][j], end='')
#    print()




