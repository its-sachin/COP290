# COP290: Project1 (Traffic Density Estimation)

## Part 2 - __Density Estimation__

  * ### __How to run:__
    1. Run the makefile.
    2. An executable file named "density" would be formed. Now run the code as "$ ./cam arg1 arg2 arg3" . Here arg1 is the path of the video on which analysis has to be done (provide path if video is not in the same folder as the code otherwise name with extension is sufficient). If arg1 is not provided console would throw "Please provide an filname/filepath for source video." and return from then code.
    3. Moreover, arg2 is the speed at which video will be played and analysed, i.e. how fast the frames of the video are checked with the background. (hence higher this value more will be load on the system). \
    __NOTE :__ this is an optional argument, if not provided by default computation will be done in real time, i.e in fps of video. Also, since domain of this value is positive integers only, fallacious values will be disregarded and deafult value will be taken
    4. Furthermore, arg3 is the time in seconds which you want to be considered as background frame for density analysis(Background frame is the frame with respect to which changes in the frame are analysed). \
    __NOTE :__ athis is also an optional input, if not provided the background will be set by default. Moreover in case of wrone input (like negative value and value more than time of video) default value will be take.  
    5. If terminal says "Unable to open the filename Provided" Check if the file exists in this directory and if path you entered is correct or not.
    6. The video that you gave as input will now be played in a window named "Original Video".
    7. The video showing the overall changes will be played in window named "Overall Difference".
    8. The video showing only the dynamic changes will be played in window named "Dynamic Difference".
    9. Queue Density and Dynamic density values with time in seconds will be printed in console window, seperated with comma for each frame.
    10. Press "Esc" if you want to stop the process.
    11. After termination values printed in console will also be saved in a csv file named "graph.csv".