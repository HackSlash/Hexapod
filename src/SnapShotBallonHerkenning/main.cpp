/* 
 * File:   main.cpp
 * Author: mark
 *
 * Created on 12 mei 2015, 22:52
 */

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
using namespace cv;
using namespace std;

Mat src, src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 40 * 40;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;


//int to string helper function

string intToString(int number) {

    //this function has a number input and string output
    std::stringstream ss;
    ss << number;
    return ss.str();
}

void drawObject(int x, int y, Mat &frame) {

    cv::circle(frame, cv::Point(x, y), 10, cv::Scalar(0, 0, 255));
    cv::putText(frame, intToString(x) + " , " + intToString(y), cv::Point(x, y + 20), 1, 1, Scalar(0, 255, 0));
}

Mat redFilter(Mat& src) {
    assert(src.type() == CV_8UC3);

    //// voor rood, met veel licht
    //    int H_MIN = 0;
    //    int H_MAX = 256;
    //    int S_MIN = 141;
    //    int S_MAX = 255;
    //    int V_MIN = 137;
    //    int V_MAX = 255;
    int H_MIN = 163;
    int H_MAX = 256;
    int S_MIN = 47;
    int S_MAX = 255;
    int V_MIN = 0;
    int V_MAX = 255;

    Mat threshRed, thresholded;
    cvtColor(src, threshRed, COLOR_BGR2HSV);
    inRange(threshRed, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), thresholded);

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(20, 20));

    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(18, 18));

    erode(thresholded, thresholded, erodeElement);
    erode(thresholded, thresholded, erodeElement);

    dilate(thresholded, thresholded, dilateElement);

    return thresholded;
}

Mat blueFilter(const Mat& src) {
    assert(src.type() == CV_8UC3);

    //// voor blauw, licht plaatje
    int H_MIN = 53;
    int H_MAX = 256;
    int S_MIN = 0;
    int S_MAX = 255;
    int V_MIN = 68;
    int V_MAX = 150;

    Mat threshBlue, thresholded;
    cvtColor(src, threshBlue, COLOR_BGR2HSV);
    inRange(threshBlue, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), thresholded);

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));

    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

    erode(thresholded, thresholded, erodeElement);
    erode(thresholded, thresholded, erodeElement);
    erode(thresholded, thresholded, erodeElement);

    dilate(thresholded, thresholded, dilateElement);
    dilate(thresholded, thresholded, dilateElement);
    dilate(thresholded, thresholded, dilateElement);
    dilate(thresholded, thresholded, dilateElement);

    return thresholded;
}

Mat getContour(Mat &thresholdFilter) {

    int x, y;
    /// Find contours   
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    RNG rng(12345); // optional, random number generator 

    findContours(thresholdFilter, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    /// Find the rotated ellipses for each contour
    vector<RotatedRect> minEllipse(contours.size());

    for (int i = 0; i < contours.size(); i++) {
        if (contours[i].size() > 5) {
            minEllipse[i] = fitEllipse(Mat(contours[i]));
        }
    }

    /// Draw contours
    Mat drawing = Mat::zeros(thresholdFilter.size(), CV_8UC3);
    for (int i = 0; i < contours.size(); i++) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        //drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
        // ellipse
        ellipse(drawing, minEllipse[i], color, 2, 8);
    }

    //use moments method to find our filtered object
    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if (numObjects < MAX_NUM_OBJECTS) {
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

                //if the area is less than 20 px by 20px then it is probably just noise
                //if the area is the same as the 3/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if (area > MIN_OBJECT_AREA) {
                    x = moment.m10 / area;
                    y = moment.m01 / area;

                    cout << x << endl;
                    cout << y << endl;
                    objectFound = true;

                } else objectFound = false;
            }
            //let user know you found an object
            if (objectFound == true) {
                //draw object location on screen
                drawObject(x, y, drawing);
            }
        } //else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
    }

    //// for debug only
    imshow("Result window", drawing);

    return thresholdFilter;
}

