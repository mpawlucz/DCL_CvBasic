/*!
 * \file
 * \brief
 * \author budrys,,,
 */

#include <memory>
#include <string>

#include "Multiplication.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace Multiplication {

Multiplication::Multiplication(const std::string & name) :
		Base::Component(name),
		denominator("denominator", 255)
{
		denominator.setToolTip("denominator: (numerator/denominator)");
		denominator.addConstraint("1");
		denominator.addConstraint("255");

		registerProperty(denominator);
}

Multiplication::~Multiplication() {
}

void Multiplication::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	h_onNewImage.setup(this, &Multiplication::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);
	addDependency("onNewImage", &in_img1);
	addDependency("onNewImage", &in_img2);

	// Input and output data streams.
	registerStream("in_img1", &in_img1);
	registerStream("in_img2", &in_img2);
	registerStream("out_img", &out_img);
}

bool Multiplication::onInit() {

	return true;
}

bool Multiplication::onFinish() {
	return true;
}

bool Multiplication::onStop() {
	return true;
}

bool Multiplication::onStart() {
	return true;
}

void Multiplication::onNewImage()
{
	LOG(LTRACE) << "Multiplication::onNewImage\n";
	try {
		cv::Mat img1 = in_img1.read();
		cv::Mat img2 = in_img2.read();

		// Create a matrix with the adequate size and depth.
		tmp.create(img1.size(), img1.depth());

		// Multiply the images
		tmp = img1.mul(img2) * (1/denominator);

		// Write the result to the output.
		out_img.write(tmp);
	} catch (...) {
		LOG(LERROR) << "Multiplication::onNewImage failed\n";
	}
}

} //: namespace Multiplication
} //: namespace Processors
