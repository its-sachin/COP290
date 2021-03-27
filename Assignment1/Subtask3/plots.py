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

def readTest(str):

    with open(str) as varFile:
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

def graphInit(xlabel,ylabel,titleStr,ax):
    ax.grid(True, color = "k")
    ax.set_title(titleStr)
    ax.set_ylabel(ylabel)
    ax.set_xlabel(xlabel)


funx = []
funTime = []
funError = []

figMain,axMain = plt.subplots()
figAbsDiff,axAbsDiff = plt.subplots()
figTime,axTime = plt.subplots()
axError = axTime.twinx()



axMain.plot(time,queueAsli, "b", linewidth = 1, label = "Base Queue Density")


def mode1(maxSkip,offset):

    mode = 1
    graphInit(xDef, yDef, "Method " + str(mode) + ": Queue Density",axMain)
    graphInit(xDef, "Absolute Difference", "Method " + str(mode) + ": Framewise error",axAbsDiff)
    graphInit("Skipped Frames", "Time taken","Method " + str(mode) + ": Runtime analysis",axTime)
    i = 0

    while (i <= maxSkip):
        
        subprocess.run("./optimise ../Subtask2/trafficvideo.mp4 " + "1" + " " + str(offset*i), shell = True)
        funTime.append(read())
        # funTime.append(readTest("GraphsTesting/graph" + str(mode)  + "-" + str(i) +".csv"))
        absDiff, sqrMean = error(queueAsli, queueVar)
        funError.append(sqrMean)
        funx.append(i)

        axMain.plot(time, queueVar, colour[(i+1)%7], linewidth = 1, label = str(offset*i)+ " frames")
        axAbsDiff.plot(time, absDiff, colour[(i+1)%7], linewidth = 1, label =  str(offset*i)+ " frames")


        i+= 1
        print("\n")

def mode2(maxDown):

    i = 1
    mode = 2
    graphInit(xDef, yDef, "Method " + str(mode) + ": Queue Density",axMain)
    graphInit(xDef, "Absolute Difference", "Method " + str(mode) + ": Framewise error",axAbsDiff)
    graphInit("Size reduction factor", "Time taken","Method " + str(mode) + ": Runtime analysis",axTime)

    while (i <= maxDown):
        
        # subprocess.run("./optimise ../Subtask2/trafficvideo.mp4 " + "2" + " " + str(1920/i) + " " + str(1080/i), shell = True)
        # funTime.append(read())
        funTime.append(readTest("GraphsTesting/graph" + str(mode) + "-" +str(i) +".csv"))
        absDiff, sqrMean = error(queueAsli, queueVar)
        funError.append(sqrMean)
        funx.append(i)

        axMain.plot(time, queueVar, colour[(i+1)%7], linewidth = 1, label = " Size/" + str(i))
        axAbsDiff.plot(time, absDiff, colour[(i+1)%7], linewidth = 1, label = " Size/" + str(i))


        i+= 1
        print("\n")

def mode34(mode,maxThread):

    i = 1
    graphInit(xDef, yDef, "Method " + str(mode) + ": Queue Density",axMain)
    graphInit(xDef, "Absolute Difference", "Method " + str(mode) + ": Framewise error",axAbsDiff)
    graphInit("Number of threads", "Time taken","Method " + str(mode) + ": Runtime analysis",axTime)

    while (i <= maxThread):
        
        subprocess.run("./optimise ../Subtask2/trafficvideo.mp4 " + "3" + " " + str(i), shell = True)
        funTime.append(read())
        # funTime.append(readTest("GraphsTesting/graph" + str(mode)  + "-" + str(i) +".csv"))
        absDiff, sqrMean = error(queueAsli, queueVar)
        funError.append(sqrMean)
        funx.append(i)

        axMain.plot(time, queueVar, colour[(i+1)%7], linewidth = 1, label = str(i) + "-Threads")
        axAbsDiff.plot(time, absDiff, colour[(i+1)%7], linewidth = 1, label =  str(i) + "-Threads")


        i+= 1
        print("\n")

mode = int(input("Enter method: "))
if (mode <=0 or mode > 4):
    print("INVALID Method!!")

else:

    if (mode == 1):
        maxSkip, offset = input("Enter max frames skipped and offset: ").split(" ")
        mode1(int(maxSkip), int(offset))
    elif (mode == 2):
        maxDown = int(input("Enter maximum down factor of size: "))
        mode2(maxDown)
    else:
        maxThread = int(input("Enter maximum number of threads: "))
        if (mode == 3): mode34(3,maxThread)
        else: mode34(4,maxThread)

    axTime.plot(funx, funTime, "b", linewidth = 1, label = "Time(s)")
    axError.plot(funx, funError, "r", linewidth = 1, label = "Error")

    axError.set_ylabel("Error")
    axMain.legend()
    axAbsDiff.legend()
    axTime.legend()
    axError.legend()
    plt.tight_layout()
    plt.show()