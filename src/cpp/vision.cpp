#include <iostream>
#include <unistd.h>
#include <opencv2/highgui/highgui.hpp> //for: VideoCapture
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp> //for: getStructuringElement & findContours & cvtColorv

using namespace std;
using namespace cv;

const int MAX_NUM_OBJECTS = 40; //max number of objects to be detected in frame
const int MIN_OBJECT_AREA = 20 * 20; //minimum object area
const int MAX_OBJECT_AREA = 640 * 480 / 1.5; //maximum object area  

//bounding rectangle of the object, we will use the center of this as its position.
Rect objectBoundingRectangle = Rect(0, 0, 0, 0);

///Converts Integer to String.

string intToString(int number) {
	stringstream ss;
	ss << number;
	return ss.str();
}

///@DEBUG Draws the object.

void drawObject(int x, int y, Mat &frame) {
	cv::circle(frame, cv::Point(x, y), 10, cv::Scalar(0, 0, 255));
	cv::putText(frame, intToString(x) + " , " + intToString(y), cv::Point(x, y + 20), 1, 1, Scalar(0, 255, 0));
}

int getDistance(int hoogteObjectInPx) {
	int brandpuntAfstandMM = 29;
	int hoogteObjectInMM = 27;
	int relatieveAfstandInMM = 0;
	return relatieveAfstandInMM = (((hoogteObjectInPx - hoogteObjectInMM) * brandpuntAfstandMM) / hoogteObjectInMM);
}

Mat redFilter1(Mat& src) {
	assert(src.type() == CV_8UC3);

	int H_MIN = 0;
	int H_MAX = 8;
	int S_MIN = 100;
	int S_MAX = 255;
	int V_MIN = 80;
	int V_MAX = 255;


	Mat threshRed, thresholded, reversedMat;
	cvtColor(src, threshRed, COLOR_BGR2HSV);
	inRange(threshRed, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), thresholded);

	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(4, 4)); //Structuring element that is used to erode an image.
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8)); //Structuring element that is used to dilate an image.

	erode(thresholded, thresholded, erodeElement);
	//	erode(thresholded, thresholded, erodeElement);

	dilate(thresholded, thresholded, dilateElement);
	dilate(thresholded, thresholded, dilateElement);
	//	dilate(thresholded, thresholded, dilateElement);
	//	dilate(thresholded, thresholded, dilateElement);

	bitwise_not(thresholded, reversedMat);

	string src_path = "./temp/binairObject1.jpg";
	imwrite(src_path, reversedMat);

	return reversedMat;
}

Mat redFilter2(Mat& src) {
	assert(src.type() == CV_8UC3);

	int H_MIN = 160;
	int H_MAX = 179;
	int S_MIN = 100;
	int S_MAX = 255;
	int V_MIN = 100;
	int V_MAX = 255;


	Mat threshRed, thresholded, reversedMat;
	cvtColor(src, threshRed, COLOR_BGR2HSV);
	inRange(threshRed, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), thresholded);

	bitwise_not(thresholded, reversedMat);

	string src_path = "./temp/binairObject2.jpg";
	imwrite(src_path, reversedMat);

	return reversedMat;
}

Mat blueFilter(Mat& src) {
	assert(src.type() == CV_8UC3); /// image 8-bit, single-channel

	//// voor blauw, licht plaatje
	//	int H_MIN = 53;
	//	int H_MAX = 256;
	//	int S_MIN = 0;
	//	int S_MAX = 255;
	//	int V_MIN = 68;
	//	int V_MAX = 150;
	int H_MIN = 88;
	int H_MAX = 256;
	int S_MIN = 114;
	int S_MAX = 182;
	int V_MIN = 0;
	int V_MAX = 99;

	//	int H_MIN = 90;
	//	int H_MAX = 100;
	//	int L_MIN = 95;
	//	int L_MAX = 133;
	//	int S_MIN = 6;
	//	int S_MAX = 255;

	Mat threshBlue, thresholded;

	cvtColor(src, threshBlue, COLOR_BGR2HLS);
	//	inRange(threshBlue, Scalar(H_MIN, L_MIN, S_MIN), Scalar(H_MAX, L_MAX, S_MAX), thresholded);
	inRange(threshBlue, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), thresholded);

	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3)); //Structuring element that is used to erode an image.
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8)); //Structuring element that is used to dilate an image.

	erode(thresholded, thresholded, erodeElement);
	erode(thresholded, thresholded, erodeElement);
	//	erode(thresholded, thresholded, erodeElement);

	dilate(thresholded, thresholded, dilateElement);
	dilate(thresholded, thresholded, dilateElement);
	//	dilate(thresholded, thresholded, dilateElement);
	//	dilate(thresholded, thresholded, dilateElement);

	return thresholded;
}

/// this methods needs binairImage

