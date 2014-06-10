/*!
 * \file
 * \brief 
 * \author mpawlucz
 * \date 2014-06-10
 */

#ifndef MULTIPLICATION_HPP_
#define MULTIPLICATION_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/core/core.hpp>

namespace Processors {
namespace Multiplication {

using namespace cv;

/*!
 * \class Multiplication
 * \brief Multiplication processor class.
 *
 * Multiplication processor.
 */
class Multiplication: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	Multiplication(const std::string & name = "Multiplication");

	/*!
	 * Destructor
	 */
	virtual ~Multiplication();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to 
	 * values set in config file.
	 */
	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();

	/*!
	 * Event handler function.
	 */
	void onNewImage();

	/// Event handler.
	Base::EventHandler <Multiplication> h_onNewImage;

	/// Input data streams
	Base::DataStreamIn <Mat> in_img1;
	Base::DataStreamIn <Mat> in_img2;

	/// Output data stream - a normalized multiplication of input images
	Base::DataStreamOut <Mat> out_img;

	// A denominator, out_img = (in_img1{0..255} * in_img2{0..255}) / denominator{1|255}
	Base::Property<double> denominator;
	
private:
	cv::Mat tmp;

};

} //: namespace Multiplication
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("Multiplication", Processors::Multiplication::Multiplication)

#endif /* MULTIPLICATION_HPP_ */
