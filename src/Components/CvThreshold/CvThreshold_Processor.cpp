/*!
 * \file CvThreshold_Processor.cpp
 * \brief
 * \author mstefanc
 * \date 2010-07-05
 */

#include <memory>
#include <string>

#include "CvThreshold_Processor.hpp"
#include "Logger.hpp"

namespace Processors {
namespace CvThreshold {

CvThreshold_Processor::CvThreshold_Processor(const std::string & name) : Base::Component(name),
		m_type("type", CV_THRESH_BINARY , "combo"),
		m_type2("type2", 0 , "combo"),
		m_thresh("thresh", 128, "range"),
		m_maxval("maxval", 255, "range")
{
	LOG(LTRACE) << "Hello CvThreshold_Processor\n";

	m_type.setToolTip("Thresholding type");
	m_type.addConstraint("BINARY");
	m_type.addConstraint("BINARY_INV");
	m_type.addConstraint("TRUNC");
	m_type.addConstraint("TOZERO");
	m_type.addConstraint("TOZERO_INV");

	m_type2.setToolTip("Thresholding type");
	m_type2.addConstraint("NULL");
	m_type2.addConstraint("OTSU");

	m_thresh.setToolTip("Threshold level");
	m_thresh.addConstraint("0");
	m_thresh.addConstraint("255");

	m_maxval.setToolTip("Maximum value to use with BINARY and BINARY_INV thresholding types");
	m_maxval.addConstraint("0");
	m_maxval.addConstraint("255");

	// Register properties.
	registerProperty(m_type);
	registerProperty(m_type2);
	registerProperty(m_thresh);
	registerProperty(m_maxval);
}

CvThreshold_Processor::~CvThreshold_Processor()
{
	LOG(LTRACE) << "Good bye CvThreshold_Processor\n";
}


void CvThreshold_Processor::prepareInterface() {
	CLOG(LTRACE) << "CvThreshold_Processor::prepareInterface\n";

	h_onNewImage.setup(this, &CvThreshold_Processor::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);

	registerStream("out_img", &out_img);

	addDependency("onNewImage", &in_img);
}

bool CvThreshold_Processor::onInit()
{
	LOG(LTRACE) << "CvThreshold_Processor::initialize\n";

	return true;
}

bool CvThreshold_Processor::onFinish()
{
	LOG(LTRACE) << "CvThreshold_Processor::finish\n";

	return true;
}

bool CvThreshold_Processor::onStep()
{
	LOG(LTRACE) << "CvThreshold_Processor::step\n";
	return true;
}

bool CvThreshold_Processor::onStop()
{
	return true;
}

bool CvThreshold_Processor::onStart()
{
	return true;
}

void CvThreshold_Processor::onNewImage()
{
	LOG(LNOTICE) << "CvThreshold_Processor::onNewImage\n";
	try {
		cv::Mat img = in_img.read();
		cv::Mat out = img.clone();
		LOG(LTRACE) << "Threshold " << m_thresh;
		int finalType = m_type | m_type2;
		cv::threshold(img, out, m_thresh, m_maxval, finalType);
		out_img.write(out);
	} catch (...) {
		LOG(LERROR) << "CvThreshold::onNewImage failed\n";
	}
}

}//: namespace CvThreshold
} //: namespace Processors
