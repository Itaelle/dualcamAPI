// DualCamCalibrateOOP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DualCamManager.h"

#include  <iostream>

#define CAMX 640
#define CAMY 480

int _tmain(int argc, _TCHAR* argv[])
{
	DualCamManager * camManager = new DualCamManager("list.txt", cvSize(CAMX, CAMY), cvSize(CAMX, CAMY), 8, 6, 0, 2.5);
	
	camManager->findVideoDevices();
	camManager->startStream();
	if (camManager->isCalibrated())
	{
		camManager->run();
		//Sleep(10000);
	}
	else
	{
		bool succeed = camManager->calibrate();
		if (succeed)
			camManager->run();
	}
	delete camManager;
	return 0;
}

