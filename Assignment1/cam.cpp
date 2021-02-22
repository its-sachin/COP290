#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class mouseSelection{
    public:
    Mat image;
    vector<Point2f> inPoints;

    // function to be given to set mouse callback (PROBLEM HERE)
    static void selectingPoints(int event, int x, int y, int flag, void* param) {

        mouseSelection *mouse = reinterpret_cast<mouseSelection*>(param);
        if (event == EVENT_LBUTTONDOWN) {
            cout << x << endl;
            imshow("Original Frame",mouse->image);
            if (mouse->inPoints.size() < 4) {
                mouse->inPoints.push_back(Point2f(x,y));
                // circle(sourcImg, Point(x,y),3,Scalar(0,0,255), 5, cv::LINE_AA);
            }
        }

    }
};


int main(int argc, char* argv[]) {

    // reading the image (grayscale) 
    Mat sourcImg = imread("empty.jpg",0);
    Mat wrapImg = Mat::zeros(sourcImg.size(),CV_8UC3);
    Mat cropImage(779,329,CV_8UC3,Scalar(0,0,0));
    if (sourcImg.empty()) {
        cout << "Unable to open the source image file - Check if empty.jpg present in the folder or not." << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    mouseSelection mouse;
    mouse.image = sourcImg;

    // display grayscaled source image
    imshow("Original Frame", sourcImg);

    // maping points given on course website
    vector<Point2f> mapPoints;
    mapPoints.push_back(Point2f(472,52));
    mapPoints.push_back(Point2f(800,52));
    mapPoints.push_back(Point2f(800,830));
    mapPoints.push_back(Point2f(472,830));
    vector<Point2f> cropPoints;
    cropPoints.push_back(Point2f(0,0));  
    cropPoints.push_back(Point2f(328,0));
    cropPoints.push_back(Point2f(328,778));
    cropPoints.push_back(Point2f(0,778));
          
    
    setMouseCallback("Original Frame", mouse.selectingPoints, &mouse);
    waitKey(0); // ---> to be changed.

    

    // do homography
    Mat wrapedMatrix = findHomography(mouse.inPoints, mapPoints);
    warpPerspective(sourcImg, wrapImg, wrapedMatrix, sourcImg.size());
    wrapedMatrix = findHomography(mapPoints,cropPoints);
    warpPerspective(wrapImg, cropImage, wrapedMatrix, cropImage.size());
    imshow("Wraped Image", wrapImg);
    waitKey(0);
    imshow("Croped Image",cropImage);
    waitKey(0);
    
}


