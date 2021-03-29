from matplotlib import pyplot as plt
import csv

queueVarA = []
dynamicVarA = []
queueVar = []
dynamicVar = []
time = []

xlabel = ""
ylabel = "Densities"
titleStr1 = "Asli graph"
titleStr2 = "Instant graph"
ylabel1 = ""
ylabel2 = ""

with open("asli.csv") as varFile:
    plots = csv.reader(varFile, delimiter = ",")
    i = 0
    for rows in plots:
        if (i ==0):
            xlabel = rows[0]
            ylabel1 = rows[1]
            ylabel2 = rows[2]
            i = 1
        else:
            queueVarA.append(float(rows[1]))
            dynamicVarA.append(float(rows[2]))
            time.append(float(rows[0]))

with open("graph.csv") as varFile:
    plots = csv.reader(varFile, delimiter = ",")
    i = 0
    for rows in plots:
        if (i ==0):
            i = 1
        elif (i > len(time)):
            break
        else:
            queueVar.append(float(rows[1]))
            dynamicVar.append(float(rows[2]))
            i += 1


figAsli,axAsli = plt.subplots()
fig,ax = plt.subplots()

axAsli.grid(True, color = "k")
axAsli.set_title(titleStr1)
axAsli.set_ylabel(ylabel)
axAsli.set_xlabel(xlabel)

ax.grid(True, color = "k")
ax.set_title(titleStr2)
ax.set_ylabel(ylabel)
ax.set_xlabel(xlabel)

axAsli.plot(time, queueVarA, "b",  linewidth = 1, label = ylabel1)
axAsli.plot(time, dynamicVarA, "r",  linewidth = 1, label = ylabel2)

ax.plot(time, queueVar, "b",  linewidth = 1, label = ylabel1)
ax.plot(time, dynamicVar, "r",  linewidth = 1, label = ylabel2)

ax.legend()
axAsli.legend()
plt.show()