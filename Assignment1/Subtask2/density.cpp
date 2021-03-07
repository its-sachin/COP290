#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;

Mat changeHom(Mat in) {

    vector<Point2f> mapPoints;
    mapPoints.push_back(Point2f(472,52));
    mapPoints.push_back(Point2f(800,52));
    mapPoints.push_back(Point2f(800,830));
    mapPoints.push_back(Point2f(472,830));

    vector<Point2f> srcPoints;
    srcPoints.push_back(Point2f(962,213));
    srcPoints.push_back(Point2f(1291,211));
    srcPoints.push_back(Point2f(1558,978));
    srcPoints.push_back(Point2f(338,976));

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
    double QueueDensity,DynamicDensity,TotalDensity;
    int time=0;
    string filename="graph.csv";
    ofstream myfile; 
    myfile.open(filename);
    myfile<<"time(ms)"<<","<<"QueueDensity"<<","<<"DynamicDensity"<<endl;
    while (true) {
        time+=(10);
        frame1 = frame2.clone();
        bool isOpened = video.read(frame2);

        if (isOpened == false) {
            cout << "Video has ended" << endl;
            myfile.close();
            break;
        } 
        cvtColor(frame2, frame2, COLOR_BGR2GRAY);
        Mat birdEye2 = changeHom(frame2);
        imshow(winName[0], birdEye2);

        Mat overallDiff;
        absdiff(bg, birdEye2,overallDiff);
        GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
        threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY );
        TotalDensity=(double)countNonZero(overallDiff)/(double)256291;
        imshow(winName[1], overallDiff);

        if (i == 0) {
            i =1;
        }
        else {
            Mat birdEye1 = changeHom(frame1);  
            Mat currDiff;
            absdiff(birdEye1, birdEye2,currDiff);
            GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
            threshold(currDiff,currDiff, 30, 255, THRESH_BINARY );
            DynamicDensity=(double)(countNonZero(currDiff))/(double)256291;
            QueueDensity=TotalDensity-DynamicDensity;
            imshow(winName[2], currDiff);
        }
        myfile<<time<<","<<QueueDensity<<","<<DynamicDensity<<endl;
        if (waitKey(10) == 27){
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
    }
}

Mat getBack(VideoCapture video,int emptime) {
    video.set(CAP_PROP_POS_MSEC,emptime*1000) ;
    Mat frame;
    bool isOpened = video.read(frame);
    cvtColor(frame, frame, COLOR_BGR2GRAY);

    if (isOpened == false) {
        cout << "The time for empty frame is not correct\n" << endl;
    } 

    video.set(CAP_PROP_POS_MSEC,0) ;
    Mat changed = changeHom(frame);
    return changed;
}


int main(int argc, char** argv) {
    string videopath,videoname;
    int emptime=345;
    if (argc==1){
        cout<<"Please provide an filname/filepath for source video\n";
        return 0;
    }
    if (argc==3){
        emptime= stoi(argv[2]);
    }
    videopath=argv[1];
    size_t found = videopath.find_last_of("/\\");
    videoname = videopath.substr(found+1);

    VideoCapture video(videoname);

    String winName[3] = {"Original Video","Overall Difference","Dynamic Difference"};

    if (video.isOpened() == false) {
        cout << "Unable to open the video, Check if the file exists in this directory" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    double fps = video.get(CAP_PROP_FPS); 
    cout << "FPS: " << fps << endl;

    Mat bg = getBack(video,emptime);
    
    show(video,winName,fps,bg);
    return 0;
    
}
