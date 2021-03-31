# COP290: Project1 (Traffic Density Estimation)

## Part 3 - __Tradeoff Analysis__

  * ### __How to run:__
    1. Run the makefile.
    2. Now run the executable with the format for different methods (defined below):
    3. If any wrong input is provided then corresponding error will be thrown.
    4. While running the code, appropriate message will be printed in console denoting the present state of code.
    5. Output will be stored in the file "graph.csv" inside folder "analysis".


  * __Method 0:__ 
    * This  method  runs the code normally without any optimisation  i.e.   it  reads  every  frame  of  of  the  video  in  the  same  size  provided sequentially  and  perform  background  subtraction  of  the  bird  eye  view  of  theframe as a whole.
    * Time taken by this method is used as baseline for the other methods.
    * Run the executable with following extra arguments:
    ``` ./optimise arg1 0```
    * Where arg1 is the video path.

  * __Method 1:__
    * This methods runs the code by skipping frames.
    * Run the executable with following extra arguments:
    ``` ./optimise arg1 1 arg2```
    * Where arg1 is the video path and arg2 is number of frames to be skipped.

  * __Method 2:__
    * This methods runs the code by resizing the frame of video.
    * Run the executable with following extra arguments:
    ``` ./optimise arg1 2 arg2 arg3```
    * Where arg1 is the video path and arg2 & arg3 are width and height of the resized video respectively.

  * __Method 3:__
    * This methods performs analysis by cropping the frame and giving each part to different threads.
    * Run the executable with following extra arguments:
    ``` ./optimise arg1 3 arg2```
    * Where arg1 is the video path and arg2 is number of threads.

  * __Method 4:__
    * This methods runs the code on consecutive frames in parallel by giving them to different threads.
    * Run the executable with following extra arguments:
    ``` ./optimise arg1 4 arg2```
    * Where arg1 is the video path and arg2 is number of threads.

  __Following are some extra methods that we performed:__

  * __Method 3(a):__
    * This methods performs analysis by first cropping all the frames in one go and giving all the subparts to each threads and perform analysis parallely.
    * Run the executable with following extra arguments:
    ``` ./optimise arg1 31 arg2```
    * Where arg1 is the video path and arg2 is number of threads.

  * __Method 4(a):__
    * This methods runs the code on subparts of video parallely by giving each part to different threads (for eg. its runs first half and second parallely for 2 threads).
    * Run the executable with following extra arguments:
    ``` ./optimise arg1 41 arg2```
    * Where arg1 is the video path and arg2 is number of threads.

  * __Method 5:__
    * This methods performs the dense optical flow.
    * Run the executable with following extra arguments:
    ``` ./optimise arg1 5```
    * Where arg1 is the video path.

  * __Method 6:__
    * This methods performs the sparse optical flow.
    * Run the executable with following extra arguments:
    ``` ./optimise arg1 6```
    * Where arg1 is the video path.

 

