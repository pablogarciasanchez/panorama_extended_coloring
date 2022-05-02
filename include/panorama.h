#ifndef PANORAMA_H_INCLUDED
#define PANORAMA_H_INCLUDED
#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc.hpp>
#include "aux.h"


/** @file panorama.h
 *  @brief PANORAMA utilities external to Malla3D
 * 	@author [Alejandro Manzanares Lemus](https://github.com/Alexmnzlms)
 * 
 */

void combine_panorama(Axis axis, std::string input, std::string output);

#endif