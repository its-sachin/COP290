from matplotlib import pyplot as plt
import csv
import subprocess
import shutil

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

work = 0

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

    opener = "graph.csv"
    if (work == -1):
        opener = str
    if (work == 1):
        print("Copying data in " + str)
        shutil.copy(opener, str)
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
        
        if (work ==0 or work == 1):
            subprocess.run("./optimise ../Subtask2/trafficvideo.mp4 " + str(mode) + " " + str(offset*i), shell = True)
            if (work == 0):
                funTime.append(read())
            else:
                funTime.append(readTest("GraphsTesting/graph" + str(mode)  + "-" + str(i) +".csv"))

        else:
            funTime.append(readTest("GraphsTesting/graph" + str(mode)  + "-" + str(i) +".csv"))


        absDiff, sqrMean = error(queueAsli, queueVar)
        funError.append(sqrMean)
        funx.append(i)

        axMain.plot(time, queueVar, colour[(i+1)%7], linewidth = 1, label = str(offset*i)+ " frames")
        axAbsDiff.plot(time, absDiff, colour[(i+1)%7], linewidth = 1, label =  str(offset*i)+ " frames")


        i+= 1
        print("")

def mode2(maxDown,gap):

    i = 1
    mode = 2
    a=0
    graphInit(xDef, yDef, "Method " + str(mode) + ": Queue Density",axMain)
    graphInit(xDef, "Absolute Difference", "Method " + str(mode) + ": Framewise error",axAbsDiff)
    graphInit("Size reduction factor", "Time taken","Method " + str(mode) + ": Runtime analysis",axTime)

    while (i <= maxDown):
        
        if (work ==0 or work == 1):
            subprocess.run("./optimise ../Subtask2/trafficvideo.mp4 " + str(mode) + " " + str(1920/i) + " " + str(1080/i), shell = True)
            if (work == 0):
                funTime.append(read())
            else:
                funTime.append(readTest("GraphsTesting/graph" + str(mode)  + "-" + str(i) +".csv"))

        else:
            funTime.append(readTest("GraphsTesting/graph" + str(mode)  + "-" + str(i) +".csv"))

        absDiff, sqrMean = error(queueAsli, queueVar)
        funError.append(sqrMean)
        funx.append(i)

        axMain.plot(time, queueVar, colour[(a+1)%7], linewidth = 1, label = " Size/" + str(i))
        axAbsDiff.plot(time, absDiff, colour[(a+1)%7], linewidth = 1, label = " Size/" + str(i))


        i+= gap
        a+=1
        print("")

def mode34(mode,maxThread):

    i = 1
    graphInit(xDef, yDef, "Method " + str(mode) + ": Queue Density",axMain)
    graphInit(xDef, "Absolute Difference", "Method " + str(mode) + ": Framewise error",axAbsDiff)
    graphInit("Number of threads", "Time taken","Method " + str(mode) + ": Runtime analysis",axTime)

    while (i <= maxThread):
        
        if (work ==0 or work == 1):
            subprocess.run("./optimise ../Subtask2/trafficvideo.mp4 " + str(mode) + " " + str(i), shell = True)
            if (work == 0):
                funTime.append(read())
            else:
                funTime.append(readTest("GraphsTesting/graph" + str(mode)  + "-" + str(i) +".csv"))

        else:
            funTime.append(readTest("GraphsTesting/graph" + str(mode)  + "-" + str(i) +".csv"))

        absDiff, sqrMean = error(queueAsli, queueVar)
        funError.append(sqrMean)
        funx.append(i)

        axMain.plot(time, queueVar, colour[(i+1)%7], linewidth = 1, label = str(i) + "-Threads")
        axAbsDiff.plot(time, absDiff, colour[(i+1)%7], linewidth = 1, label =  str(i) + "-Threads")


        i+= 1
        print("")

work = int(input("Plot saved(-1) or Analyse and plot(0) or Analyse, plot and save data(1): "))

if (work < -1 or work > 1):
    print("INVALID Value!!")

else :
    mode = int(input("Enter method: "))
    if (mode <=0 or mode > 4):
        print("INVALID Method!!")

    else:
        if (mode == 1):
            maxSkip, offset = input("Enter max frames skipped and offset: ").split(" ")
            print("")
            mode1(int(maxSkip), int(offset))
        elif (mode == 2):
            maxDown,gap = input("Enter maximum down factor of size and increment in factor: ").split(" ")
            print("")
            mode2(float(maxDown),float(gap))
        else:
            maxThread = int(input("Enter maximum number of threads: "))
            print("")
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