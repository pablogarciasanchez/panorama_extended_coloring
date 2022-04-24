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

void combine_panorama(Axis axis);

#endif