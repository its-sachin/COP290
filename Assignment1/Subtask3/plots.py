from matplotlib import pyplot as plt
import csv
import subprocess

def error(queueAsli, queueVar):
    i = 0
    absDiff = []
    sqrMean = 0
    while (i < len(queueAsli)):
        absDiff.append(abs(queueAsli[i] - queueVar[i]))
        sqrMean += (queueAsli[i] - queueVar[i])**2
        i += 1

    sqrMean = (sqrMean/len(queueAsli))**0.5

    return absDiff, sqrMean

time = []
queueAsli = []
queueVar = []
colour = ['b', 'g', 'r', 'c', 'm', 'y', 'k']

xDef = ""
yDef = ""

with open("asli.csv") as asliFile:
    plots = csv.reader(asliFile, delimiter = ",")
    i = 0
    for rows in plots:
        if (i == 0):
            xDef = rows[0]
            yDef = rows[1]
            i =1
        else:
            time.append(float(rows[0]))
            queueAsli.append(float(rows[1]))
            queueVar.append(float(rows[1]))

def read():

    with open("graph.csv") as varFile:
        plots = csv.reader(varFile, delimiter = ",")
        i = 0
        for rows in plots:
            if (i ==0):
                i = 1
            elif (rows[0] == "$"):
                return int(rows[1])
            else :
                queueVar[i-1] = float(rows[1])
                i += 1
    return -1

def graphInit(xlabel,ylabel,titleStr):
    plt.grid(True, color = "k")
    plt.title(titleStr)
    plt.ylabel(ylabel)
    plt.xlabel(xlabel)

mode = 1

i = 0
maxSkip =2
offset=5
funx = []
funTime = []
funError = []

graphInit(xDef, yDef, "Method 1")
plt.plot(time,queueAsli, "b", linewidth = 1, label = "Base Queue Density")

while (i <= maxSkip):
    
    subprocess.run("./optimise ../Subtask2/trafficvideo.mp4 " + str(mode) + " " + str(offset*i), shell = True)
    funTime.append(read())
    absDiff, sqrMean = error(queueAsli, queueVar)
    funError.append(sqrMean)
    funx.append(i)

    plt.plot(time, queueVar, colour[i+1], linewidth = 1, label = "Skipping " + str(offset*i)+ " frames")
    # plt.plot(time, absDiff, "r", linewidth = 1, label = "Error")


    i+= 1
    print("\n")

plt.legend()
plt.show()

graphInit("Skipped Frame", "Time taken", "Analysis method 1")

plt.plot(funx, funTime, "b", linewidth = 1, label = "Time taken for analysis")
plt.plot(funx, funError, "r", linewidth = 1, label = "Sqaure mean error")

plt.legend()
plt.show()





