#pragma once
#include <string>
#include <thread>
#include <vector>
#include "CalibrationManager.h"

class DualCamManager
{
public:
	/**
	** DualCamManager : Constructor
	** Args : 1/ fileName in which the image file locations will be saved
	** 2/ cvSize define the size of the images the camera will stream.
	** 3/ cvSize same as 2/
	** 4/ nx : size of chessboard width
	** 5/ ny : size of chessboard height
	** 6/ useUncalibrated : deprecated
	** 7/ squareSize : size in cm of the squares on chessboard
	**/
	DualCamManager(std::string fileName = "list.txt", CvSize sizeCam1 = cvSize(320, 240), CvSize sizeCam2 = cvSize(320, 240), int nx = 8, int ny = 6, int useUncalibrated = 0, double squareSize = 5.0);

	~DualCamManager(void);
	/**
	** calibrated : tell the instance of calibrationManager to run the calibration manager
	**/

	bool calibrate(int nx = 8, int ny = 6, int useUncalibrated = 0, float _squareSize = 2.5);
	/**
	** isCalibrated (bool) : detects whether the file where all the image location is present or not and
	** determines if the program can be run precalibrated or not
	**/
	bool isCalibrated()const;
	/**
	** startStream(int, int) : run the dual camera stream
	** Args : 1/ id of the 1st camera
	**	2/ id of the 2nd camera
	** *************** TODO***************
	**			successfully determine which 
	**			camera is left and which is right
	**/
	void startStream(int camId1 = 0, int camId2 = 2);
	/**
	** findVideoDevices() : find which usb devices are similar (name wise) and assumes
	** these devices are the dual cameras.
	** ********************* TODO ***********************
	**			Only compatible windows, find
	**			way for linux (hint : using libusb)
	**/
	void findVideoDevices();
	/**
	** run() : load the data in matrices and run the stereoscopic vision
	** algorithm on the current dual cam video stream
	**/
	void run();
	/**
	** runThread() : run software as a thread independantly to program
	** known bugs : sometimes at exit of program error pops up
	**/
	void runThread();
private :
	/**
	** Display3D() : displays the reconstructed 3d real time data.
	** library used for display : SFML 2.0 & OPENGL
	** *********************** TODO *****************************
	**				3d data is incorrect, due to wrong values
	**				or misinterprated values. Look also towards
	**				the way they are stored in the matrix(chars) maybe
	**				this is the cause of the faulty and glitchy display.
	**/
	void display3D();

	/**
	** threadRunning : is the program launched within a thread or not. 
	** used to be able to stop thread adequatly when destructor is called.
	**/
	bool threadRunning;
	bool stopThread;
	/**
	**stop3D : stop 3d display thread.
	**/
	bool stop3D;

	std::thread* dualCamThread;
	std::thread* display3DThread;

	CalibrationManager * calibManager;
	std::string fileName;
	std::vector<std::string> deviceList;
	bool checkFileQuality(FILE *);//check the quality of the file, it is deleted when not satisfying
	/**
	** saveCalibrationImages(int,int)
	** starts the process of saving the images used for calibration.
	** each time a chessboard is detected in both camera streams, the image is saved and
	** its location is saved in the file specified as fileName. which is then used by the 
	** calibrationManager.
	**/
	void saveCalibrationImages(int, int);
	int chessX, chessY;
	IplImage * depthData;
	bool depthUpdated;//is the depth data ready to be used

	int camId1, camId2;

	bool iscalibrated;//is the software precalibrated or not
	CvCapture * cap1, * cap2; // cameras streams
	IplImage * cam1, * cam2;// input cameras images
	IplImage * cam1Resize, * cam2Resize;// resized camera images to fit the desired size
	IplImage * cam1Gray, * cam2Gray;// grayscaled camera images
	CvSize SizeCam1;//size of cameras
	CvSize SizeCam2;// size of cam need to be the same!!
};

