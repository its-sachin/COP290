
# COP290: Project1 (Traffic Density Estimation)

## Part 1 - __Homography__

  * ### __How to run:__
    1. Run the makefile.
    2. The exucutable file "cam" would be formed. Now you could run the code as "$ ./cam arg1 arg2 arg3 " . Here arg1 is the name of the image on which analysis has to be done and if not provided console would throw "Please provide an filname for source image\n" and return from function. arg2 and arg3 are optional.The wrapped image would be saved as arg2 and cropped image as arg3 if provided else saved by default name.
    3. If terminal says "Unable to open the file <filenameProvided> Check if the file exists in this directory" then check if path you entered is correct or not.
    4. The image that you gave as input will now be shown in a GUI box.
    5. Select 4 corner points by left click of mouse (a black circle will be displayed where the point is selected) for giving reference for the homography. Points can be selected in any 		  order.Selecting 4 points is important if 4 points is not selected then a message "Please select 4 points\n" would be displayed and would ask for 4 points again
    6. If by mistake any unwanted point is selected, click right mouse button. It will discard the last selected point and also its marker.
    7. After successfully selecting 4 points press any key. 
    8. A quadrilateral with your points as corners will be displayed.
    9. Press any key to change homography. Original image will be close and Projected image will be shown.
    10. Press any key if you want to crop the image about the same points that you entered in step 5. Press "m" if you to change the dimensions of the cropped image and enter dimensions in console 	window.
    11.If m is pressed console asks for dimesnsion first x and then y . Remember Dimensions cant be negative. So if negative dimesnions provied console asks for it again until positive dimesion is provided.
    11. Birds eye view will be displayed.
    12. Press any key to close the window.
