//objectTrackingTutorial.cpp

//Written by  Kyle Hounslow 2013

//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software")
//, to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
//and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//IN THE SOFTWARE.

#include <sstream>
#include <string>
#include <iostream>
#include <opencv2/highgui/highgui.hpp> //for: VideoCapture;
#include <opencv2/imgproc/imgproc.hpp> //for: getStructuringElement & findContours & cvtColor
#include <cv.h>

using namespace cv;
using namespace std;

//initial min and max HSV filter values.
//these will be changed using trackbars
//// voor rood, donker plaats
//int H_MIN = 35;
//int H_MAX = 256;
//int S_MIN = 0;
//int S_MAX = 153;
//int V_MIN = 25;
//int V_MAX = 255;
//// voor rood, met veel licht
int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 141;
int S_MAX = 255;
int V_MIN = 137;
int V_MAX = 255;
//// voor blauw
//int H_MIN = 53;
//int H_MAX = 256;
//int S_MIN = 0;
//int S_MAX = 255;
//int V_MIN = 68;
//int V_MAX = 150;
//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 40 * 40;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Trackbars";

string intToString(int number) {

    std::stringstream ss;
    ss << number;
    return ss.str();
}

void drawObject(int x, int y, Mat &frame) {

    cv::circle(frame, cv::Point(x, y), 10, cv::Scalar(0, 0, 255));
    cv::putText(frame, intToString(x) + " , " + intToString(y), cv::Point(x, y + 20), 1, 1, Scalar(0, 255, 0));
}

void morphOps(Mat &thresh) {

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle

    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

    erode(thresh, thresh, erodeElement);
    erode(thresh, thresh, erodeElement);

    dilate(thresh, thresh, dilateElement);
    dilate(thresh, thresh, dilateElement);

}

void trackFilteredObject(Mat threshold, Mat HSV, Mat &cameraFeed) {

    int x, y;

    Mat temp;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
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
                drawObject(x, y, cameraFeed);
            }
        } else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
    }
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
    int fps = 5; // frame per second interger. 
    Size framesize(videoConnection.get(CV_CAP_PROP_FRAME_WIDTH), videoConnection.get(CV_CAP_PROP_FRAME_HEIGHT)); // frame size

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
    //// test if webcam worked
    imshow("Writer", vidframe);
    //waitKey(3000);
    return true;
}

int main(int argc, char* argv[]) {
    //if we would like to calibrate our filter values, set to true.
    bool calibrationMode = true;

    //Matrix to store each frame of the webcam feed
    Mat cameraFeed;
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
            cameraFeed = imread("img//SNAPSHOT.jpeg");
            //if in calibration mode, we track objects based on the HSV slider values.
            cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
            inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
            morphOps(threshold);
            //imshow(windowName2, threshold); for debug only
            trackFilteredObject(threshold, HSV, cameraFeed);
            // write the new images to this path
            // for debug only
            string src_path = "img//SNAPSHOTtoTresh.jpeg";
            imwrite(src_path, cameraFeed);
        }

        //show frames 
        //imshow(windowName2,threshold);

        imshow(windowName, cameraFeed); //for debug only
        imshow(windowName1,HSV);

        //delay 30ms so that screen can refresh.
        //image will not appear without this waitKey() command
        waitKey(30);
    }
    return 0;
}