bool getVideo(Mat &vidframe) {

    VideoCapture videoConnection(0);
    
    if (!videoConnection.isOpened()) // if not success, exit program
    {
        cout << "ERROR COULD NOT CONNECT WITH WEBCAM!" << endl;
        return false;
    }
    
    VideoWriter writer; // Write each frame from the webcam to the matrix.
    //foto-options
    int fcc = CV_FOURCC('J', 'P', 'E', 'G'); // four character code.
    int fps = 1; // frame per second interger. 
    Size framesize(videoConnection.get(CV_CAP_PROP_FRAME_WIDTH), videoConnection.get(CV_CAP_PROP_FRAME_HEIGHT)); // frame size

    //waitKey(3000);
    string filePath = "img//SNAPSHOT.jpeg"; // imagePath
    writer = VideoWriter(filePath, fcc, fps, framesize); //Writes the jpg-file to a path.

    if (!writer.isOpened()) {
        cout << "Error opening file for writer" << endl;
        getchar;
        return false;
    }

    bool bSuccess = videoConnection.read(vidframe); //Check if types are OK.

    if (!bSuccess) //test if frame successfully read
    {
        cout << "ERROR READING FRAME FROM CAMERA FEED" << endl;
        return false;
    }


    writer.write(vidframe);

    /*
    int breakLoop = 0;
    
    while (1) {

        //startNewRecording = true;

        if (startNewRecording == true) {
            startNewRecording = false;
            recording = true;

            videoNumber++; // when new recording is started, file name will be incremented

            string filePath = "img//SNAPSHOT.jpeg"; // imagePath
            writer = VideoWriter(filePath, fcc, fps, framesize); //Writes the jpg-file to a path.

            if (!writer.isOpened()) {
                cout << "Error opening file for writer" << endl;
                getchar;
                return false;
            }
        }

        bool bSuccess = videoConnection.read(vidframe); //Check if types are OK.

        if (!bSuccess) //test if frame successfully read
        {
            cout << "ERROR READING FRAME FROM CAMERA FEED" << endl;
            return false;
        }

        if (recording == true) // are recording
        {
            // write each frame from the webcam
            writer.write(vidframe); 
        }
        
        if (waitKey(2000)) {

            startNewRecording = true;
        }

        //// after ten snapshots the wile loop
        //// will be broken
        if (breakLoop == 10) {
            break;
        }
        breakLoop++;
    }
     */ 




    return true;
}

int main(int argc, char* argv[]) {
    //if we would like to calibrate our filter values, set to true.
    bool calibrationMode = true;

    //Matrix to store each frame of the webcam feed
    Mat cameraFeed;
    Mat cameraFrame;
    Mat threshold;
    Mat HSV;

    //video capture object to acquire webcam feed
    //    VideoCapture capture;
    //open capture object at location zero (default location for webcam)
    //    capture.open(0);
    //set height and width of capture frame
    //    capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    //    capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
    //start an infinite loop where webcam feed is copied to cameraFeed matrix
    //all of our operations will be performed within this loop
    while (1) {


        bool balloon = getVideo(cameraFeed);

        if (!balloon) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        //store image to matrix
        //        capture.read(cameraFeed);
        //convert frame from BGR to HSV colorspace
        //        cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);

        if (calibrationMode == true) {
            // Read image
            cameraFrame = imread("img//SNAPSHOT.jpeg");
            //if in calibration mode, we track objects based on the HSV slider values.
            //cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
            Mat redOnly = redFilter(cameraFrame);
            Mat gray;
            cvtColor(cameraFrame, gray, CV_BGR2GRAY);
            Canny(redOnly, gray, 200, 200, 3);
            Mat contourFound = getContour(gray);
            imshow("Get Contour", contourFound);
            //inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
            //Mat redOnly = redFilter(threshold);
            //morphOps(threshold);
            //thresh_callback(cameraFeed);
            //imshow(windowName2, threshold); for debug only
            //trackFilteredObject(threshold, HSV, cameraFeed);
            // write the new images to this path
            // for debug only
            string src_path = "img//SNAPSHOTtoTresh.jpeg";
            imwrite(src_path, cameraFrame);

            string src_path1 = "img//gray.jpeg";
            imwrite(src_path1, gray);

            string src_path2 = "img//contourFound.jpeg";
            imwrite(src_path2, contourFound);

            string src_path3 = "img//redOnly.jpeg";
            imwrite(src_path3, redOnly);
        }

        //show frames 
        //imshow(windowName2,threshold);

        //imshow(windowName, cameraFeed); //for debug only
        //imshow(windowName1, HSV);

        //delay 30ms so that screen can refresh.
        //image will not appear without this waitKey() command
        waitKey(30);
    }
    return 0;
}




