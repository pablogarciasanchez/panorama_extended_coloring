#include "panorama.h"

/** @file panorama.cpp
 *  @brief PANORAMA utilities external to Malla3D
 * 	@author [Alejandro Manzanares Lemus](https://github.com/Alexmnzlms)
 * 
 */

/**
 * @brief Combine PANORAMA feature maps SDM, NDM and GNDM in PANORAMA extended
 * representation
 * 
 * SDM, NDM and GNDM are combine in to a single image. One feature map 
 * per color channel.
 * 
 * PANORAMA extended output image is exported as original size and 10% of the
 * original size. This reduction is performed by using resize function provided
 * by OpenCV.
 * 
 * @param axis Axis of feature maps
 * 
 * @see [cv::resize](https://docs.opencv.org/3.4/da/d54/group__imgproc__transform.html#ga47a974309e9102f5f08231edc7e7529d)
 */
void combine_panorama(Axis axis, std::string output){
	std::string extension = ".png";

	std::vector<cv::Mat> channels;

	cv::Mat sdm, ndm, gndm, panorama_extended, panorama_resize;

	sdm = cv::imread(output + "SDM_" + axis_to_string(axis) + extension, 0);
	ndm = cv::imread(output + "NDM_" + axis_to_string(axis) + extension, 0);
	gndm = cv::imread(output + "GNDM_" + axis_to_string(axis) + extension, 0);

	channels.push_back(gndm);
	channels.push_back(sdm);
	channels.push_back(ndm);

	cv::merge(channels, panorama_extended);

	int r = (int) (panorama_extended.rows * 0.1);
	int c = (int) (panorama_extended.cols * 0.1);
	
	cv::resize(panorama_extended, panorama_resize, cv::Size(c,r), CV_INTER_CUBIC);
	cv::imwrite(output + "panorama_ext_" + axis_to_string(axis) + extension , panorama_extended);
	cv::imwrite(output + "panorama_ext_" + axis_to_string(axis) + "_10" + extension , panorama_resize);
}