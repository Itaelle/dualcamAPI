#pragma once
#include <cv.h>
#include <highgui.h>


class CalibrationManager
{
	friend class DualCamManager;
public:
	/**
	** CalibrationManager : Constructor
	** Args:1/ filename in which to save the list of calibration images
	**		2/ Width of Chessboard
	**		3/ Height of chessboard
	**		4/ Deperecated
	**		5/ Size in centimeters of the squares in the chessboard
	**/
	CalibrationManager(std::string = "list.txt", int nx = 8, int ny = 6, int useUncalibrated = 0, double _squareSize = 5);
	/**
	**	~CalibrationManager : Destructor free's all allocated data
	**/
	~CalibrationManager(void);
	/**
	** runCalibration : run the calibration algorithm
	**	Process : Loads the images saved in the file, and runs cvStereoCalibrate.
	**/
	bool runCalibration();
private :
	/**
	** Function
	** return value
	** loadData : loads the matrixes from the xml 
	** files after calibration or when the program is launched precalibrated
	** Arg : 1/ Size of the input images.
	**/
	void loadData(CvSize);
	/**
	** Function
	** return value : void
	** InitMatrices : allocates sufficient amount for matrices
	**/
	void InitMatrices();
	/**
	** Function
	** return value : void
	** InitMatricesFile : allocates memory for matrices
	** before loading the calibration xml files
	** Arg: 1/ Size of input images
	**/
	void InitMatricesFile(CvSize);
	/**
	** Function
	** return value : void
	** saveFile : saves the calibration matrices in xml files (mx1, my1, mx2, my2)
	**/
	void saveFiles(CvMat, CvMat, CvMat, CvMat);
	/**
	** std::string
	** fileName ; saves the file name in which the 
	** location of calibration images are saved
	**/
	std::string fileName;
	/**
	** nx : width of chessboard
	** ny : height of chessboard
	**/
	int nx, ny;
	/**
	** useUncalibrated : deprecated
	**/
	int useUncalibrated;
	/**
	** squareSize : cm of chessboard square size
	**/
	float squareSize;

	/**
	** avgError : calibration result average error
	**/
	double avgError;


	/**
	** matrices to calculate stereo disparity
	**/
	CvMat _M1;
	CvMat _M2;
	CvMat _D1;
	CvMat _D2;
	CvMat _R;
	CvMat _T;
	CvMat _E;
	CvMat _F;
	CvMat _Q;
	CvMat *_Q2;
	CvMat *mx1;
	CvMat *my1;
	CvMat *mx2;
	CvMat *my2;
	double Q[4][4];

	double M1[3][3], M2[3][3], D1[5], D2[5];
    double R[3][3], T[3], E[3][3], F[3][3];
	
	/**
	** BMState : stereo parameters
	**/
	CvStereoBMState * BMState;
};

