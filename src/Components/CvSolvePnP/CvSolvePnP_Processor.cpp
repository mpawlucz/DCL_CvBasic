/*
 * CvSolvePnP_Processor.cpp
 *
 *  Created on: 18-10-2010
 *      Author: mateusz
 */

#include "CvSolvePnP_Processor.hpp"
#include "Logger.hpp"

#include <sstream>

namespace Processors {

namespace CvSolvePnP {

using namespace std;
using namespace cv;
using namespace boost;
using Types::HomogMatrix;
using namespace Types::Objects3D;

CvSolvePnP_Processor::CvSolvePnP_Processor(const std::string & n) :
	Component(n)
{
}

CvSolvePnP_Processor::~CvSolvePnP_Processor()
{
}

void CvSolvePnP_Processor::prepareInterface() {
	h_onNewObject3D.setup(this, &CvSolvePnP_Processor::onNewObject3D);
	registerHandler("onNewObject3D", &h_onNewObject3D);
	addDependency("onNewObject3D", &in_object3d);
	addDependency("onNewObject3D", &in_camerainfo);

	registerStream("in_object3d", &in_object3d);
	registerStream("in_camerainfo", &in_camerainfo);
	registerStream("out_homogMatrix", &out_homogMatrix);
}

bool CvSolvePnP_Processor::onStart()
{
	LOG(LTRACE) << "CvSolvePnP_Processor::onStart()\n";
	return true;
}

bool CvSolvePnP_Processor::onStop()
{
	LOG(LTRACE) << "CvSolvePnP_Processor::onStop()\n";
	return true;
}

bool CvSolvePnP_Processor::onInit()
{
	LOG(LTRACE) << "CvSolvePnP_Processor::onInit()\n";


	return true;
}

bool CvSolvePnP_Processor::onFinish()
{
	LOG(LTRACE) << "CvSolvePnP_Processor::onFinish()\n";
	return true;
}

bool CvSolvePnP_Processor::onStep()
{
	LOG(LTRACE) << "CvSolvePnP_Processor::onStep()\n";
	return true;
}

void CvSolvePnP_Processor::onNewObject3D()
{
	LOG(LTRACE) << "CvSolvePnP_Processor::onNewObject3D()\n";
	boost::shared_ptr <Types::Objects3D::Object3D> object3D = in_object3d.read();

	Types::CameraInfo camera_info = in_camerainfo.read();

	Mat modelPoints(object3D->getModelPoints());
	Mat imagePoints(object3D->getImagePoints());

	Mat_<double> rvec;
	Mat_<double> tvec;

	solvePnP(modelPoints, imagePoints, camera_info.cameraMatrix(), camera_info.distCoeffs(), rvec, tvec, false);

	Mat_<double> rotationMatrix;
	Rodrigues(rvec, rotationMatrix);

	HomogMatrix hm;

	stringstream ss;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			hm.elements[i][j] = rotationMatrix(i, j);
			ss << hm.elements[i][j] << "  ";
		}
		hm.elements[i][3] = tvec(i, 0);
		ss << hm.elements[i][3] << "\n";
	}
	LOG(LDEBUG) << "HomogMatrix:\n" << ss.str() << endl;

	out_homogMatrix.write(hm);
}

} // namespace CvSolvePnP

} // namespace Processors
