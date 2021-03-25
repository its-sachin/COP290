#include <algorithm>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;
using namespace std::chrono;

class Mode
{

public:

int getMethod() {
    return method;
}
int getSkipper() {
    return skipper;
}

void setMethod(int set_method) {
    method = set_method;
}

void setSkipper(int set_skipper) {
    skipper = set_skipper;
}


private:

int method;

// skipper is method related variable
// frames skipped for method 1
// number of threads for method 3 and 4
int skipper; 

    
};


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


void show(VideoCapture video,String winName[],double fps, Mat bg, Mode mode) {
    // int i = 0;
    // Mat frame1;
    Mat frame2;

    double QueueDensity =0;
    double DynamicDensity=0;
    double time=0;

    string filename="graph.csv";
    ofstream myfile; 

    myfile.open(filename);
    myfile<<"Time(s)"<<","<<"Queue Density"<<","<<"Dynamic Density"<<endl;

    cout<<"Time(s)"<<","<<"Queue Density"<<","<<"Dynamic Density"<<endl;

    while (true) {
        time+=(1);
        // frame1 = frame2.clone();
        bool isOpened = video.read(frame2);

        if (isOpened == false) {
            cout << "Video has ended" << endl;
            myfile.close();
            break;
        } 

        if (mode.getMethod() == 1 && (int)time%mode.getSkipper() != 0) {
            myfile<<(time)/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
            cout<< (time)/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
            continue;
        }

        if (mode.getMethod() == 2) {
            int factor = mode.getSkipper();
            resize(frame2, frame2, frame2.size(), factor,factor, INTER_LANCZOS4);
            resize(bg, bg, bg.size(), factor,factor, INTER_LANCZOS4);
        }
        
        cvtColor(frame2, frame2, COLOR_BGR2GRAY);
        Mat birdEye2 = changeHom(frame2);
        imshow(winName[0], birdEye2);

        Mat overallDiff;
        absdiff(bg, birdEye2,overallDiff);
        GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
        threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY );

        imshow(winName[1], overallDiff);

        // if (i == 0) {
        //     i =1;
        // }
        // else {
            // Mat birdEye1 = changeHom(frame1);  
            // Mat currDiff;
            // absdiff(birdEye1, birdEye2,currDiff);
            // GaussianBlur(currDiff,currDiff, Size(5,5),0);
            // threshold(currDiff,currDiff, 20, 255, THRESH_BINARY );

            // DynamicDensity=(double)(countNonZero(currDiff))/(double)256291;

            // imshow(winName[2], currDiff);

        // }

        QueueDensity=(double)countNonZero(overallDiff)/(double)256291;

        myfile<<time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
        cout<< time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
        
        
        if (waitKey(1) == 27){
            cout << "Esc key is pressed by user. Stopping the video" << endl;
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
    
    double fps,totalTime; 
    if (argc==1){
        cout<<"Please provide an filname/filepath for source video\n";
        return 0;
    }

    videopath=argv[1];

    VideoCapture video(videopath);

    if (video.isOpened() == false) {
        cout << "Unable to open the video, Check if the file exists in this directory" << endl;
        cin.get(); //wait for any key press
        return -1;
    }
    fps = video.get(CAP_PROP_FPS);
    totalTime = video.get(CAP_PROP_FRAME_COUNT)/fps;

    Mode mode;
    if (argc == 2) {
        cout<< "Please provide the method for optimization" << endl;
        return 0;
    }
    if (argc == 3) {
        cout<< "Please provide the argument for method" << endl;
        return 0;
    }

    mode.setMethod(stoi(argv[2]));
    mode.setSkipper(stoi(argv[3]));

    int emptime=345;
    if (argc == 5) {
        try{
            emptime= stoi(argv[4]);
            if (emptime<0 || emptime > totalTime) {
                cout<<"Time provided for background is invalid, taking default value." <<endl;
                emptime = 345;
            }
        }	

        catch(exception &err)
        {
            cout<<"Time provided for background is invalid, taking default value." <<endl;
            emptime = 345;
        }        
    }


    String winName[3] = {"Original Video","Overall Difference","Dynamic Difference"};

    auto start = high_resolution_clock::now();
    Mat bg = getBack(video,emptime);
    
    show(video,winName,fps,bg, mode);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "<< duration.count()/1000000 << " seconds" << endl;
    return 0;
    
}
