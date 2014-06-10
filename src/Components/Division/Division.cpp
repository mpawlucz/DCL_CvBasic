/*!
 * \file
 * \brief
 * \author budrys,,,
 */

#include <memory>
#include <string>

#include "Division.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace Division {

Division::Division(const std::string & name) :
		Base::Component(name),
		numerator("numerator", 255)
  {
		numerator.setToolTip("Numerator: (numerator/denominator)");
		numerator.addConstraint("1");
		numerator.addConstraint("255");

		registerProperty(numerator);
}

Division::~Division() {
}

void Division::prepareInterface() {
	// Register data streams, events and event handlers HERE!
		h_onNewImage.setup(this, &Division::onNewImage);
		registerHandler("onNewImage", &h_onNewImage);
		addDependency("onNewImage", &in_img1);
		addDependency("onNewImage", &in_img2);

		// Input and output data streams.
		registerStream("in_img1", &in_img1);
		registerStream("in_img2", &in_img2);
		registerStream("out_img", &out_img);
}

bool Division::onInit() {

	return true;
}

bool Division::onFinish() {
	return true;
}

bool Division::onStop() {
	return true;
}

bool Division::onStart() {
	return true;
}

void Division::onNewImage()
{
	LOG(LTRACE) << "Division::onNewImage\n";
	try {
		cv::Mat img1 = in_img1.read();
		cv::Mat img2 = in_img2.read();

		// Create a matrix with the adequate size and depth.
		tmp.create(img1.size(), img1.depth());

		// Divide the images
		divide(img1, img2, tmp);
		// Normalize
		tmp = tmp * numerator;

		// Write the result to the output.
		out_img.write(tmp);
	} catch (...) {
		LOG(LERROR) << "Division::onNewImage failed\n";
	}
}


} //: namespace Division
} //: namespace Processors
