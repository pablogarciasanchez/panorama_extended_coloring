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
 * @param input Relative path to feature maps images contaning folder
 * @param output Relative path to img export folder
 * 
 * @see [cv::resize](https://docs.opencv.org/3.4/da/d54/group__imgproc__transform.html#ga47a974309e9102f5f08231edc7e7529d)
 */
void combine_panorama(Axis axis, std::string input, std::string output){
	std::string extension = ".png";

	std::vector<cv::Mat> channels;

	cv::Mat sdm, ndm, gndm, panorama_extended, panorama_resize;

	sdm = cv::imread(input + "SDM_" + axis_to_string(axis) + extension, 0);
	ndm = cv::imread(input + "NDM_" + axis_to_string(axis) + extension, 0);
	gndm = cv::imread(input + "GNDM_" + axis_to_string(axis) + extension, 0);

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

/**
 * @brief Concatenation PANORAMA feature maps SDM and NDM
 * 
 * vconcat function is used to compute this concatenation.
 *
 * PANORAMA output image is exported as original size and 10% of the
 * original size. This reduction is performed by using resize function provided
 * by OpenCV.
 * 
 * @param axis Axis of feature maps
 * @param input Relative path to feature maps images contaning folder
 * @param output Relative path to img export folder
 * 
 * @see [cv::resize](https://docs.opencv.org/3.4/da/d54/group__imgproc__transform.html#ga47a974309e9102f5f08231edc7e7529d)
 * @see [cv::vconcat](https://docs.opencv.org/3.4/d2/de8/group__core__array.html#ga744f53b69f6e4f12156cdde4e76aed27)
 */
void concat_panorama(Axis axis, std::string input, std::string output){
	std::string extension = ".png";

	std::vector<cv::Mat> channels;

	cv::Mat sdm, ndm, gndm, panorama, panorama_resize;

	sdm = cv::imread(input + "SDM_" + axis_to_string(axis) + extension, 0);
	ndm = cv::imread(input + "NDM_" + axis_to_string(axis) + extension, 0);

	cv::Mat feature_array[2] = {sdm,ndm};

	cv::vconcat(feature_array,2,panorama);

	int r = (int) (panorama.rows * 0.1);
	int c = (int) (panorama.cols * 0.1);
	
	cv::resize(panorama, panorama_resize, cv::Size(c,r), CV_INTER_CUBIC);
	cv::imwrite(output + "panorama_" + axis_to_string(axis) + extension , panorama);
	cv::imwrite(output + "panorama_" + axis_to_string(axis) + "_10" + extension , panorama_resize);
}

/**
 * @brief Concatenation PANORAMA feature maps SDM and NDM
 * 
 * vconcat function is used to compute this concatenation.
 *
 * PANORAMA output image is exported as original size and 10% of the
 * original size. This reduction is performed by using resize function provided
 * by OpenCV.
 * 
 * @param map Axis of feature maps
 * @param input Relative path to feature maps images contaning folder
 * @param output Relative path to img export folder
 * 
 * @see [cv::resize](https://docs.opencv.org/3.4/da/d54/group__imgproc__transform.html#ga47a974309e9102f5f08231edc7e7529d)
 * @see [cv::vconcat](https://docs.opencv.org/3.4/d2/de8/group__core__array.html#ga744f53b69f6e4f12156cdde4e76aed27)
 */
void concat_panorama(Map map, std::string input, std::string output){
	std::string extension = ".png";

	std::vector<cv::Mat> channels;

	cv::Mat map_x, map_y, map_z, panorama, panorama_resize;

	map_x = cv::imread(input + map_to_string(map) + "_X" + extension, 0);
	map_y = cv::imread(input + map_to_string(map) + "_Y" + extension, 0);
	map_z = cv::imread(input + map_to_string(map) + "_Z" + extension, 0);
	

	cv::Mat feature_array[3] = {map_x, map_y, map_z};

	cv::vconcat(feature_array,3,panorama);

	int r = (int) (panorama.rows * 0.1);
	int c = (int) (panorama.cols * 0.1);
	
	cv::resize(panorama, panorama_resize, cv::Size(c,r), CV_INTER_CUBIC);
	cv::imwrite(output + "panorama_" + map_to_string(map) + extension , panorama);
	cv::imwrite(output + "panorama_" + map_to_string(map) + "_10" + extension , panorama_resize);
}