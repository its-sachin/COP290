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

xlabel = ""
ylabel = ""
titleStr = ""

with open("asli.csv") as asliFile:
    plots = csv.reader(asliFile, delimiter = ",")
    i = 0
    for rows in plots:
        if (i == 0):
            xlabel = rows[0]
            ylabel = rows[1]
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
            else :
                queueVar[i-1] = float(rows[1])
                i += 1

def graphInit():
    plt.grid(True, color = "k")
    plt.title(titleStr)
    plt.ylabel(ylabel)
    plt.xlabel(xlabel)
    plt.legend()

mode = 1

i = 0

while (i <= 5):
    
    subprocess.run("./optimise ../Subtask2/trafficvideo.mp4 " + str(mode) + " " + str(i))
    read()

    absDiff, sqrMean = error(queueAsli, queueVar)

    
    plt.plot(time,queueAsli, "g", linewidth = 1, label = "Base Queue Density")
    plt.plot(time, queueVar, "b", linewidth = 1, label = labelStr)
    plt.plot(time, absDiff, "r", linewidth = 1, label = "Error")

    
    plt.show()


    i+= 1





