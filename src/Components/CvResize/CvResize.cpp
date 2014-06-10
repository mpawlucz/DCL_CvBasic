/*!
 * \file
 * \brief
 * \author mpawlucz
 * \date 2014-06-04
 */

#include <memory>
#include <string>

#include "CvResize.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace CvResize {

CvResize::CvResize(const std::string & name) :
	Base::Component(name),
	outputWidth("outputWidth", 500),
	outputHeight("outputHeight", 500)
{
	outputWidth.setToolTip("Width");
	outputWidth.addConstraint("1");
	outputWidth.addConstraint("5000");

	outputHeight.setToolTip("Width");
	outputHeight.addConstraint("1");
	outputHeight.addConstraint("5000");

	registerProperty(outputWidth);
	registerProperty(outputHeight);
}

CvResize::~CvResize() {
}

void CvResize::prepareInterface() {
	// Register data streams, events and event handlers HERE!

	h_onNewImage.setup(this, &CvResize::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);
	addDependency("onNewImage", &in_img);

	registerStream("in_img", &in_img);

	registerStream("out_img", &out_img);
}

bool CvResize::onInit() {

	return true;
}

bool CvResize::onFinish() {
	return true;
}

bool CvResize::onStop() {
	return true;
}

bool CvResize::onStart() {
	return true;
}

void CvResize::onNewImage()
{
	LOG(LTRACE) << "CvResize::onNewImage\n";
	try {
		cv::Mat img = in_img.read();

		//cv::filter2D(img, tmp, -1, norm * kernel, cv::Size(-1, -1), delta, cv::BORDER_REPLICATE);
		cv::resize(img, tmp, cv::Size(outputWidth, outputHeight));

		out_img.write(tmp);
	} catch (...) {
		LOG(LERROR) << "CvResize::onNewImage failed\n";
	}
}


} //: namespace CvResize
} //: namespace Processors
