#include <algorithm>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <pthread.h>
using namespace cv;
using namespace std;
using namespace std::chrono;

struct modefour{
    VideoCapture video;
    map<int,double> data;
    Mat bg;
    int start;
    int end;
};


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

double xDimen;
double yDimen;
int noThread;
private:

int method;

// skipper is method related variable
// frames skipped for method 1
// number of threads for method 3 and 4
int skipper; 

    
};


Mat changeHom(Mat in) {

    double xFactor = in.size().width/1920.0;
    double yFactor = in.size().height/1080.0;


    vector<Point2f> mapPoints;
    mapPoints.push_back(Point2f(472*xFactor,52*yFactor));
    mapPoints.push_back(Point2f(800*xFactor,52*yFactor));
    mapPoints.push_back(Point2f(800*xFactor,830*yFactor));
    mapPoints.push_back(Point2f(472*xFactor,830*yFactor));

    vector<Point2f> srcPoints;
    srcPoints.push_back(Point2f(962*xFactor,213*yFactor));
    srcPoints.push_back(Point2f(1291*xFactor,211*yFactor));
    srcPoints.push_back(Point2f(1558*xFactor,978*yFactor));
    srcPoints.push_back(Point2f(338*xFactor,976*yFactor));

    Mat wrapImg = Mat::zeros(in.size(),CV_8UC3);
    Mat wrapedMatrix = findHomography(srcPoints, mapPoints);
    warpPerspective(in, wrapImg, wrapedMatrix, in.size());

    int xdimension=329*xFactor;
    int ydimension=779*yFactor;

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

Mat cropImage(Mat source,  int width, int start, int end){

    Rect rec(0,start, width, end-start);

    Mat croppedRef(source, rec);

    Mat cropped;
    croppedRef.copyTo(cropped);

    return cropped;
}

struct modethree{
    Mat framePart;
    double partialSum;
    Mat bgPart;
    int start;
    int end;

    void initailize(Mat bg, Mat frame, int width) {
        bgPart = cropImage(bg, width, start, end);
        framePart = cropImage(frame, width, start, end);
    }
};

void* show2(void* arg ) {
    struct modethree *arg_struct =(struct modethree*) arg;

    double partialSum = 0;
      
    Mat overallDiff;
    absdiff(arg_struct->bgPart, arg_struct->framePart ,overallDiff);
    GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
    threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY);

    partialSum =(double)countNonZero(overallDiff);

    arg_struct->partialSum = partialSum;
    pthread_exit(0);
}


void show(VideoCapture video,String winName[],double fps, Mat bg, Mode mode) {
    // int i = 0;
    // Mat frame1;
    Mat frame2;

    double QueueDensity =0;
    double DynamicDensity=0;
    double totalSum = 0;
    double time=0;

    cout<< "Analysis started" << endl;

    string filename="graph.csv";
    ofstream myfile; 

    myfile.open(filename);
    myfile<<"Time(s)"<<","<<"Queue Density"<<","<<"Dynamic Density"<<endl;

    // cout<<"Time(s)"<<","<<"Queue Density"<<","<<"Dynamic Density"<<endl;

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
            // cout<< (time)/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
            continue;
        }

        if (mode.getMethod() == 2) {
            Mat temp = frame2.clone();
            resize(temp, frame2, Size(mode.xDimen,mode.yDimen), 0,0);
        }
        
        cvtColor(frame2, frame2, COLOR_BGR2GRAY);
        Mat birdEye2 = changeHom(frame2);
        // imshow(winName[0], birdEye2);

        if (mode.getMethod() == 3) {
            int no = mode.noThread;
            struct modethree args[no];
            pthread_t tids[no];

            int count= 0; 
            int height = birdEye2.rows;
            int width = birdEye2.cols;

            for (int i=0; i<no; i++){
                args[i].start = count;

                // cout<< "start " << start<< endl;
                count += height/no;
                if (i == no-1){
                    args[i].end=height;
                }
                else{
                    args[i].end=count;
                }
                
                // cout<< "end " << end<< endl;
                // cout<< "width " << width<< endl;
                args[i].initailize(bg,frame2, width);
                pthread_attr_t attr;
                pthread_attr_init(&attr);
                pthread_create(&tids[i],&attr,show2,&args[i]);
            }  

            for (int i=0; i<no;i++){
                pthread_join(tids[i],NULL);
            }

            for (int i=0; i<no;i++){
                totalSum += args[i].partialSum;
            }
        }

        else {
            Mat overallDiff;
            absdiff(bg, birdEye2,overallDiff);
            GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
            threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY );
            totalSum = (double)countNonZero(overallDiff);

            // imshow(winName[1], overallDiff);

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

        }

        QueueDensity= totalSum/(double)256291;

        myfile<<time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
        // cout<< time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
        
        
        if (waitKey(1) == 27){
            cout << "Esc key is pressed by user. Stopping the video" << endl;
            break;
        }
    }
}


