# COP290: Project1 (Traffic Density Estimation)

## Part 3 - __Tradeoff Analysis__


* ### __Following are the files and folders in this folder with their significance :__

    1. [__GraphsTesting/__](./GraphsTesting/)
        * This subfolder contains all the final results that we got and that are used in the report.
        * All the plots are stored in this folder with names ``` plot(i)-(name).png``` Where i is the method number and name denoting different graphs for same method (like "queue" for queue density and frame wise error, "runtime" for time and error vs parameter, "cpu" for cpu and memory usage vs parameter).
        * Subfolder __cpuData/.__ contains output of command usr/bin/time for every method with names ``` cpu(i)-(j).txt ``` where i is the method and j is number of threads.
        * Subfolder __GraphValues/.__ contains output of each and every method with different sets of parameters used for report, with names ``` graph(i)-(j).csv``` where i is the method and j is parameter value.

    5. [__report.pdf__](./report.pdf)
        * PDF file containing the report of the subtask.

    2. [__asli.csv__](./asli.csv)
        * This csv file stores the baseline data (output of method 0).

    3. [__graph.csv__](./graph.csv)
        * This csv file stores the output of latest run command of the code.
    
    4. [__plots.py__](./plots.py)
        * This python file is used for post processing, this takes as input the mode of work (like __-1__ if you want to just plot the values stored in __cpuData/.__ & __GraphValues/.__ and __0__ if you want to execute the code and plot the graph without saving and __1__ if you want to execute the code and simultaneously overwrite the values stored in __GraphValues/.__ and __cpuData/.__)
        * __NOTE:__ Mode 1 is for our own use for overwriting the values in case we find any error in execution, please try to avoid running it as it will reult in loss of data used for report.
        * If you select mode 0 or 1 path of video file will be asked.
        * Then it asked for the method and corresponding values (parameter max values and offset) for plotting graph.
        * After successfully opening (for mode -1) and successfully running code (for mode 0 and 1) this will plot the graph using matplotlib.

    5. [__instant.py__](./instant.py)

        * This is for instant plotting of graph of some values, used mainly for optical flow. But can be used for any method.
        * It just plots the graph.csv data and asli.csv data and error between them.
        * It asks if you want to plot dynamic density or not (enter "y" if you are using for optical flow otherwise enter anything).  
    
