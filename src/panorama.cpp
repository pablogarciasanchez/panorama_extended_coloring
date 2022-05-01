#include "panorama.h"

/**
 * doc template
 */
void combine_panorama(Axis axis){
	std::string folder = "png/";
	std::string extension = ".png";

	std::vector<cv::Mat> channels;

	cv::Mat sdm, ndm, gndm, panorama_extended, panorama_resize;

	sdm = cv::imread(folder + "SDM_" + axis_to_string(axis) + extension, 0);
	ndm = cv::imread(folder + "NDM_" + axis_to_string(axis) + extension, 0);
	gndm = cv::imread(folder + "GNDM_" + axis_to_string(axis) + extension, 0);

	channels.push_back(gndm);
	channels.push_back(sdm);
	channels.push_back(ndm);

	cv::merge(channels, panorama_extended);

	int r = (int) (panorama_extended.rows * 0.1);
	int c = (int) (panorama_extended.cols * 0.1);
	
	cv::resize(panorama_extended, panorama_resize, cv::Size(c,r), CV_INTER_CUBIC);
	cv::imwrite(folder + "panorama_ext_" + axis_to_string(axis) + extension , panorama_extended);
	cv::imwrite(folder + "panorama_ext_" + axis_to_string(axis) + "_10" + extension , panorama_resize);
}