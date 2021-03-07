#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat changeHom(Mat in) {

    vector<Point2f> mapPoints;
    mapPoints.push_back(Point2f(472,52));
    mapPoints.push_back(Point2f(800,52));
    mapPoints.push_back(Point2f(800,830));
    mapPoints.push_back(Point2f(472,830));

    vector<Point2f> srcPoints;
    srcPoints.push_back(Point2f(865,240));
    srcPoints.push_back(Point2f(1279,232));
    srcPoints.push_back(Point2f(1551,1018));
    srcPoints.push_back(Point2f(138,968));

    Mat wrapImg = Mat::zeros(in.size(),CV_8UC3);
    Mat wrapedMatrix = findHomography(srcPoints, mapPoints);
    warpPerspective(in, wrapImg, wrapedMatrix, in.size());

    int xdimension=329;
    int ydimension=779;

    Mat out(ydimension,xdimension,CV_8UC3,Scalar(0,0,0));

    vector<Point2f> cropPoints;
    cropPoints.push_back(Point2f(0,0));  
    cropPoints.push_back(Point2f(xdimension-1,0));
    cropPoints.push_back(Point2f(xdimension-1,ydimension-1));
    cropPoints.push_back(Point2f(0,ydimension-1));

    wrapedMatrix = findHomography(mapPoints,cropPoints);

    warpPerspective(wrapImg, out, wrapedMatrix, out.size());

    return out;

}


void show(VideoCapture video,String winName[],double fps, Mat bg) {
    int i = 0;
    Mat frame1;
    Mat frame2;
    while (true) {
        frame1 = frame2.clone();
        bool isOpened = video.read(frame2);
        cvtColor(frame2, frame2, COLOR_BGR2GRAY);

        if (isOpened == false) {
            cout << "ERROR" << endl;
            break;
        } 

        Mat birdEye2 = changeHom(frame2);
        imshow(winName[0], birdEye2);

        Mat overallDiff;
        absdiff(bg, birdEye2,overallDiff);
        imshow(winName[1], overallDiff);

        if (i == 0) {
            i =1;
        }
        else {
            Mat birdEye1 = changeHom(frame1);  
            Mat currDiff;
            absdiff(birdEye1, birdEye2,currDiff);
            imshow(winName[2], currDiff);
        }


        if (waitKey(1000/fps) == 27){
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
    }
}

Mat getBack(VideoCapture video) {
    video.set(CAP_PROP_POS_MSEC,345000) ;
    Mat frame;
    bool isOpened = video.read(frame);
    cvtColor(frame, frame, COLOR_BGR2GRAY);

    if (isOpened == false) {
        cout << "ERROR in skipping to background frame" << endl;
    } 

    video.set(CAP_PROP_POS_MSEC,0) ;
    Mat changed = changeHom(frame);
    return changed;
}


int main(int argc, char** argv) {
    VideoCapture video("../../trafficvideo.mp4");

    String winName[3] = {"Original Video","Overall Difference","Dynamic Difference"};

    if (video.isOpened() == false) {
        cout << "Unable to open the video, Check if the file exists in this directory" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    double fps = video.get(CAP_PROP_FPS); 
    cout << "FPS: " << fps << endl;

    Mat bg = getBack(video);
    
    show(video,winName,fps,bg);
    return 0;
    
}
