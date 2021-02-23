
# COL290: Project1 (Traffic Density Estimation)

## Part 1 - __Homography__

  * ### __How to run:__
    1. Run the makefile.
    2. (an instruction of giving path of image, to be added after making makefile)
    3. If terminal says "Unable to open the source image file - Check if empty.jpg present in the folder or not." then check if path you entered is correct or not.
    4. The image that you gave as input will now be shown in a GUI box.
    5. Select 4 corner points by left click of mouse (a black circle will be displayed where the point is selected) for giving reference for the homography. Points can be selected in any order.
    6. If by mistake any unwanted point is selected, click right mouse button. It will discard the last selected point. (Although circles will be still displayed, working on it.)
    7. After successfully selecting 4 points press any key. 
    8. A quadrilateral with your points as corners will be displayed.
    9. Press any key to change homography. Original image will be close and Projected image will be shown.
    10. Press any key if you want to crop the image about the same points that you entered in step 5. Press "m" if you to change the dimensions of the cropped image and enter dimensions in console window.
    11. Birds eye view will be displayed.
    12. Press any key to close the window.