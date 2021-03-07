
# COP290: Project1 (Traffic Density Estimation)

## Part 1 - __Homography__

  * ### __How to run:__
    1. Run the makefile.
    2. An executable file named "cam" would be formed. Now run the code as "$ ./cam arg1 arg2 arg3 " . Here arg1 is the path of the image on which analysis has to be done (provide path if image is not in the same folder as the code). If arg1 is not provided console would throw "Please provide an filname for source image." and return from function.
    3. Furthermore, arg2 is the name with which wrapped image will be saved, and arg3 name of the cropped image. __NOTE :__ these are optional inputs, if not provided the images will be saved with default names. 
    4. If terminal says "Unable to open the file "filename Provided" Check if the file exists in this directory and if path you entered is correct or not.
    5. The image that you gave as input will now be shown in a GUI box.
    6. Select 4 corner points by left click of mouse (a black circle will be displayed where the point is selected) for giving reference for the homography. Points can be selected in any 		  order.Selecting 4 points is important if 4 points is not selected then a message "Please select 4 points" would be displayed and would ask for 4 points again.
    7. If by mistake any unwanted point is selected, click right mouse button. It will discard the last selected point and also its marker.
    8. After successfully selecting 4 points press any key. 
    9. A quadrilateral with your points as corners will be displayed.
    10. Press any key to change homography. Original image will be closed and Projected image will be shown.
    11. Press any key if you want to crop the image about the same points that you entered in step 5. Press "m" if you to change the dimensions of the cropped image and enter dimensions in console 	window.
    12. If key "m" is pressed console asks for dimesnsion, first x and then y. Remember dimensions can only be non negative integer. So if fallacious dimesnions are provied console asks for it again until valid dimesion is provided.
    13. Birds eye view will be displayed.
    14. Press any key to close the window.