bool balloonDetector(Mat &originalImage) {

	// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;

	// Change thresholds
	params.minThreshold = 0;
	params.maxThreshold = 100;

	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 800;
	params.maxArea = 1800;

	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.1;
	params.maxCircularity = 0.9;

	// Filter by Convexity
	params.filterByConvexity = true;
	params.minConvexity = 0.96;
	params.maxConvexity = 0.98;

	// Filter by Inertia
	params.filterByInertia = true;
	params.minInertiaRatio = 0.01;
	params.maxInertiaRatio = 0.90;

	// Storage for blobs
	vector<KeyPoint> keypoints;

	// Set up detector with params
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

	// Detect blobs
	detector->detect(originalImage, keypoints);

	Mat im_with_keypoints;
	drawKeypoints(originalImage, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	return true;
}

void getXandY(Mat thresholdImage, Mat &cameraFeed) {
	bool objectDetected = false;
	Mat temp;
	thresholdImage.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(temp, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE); // retrieves external contours

	objectDetected = contours.size() > 0; //if contours vector is not empty, we have found some objects

	if (objectDetected) {
    	//the largest contour is found at the end of the contours vector
    	//we will simply assume that the biggest contour is the object we are looking for.
    	vector< vector<Point> > largestContourVec;
    	largestContourVec.push_back(contours.at(contours.size() - 1));
    	//make a bounding rectangle around the largest contour then find its centroid
    	//this will be the object's final estimated position.
    	objectBoundingRectangle = boundingRect(largestContourVec.at(0));
    	int xpos = objectBoundingRectangle.x + objectBoundingRectangle.width / 2;
    	int ypos = objectBoundingRectangle.y + objectBoundingRectangle.height / 2;

    	//update the objects positions by changing the 'theObject' array values
    	//theObject[0] = xpos, theObject[1] = ypos;
    	printf("x: %d; ", xpos);
    	printf("y: %d; ", ypos);
	}
}

void getContour(int &x, int &y, Mat threshold, Mat &cameraFeed) {

	//if the area is less than 20 px by 20px then it is probably just noise
	//if the area is the same as the 3/2 of the image size, probably just a bad filter
	//we only want the object with the largest area so we safe a reference area each
	//iteration and compare it to the area in the next iteration.

	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Mat temp;
	threshold.copyTo(temp);

	///Find all contours in the image.
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
    
//	// Set up the detector with default parameters.
	SimpleBlobDetector detector;

	// Detect blobs.
	std::vector<KeyPoint> keypoints;
	detector.detect(threshold, keypoints);
//
//	// Draw detected blobs as red circles.
//	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
//	Mat im_with_keypoints;
//	drawKeypoints(threshold, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    

	///Find the contour we need.
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
    	int numObjects = hierarchy.size();
    	if (numObjects < MAX_NUM_OBJECTS) {

        	for (int index = 0; index >= 0; index = hierarchy[index][0]) {
            	Moments moment = moments((cv::Mat)contours[index]);
            	double area = moment.m00;

            	if (area > MIN_OBJECT_AREA && area < MAX_OBJECT_AREA && area > refArea) {

                	x = moment.m10 / area;
                	y = moment.m01 / area;
                	objectFound = true;
                	refArea = area;
                	objectFound = true;
            	}
            	if (objectFound) {
                	printf("x: %d", x);
                	printf("y: %d", y);
            	} else objectFound = false;
            	printf("NO OBJECT");
        	}
    	}
	}

//	// Show blobs
//	imshow("Keypoints", im_with_keypoints);
	cout << "bitch cpu" << endl;
//	waitKey(0);
}

int captureFrame(Mat &vidframe) {

	VideoCapture videoConnection(0);

	if (!videoConnection.isOpened()) // if no feed, exit program
	{
    	cout << "ERROR COULD NOT CONNECT WITH WEBCAM!" << endl;
    	return -1;
	}

	VideoWriter writer; // Write each frame from the webcam to the matrix.
	///foto-options
	int fcc = CV_FOURCC('J', 'P', 'E', 'G'); // four character code.
	int fps = 1; // frame per second interger.
	Size framesize(videoConnection.get(CV_CAP_PROP_FRAME_WIDTH), videoConnection.get(CV_CAP_PROP_FRAME_HEIGHT)); // frame size

	string filePath = "./temp/SNAPSHOT.jpg"; // imagePath
	writer = VideoWriter(filePath, fcc, fps, framesize); // Writes the jpg-file to a path. Initialize the writer object

	if (!writer.isOpened()) {
    	cout << "Error opening file for writer" << endl; //@DEBUG mode
    	getchar; //// getchar returns an int value
    	return -1;
	}

	bool bSuccess = videoConnection.read(vidframe);

	if (!bSuccess) {
    	cout << "ERROR READING FRAME FROM CAMERA FEED" << endl; //@DEBUG mode
    	return -1;
	}
	sleep(4); // wait for writing frame to open the camera for a bit
	writer.write(vidframe);
	return 0;
}

//// argc = represent the number of things that you entered into the command line when running this program
//// argv = an array that holds the string value of the things that we entred on the command line running this program

int main(int argc, char* argv[]) {

	Mat cameraFeed;

	string argument = argv[1];
	string red = "red";
	string blue = "blue";
	int x = 0, y = 0;

	int succes = captureFrame(cameraFeed);

	Mat snapshot = imread("./temp/SNAPSHOT.jpg");

	if (argument == red) {
    	Mat biniarObject = redFilter1(snapshot);
    	Mat binairObject2 = redFilter2(snapshot);
    	Mat binairFinal;
    	bitwise_and(biniarObject, binairObject2, binairFinal);
    	bool findBalloon = balloonDetector(binairFinal);

    	if (findBalloon) {
        	//        	getXandY(biniarObject, snapshot);
        	getContour(x, y, binairFinal, snapshot);
    	} else {
        	printf("No object were found!");
    	}

    	string src_path4 = "./temp/FinalbinairObject.jpg";
    	imwrite(src_path4, binairFinal);
	}
	if (argument == blue) {
    	Mat blueOnly = redFilter1(snapshot);
    	//findBalloon(x, y, relativeDistance, blueOnly, snapshot);
	}
	return 0;
}
