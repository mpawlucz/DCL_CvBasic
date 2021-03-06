/*!
 * \file
 * \brief 
 * \author mpawlucz
 * \date 2014-06-04
 */

#ifndef CVRESIZE_HPP_
#define CVRESIZE_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 * \defgroup CvResize CvResize
 * \ingroup Processors
 *
 * Resizes an image
 *
 *
 *
 * \par Data streams:
 *
 * \streamin{in_img,cv::Mat}
 * Input image
 * \streamout{out_img,cv::Mat}
 * Output image
 *
 *
 * \par Events:
 *
 * \event{newImage}
 * Image split
 *
 *
 * \par Event handlers:
 *
 * \handler{onNewImage}
 * New image arrived
 *
 *
 * \par Properties:
 *
 * \prop{outputWidth,int,500}
 * \prop{outputHeight,int,500}
 *
 */

namespace Processors {
namespace CvResize {

using namespace cv;

/*!
 * \class CvResize
 * \brief CvResize processor class.symbol lookup error
 *
 * CvResize processor.
 */
class CvResize: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	CvResize(const std::string & name = "CvResize");

	/*!
	 * Destructor
	 */
	virtual ~CvResize();

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
	Base::EventHandler <CvResize> h_onNewImage;

	/// Input data stream
	Base::DataStreamIn <Mat> in_img;

	/// Output data stream - processed image
	Base::DataStreamOut <Mat> out_img;

	Base::Property<int> outputWidth;
	Base::Property<int> outputHeight;

private:
	cv::Mat tmp;

};

} //: namespace CvResize
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("CvResize", Processors::CvResize::CvResize)

#endif /* CVRESIZE_HPP_ */
