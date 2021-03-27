from matplotlib import pyplot as plt
import csv


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

with open("graph.csv") as varFile:
    plots = csv.reader(varFile, delimiter = ",")
    i = 0
    for rows in plots:
        if (i ==0):
            i = 1
        else :
            queueVar.append(float(rows[1]))

absDiff, sqrMean = error(queueAsli, queueVar)

print("Square root averaged mean error is " + str(sqrMean))
plt.grid(True, color = "k")
plt.plot(time,queueAsli, "g", linewidth = 2, label = "Base Queue Density")
plt.plot(time, queueVar, "b", linewidth = 2, label = "Queue Density")
plt.plot(time, absDiff, "r", linewidth = 2, label = "Error")

plt.title("Runtime Analysis")
plt.ylabel(ylabel)
plt.xlabel(xlabel)
plt.legend()
plt.show()