void* show1(void* arg ) {
    struct modefour *arg_struct =(struct modefour*) arg;

    double QueueDensity =0;

    int count=arg_struct->start;
    VideoCapture video = arg_struct->video;
    video.set(CAP_PROP_POS_FRAMES,count);

    Mat frame2;
    Mat bg = arg_struct->bg;
    map<int,double> data;
    while (count != arg_struct->end) {
        bool isOpened = video.read(frame2);

        if (isOpened == false) {
            cout << "Video has ended" << endl;
            break;
        } 
        cvtColor(frame2, frame2, COLOR_BGR2GRAY);
        Mat birdEye2 = changeHom(frame2);
        Mat overallDiff;
        absdiff(bg, birdEye2,overallDiff);
        GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
        threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY );

        QueueDensity=(double)countNonZero(overallDiff)/(double)256291;
        data.insert({count,QueueDensity});
        if (waitKey(1) == 27){
            cout << "Esc key is pressed by user. Stopping the video" << endl;
            break;
        }
        count++;
    }
    arg_struct->data=data;
    pthread_exit(0);
}



Mat getBack(VideoCapture video,int emptime, Mode mode) {
    video.set(CAP_PROP_POS_MSEC,emptime*1000) ;
    Mat frame;
    bool isOpened = video.read(frame);

    if (isOpened == false) {
        cout << "The time for empty frame is not correct\n" << endl;
    } 

    if (mode.getMethod() == 2){
        Mat bg;
        resize(frame, bg, Size(mode.xDimen, mode.yDimen), 0,0);
        cvtColor(bg, bg, COLOR_BGR2GRAY);

        video.set(CAP_PROP_POS_MSEC,0) ;
        Mat changed = changeHom(bg);
        return changed;

    }

    cvtColor(frame, frame, COLOR_BGR2GRAY);

    video.set(CAP_PROP_POS_MSEC,0) ;
    Mat changed = changeHom(frame);
    return changed;
}


int main(int argc, char** argv) {
    string videopath,videoname;
    
    double fps; 
    int frameT;
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
    frameT= (int) video.get(CAP_PROP_FRAME_COUNT);
    Mode mode;
    if (argc == 2) {
        cout<< "Method for optimization not provided" << endl;
        return 0;
    }
    int modeVal = stoi(argv[2]);
    mode.setMethod(modeVal);

    int emptime=345;
    
    if (modeVal ==1){
        if (argc == 3) {
            cout<< "Number of frames to skip not provided" << endl;
            return 0;
        }
        mode.setSkipper(stoi(argv[3]));
    }

    else if (modeVal == 2){
        if (argc <5) {
            cout<< "Both dimensions not provided" << endl;
            return 0;
        }
        mode.xDimen = stod(argv[3]);
        mode.yDimen = stod(argv[4]);
    }

    Mat bg = getBack(video,emptime, mode);

    if (modeVal == 4){
        
        if (argc==3){
            cout<<"No of threads not provided"<<endl;
            return 0;
        }
        int no = stoi(argv[3]);
        mode.noThread=no;

        struct modefour args[no];
        pthread_t tids[no];
        int count=0;

        cout<< "Analysis started" << endl;
        auto start = high_resolution_clock::now();
        for (int i=0; i<no; i++){
            args[i].start = count;
            count += frameT/no;
            if (i == no-1){
                args[i].end=frameT+1;
            }
            else{
                args[i].end=count;
            }
            args[i].bg = bg; 
            VideoCapture vid(videopath);
            args[i].video = vid;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_create(&tids[i],&attr,show1,&args[i]);
        }

        ofstream myfile;
        myfile.open ("graph.csv");
        myfile<<"Time(s),Queue Density\n";
        for (int i=0; i<no;i++){
            pthread_join(tids[i],NULL);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by function: "<< duration.count()/1000000 << " seconds" << endl;
        for (int i=0; i<no;i++){
            for (int j=args[i].start;j<args[i].end;j++){
                if (j<frameT-2){
                    double k= (double) j /15.0;
                    myfile<<k<<","<<args[i].data.at(j)<<endl;
                }
            }
        }        
        myfile.close(); 
        return 0;
    }
    else if (modeVal==3){
        if (argc==3){
            cout<<"No of threads not provided"<<endl;
            return 0;
        }
        mode.noThread= stoi(argv[3]);  
    }

    
    string winName[3] = {"Original Video","Overall Difference","Dynamic Difference"};  

    auto start = high_resolution_clock::now(); 
    show(video,winName,fps,bg, mode);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "<< duration.count()/1000000 << " seconds" << endl;
    return 0;
    
}



