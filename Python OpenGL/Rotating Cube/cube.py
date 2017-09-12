from lines import *
from numpy import *
from math import *

#Joey van Eijk, 0893282, TI3A

l = Lines(1280, 768)
v1 = [-1.0,-1.0,-1.0]
v2 = [1.0,-1.0,-1.0]
v3 = [1.0, 1.0,-1.0]
v4 = [-1.0, 1.0,-1.0]
v5 = [-1.0,-1.0, 1.0]
v6 = [1.0,-1.0, 1.0]
v7 = [1.0, 1.0, 1.0]
v8 = [-1.0, 1.0, 1.0]

loc1 = [0, 0]
loc2 = [0, 0]
loc3 = [0, 0]
loc4 = [0, 0]
loc5 = [0, 0]
loc6 = [0, 0]
loc7 = [0, 0]
loc8 = [0, 0]

locationHolders = [loc1,loc2,loc3,loc4,loc5,loc6,loc7,loc8]
cubeVectors = [v1,v2,v3,v4,v5,v6,v7,v8]

#The function below scales the cube to a size that is suitable for the chosen resolution
def scaleCube(vectors):
    Scalair = 100
    for x in vectors:
        for i in range(len(x)):
            x[i] = (x[i] * Scalair)
    return vectors

#This function allows for the cube to be moved across the screen, right now it is used to centre the cube
def moveCube(vectors):
    Translate = 500
    for x in vectors:
        for i in range(len(x)):
            x[i] = (x[i] + Translate)
    return vectors

#This part of the code lets the cube turn while live, this works both positive,
#turning left, and negative, turning right.
def rotateCube(vectors):
    deg = 0
    deg += 0.0001*pi
    if(deg >= 360):
        deg = 0
    for x in vectors:
        x[0] = (math.cos(deg) * x[0]) + ((math.sin(deg))*x[2])
        x[2] = ((-(math.sin(deg)))* x[0]) + ((math.cos(deg))* x[2])

#Converting xyz to xy coordinates for usage in the 2D display
def dimensionShift(vectors):
    count = 0
    for x in vectors:
        flatX = ((1.0/(math.sqrt(2)) * x[0]) + (((1.0/(math.sqrt(2))) * x[2])))
        flatY = (((1.0/math.sqrt(6)) * x[0]) + (math.sqrt(2/3)* x[1]) + (((-1*( 1.0)/math.sqrt(6)))* x[2]))
        locationHolders[count] = [flatX + 640, flatY + 364]
        count = count+1
    return locationHolders

#Preparing for the draw by adding the lines in the buffer, this happens every sweep
def prepareDraw(locationHolders):
    l.addLine(locationHolders[0],locationHolders[1])
    l.addLine(locationHolders[1],locationHolders[2])
    l.addLine(locationHolders[2],locationHolders[3])
    l.addLine(locationHolders[3],locationHolders[0])
    l.addLine(locationHolders[0],locationHolders[4])
    l.addLine(locationHolders[1],locationHolders[5])
    l.addLine(locationHolders[2],locationHolders[6])
    l.addLine(locationHolders[3],locationHolders[7])
    l.addLine(locationHolders[4],locationHolders[5])
    l.addLine(locationHolders[5],locationHolders[6])
    l.addLine(locationHolders[6],locationHolders[7])
    l.addLine(locationHolders[7],locationHolders[4])

#Regulating code
scaleCube(cubeVectors)
for x in range(0, 10000):
    rotateCube(cubeVectors)
    dimensionShift(cubeVectors)
    prepareDraw(locationHolders)
    l.display()
    l.lines = []
print("Joey van Eijk, 0893282, TI3A")
