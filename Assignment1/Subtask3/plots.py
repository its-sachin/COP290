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
    i = maxSkip

    while (i >= 0):
        
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


        i-= 1
        print("")

def mode2(maxDown,gap):

    i = maxDown
    mode = 2
    a=0
    graphInit(xDef, yDef, "Method " + str(mode) + ": Queue Density",axMain)
    graphInit(xDef, "Absolute Difference", "Method " + str(mode) + ": Framewise error",axAbsDiff)
    graphInit("Size reduction factor", "Time taken","Method " + str(mode) + ": Runtime analysis",axTime)

    while (i >= 1):
        
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


        i-= gap
        a+=1
        print("")


def mode34(mode,maxThread,offset):

    def readCPU(str) :
        cpu = ""
        mem = ""
        opener = "cpu.txt"
        if (work == -1):
            opener = str

        cpu = open(opener,"r+")
        cpuList = cpu.readlines()
        for i in cpuList:
            if (i[1:8] == "Percent"):
                j = -2
                while (i[j] != " "):
                    j -= 1
                cpu = i[j:-2]
            elif (i[1:8] == "Maximum"):
                j = -1
                while (i[j] != " "):
                    j -= 1
                mem = i[j:-1]
        
        if (work == 1):
            print("Copying time output in " + str)
            shutil.copy(opener, str)

        return int(cpu), float(mem)/1024

    i = maxThread

    cpuVar = []
    memVar = []

    figCPU,axCPU = plt.subplots()
    axMem = axCPU.twinx()

    graphInit(xDef, yDef, "Method " + str(mode) + ": Queue Density",axMain)
    graphInit(xDef, "Absolute Difference", "Method " + str(mode) + ": Framewise error",axAbsDiff)
    graphInit("Number of threads", "Time taken","Method " + str(mode) + ": Runtime analysis",axTime)
    graphInit("Number of threads", "CPU Usage","Method " + str(mode) +  ": Usage Analysis", axCPU)

    while (i >= 1):
        
        if (work ==0 or work == 1):
            subprocess.run("{ /usr/bin/time -v ./optimise ../Subtask2/trafficvideo.mp4 " + str(mode) + " " + str(i)+ "; } 2> cpu.txt", shell = True)
            if (work == 0):
                funTime.append(read())
            else:
                funTime.append(readTest("GraphsTesting/graph" + str(mode)  + "-" + str(i) +".csv"))
            

        else:
            funTime.append(readTest("GraphsTesting/graph" + str(mode)  + "-" + str(i) +".csv"))

        cpu,memory = readCPU("GraphsTesting/cpu" + str(mode)  + "-" + str(i) +".txt")

        cpuVar.append(cpu)
        memVar.append(memory)

        absDiff, sqrMean = error(queueAsli, queueVar)
        funError.append(sqrMean)
        funx.append(i)

        axMain.plot(time, queueVar, colour[(i+1)%7], linewidth = 1, label = str(i) + "-Threads")
        axAbsDiff.plot(time, absDiff, colour[(i+1)%7], linewidth = 1, label =  str(i) + "-Threads")

        if (i == 1): break
        i-= offset
        if (i <= 0): i = 1
        print("")

    axCPU.plot(funx, cpuVar, "b", linewidth = 2, label = "CPU Usage(%)")
    axMem.plot(funx, memVar, "c", linewidth = 2, label = "Max Memory(MB)")
    axMem.set_ylabel("Memory(MB)")
    axCPU.legend(loc="upper left")
    axMem.legend(loc="upper right")


work = int(input("Plot saved(-1) | Analyse and plot(0) | Analyse, plot and save data(1): "))

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
            maxThread, offset = input("Enter maximum number of threads and increment: ").split(" ")
            print("")
            if (mode == 3): mode34(3,int(maxThread),int(offset))
            else: mode34(4,int(maxThread), int(offset))

        axTime.plot(funx, funTime, "b", linewidth = 2, label = "Time(s)")
        axError.plot(funx, funError, "r", linewidth = 2, label = "Error")

        axMain.legend()
        axAbsDiff.legend()
        axError.set_ylabel("Error")
        axTime.legend(loc="upper left")
        axError.legend(loc="upper right")
        plt.tight_layout()
        plt.show()