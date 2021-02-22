#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class mouseSelection{
    public:
    Mat image;
    vector<Point2f> inPoints;
    vector<Mat> imageTrack;

    // function to be given to set mouse callback (PROBLEM HERE)
    static void selectingPoints(int event, int x, int y, int flag, void* param) {

        mouseSelection *mouse = reinterpret_cast<mouseSelection*>(param);
        mouse->imageTrack.push_back(mouse->image);
        if (event == EVENT_LBUTTONDOWN) {
            circle(mouse->imageTrack.back(),Point2f(x,y),5,Scalar(0,0,0),FILLED);        
            imshow("Original Frame",mouse->imageTrack.back());
            if (mouse->inPoints.size() < 4) {
                mouse->inPoints.push_back(Point2f(x,y));
            }
        }
        else if (event == EVENT_RBUTTONDOWN){
            if (mouse->inPoints.size()>0){
                mouse->inPoints.pop_back();
                mouse->imageTrack.pop_back();
                cout<<mouse->imageTrack.size()<<endl;
            }
            imshow("Original Frame",mouse->imageTrack.back());
        }
        Mat imagei=mouse->image.clone();
        mouse->imageTrack.push_back(imagei);   

    }
    //function to sort the points in our prefrence always gives a  quad angle 
    void pointsSort(){
        Point2f mid= Point2f(0,0);
        for (auto it = inPoints.begin(); it != inPoints.end(); it++){ 
            mid.x+=(*it).x/4;
            mid.y+=(*it).y/4;
        }
        int i=0;
        for (int j=2;j<4; j++){ 
            if (inPoints[j].y<mid.y){
                if (inPoints[i].y<mid.y){
                    i++;
                }
                swap(inPoints[j],inPoints[i]);
            }        
        }
        if (inPoints[0].x>mid.x){
            swap(inPoints[0],inPoints[1]);          
        }
        if (inPoints[2].x<mid.x){
            swap(inPoints[2],inPoints[3]);          
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
    Mat sourcImgcopy=sourcImg.clone();
    mouseSelection mouse;
    mouse.image = sourcImgcopy;

    // display grayscaled source image
    imshow("Original Frame", sourcImgcopy);


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
    mouse.pointsSort();
    

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


