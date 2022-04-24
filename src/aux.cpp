#include "aux.h"

std::string axis_to_string(Axis axis){
	std::string axis_string;
	switch (axis)
	{
	case X:
		axis_string = "X";
		break;
	
	case Y:
		axis_string = "Y";
		break;

	case Z:
		axis_string = "Z";
		break;
	}
	return axis_string;
}

std::string map_to_string(Map map){
	std::string map_string;
	switch (map)
	{
	case SDM:
		map_string = "SDM";
		break;
	
	case NDM:
		map_string = "NDM";
		break;
	}
	return map_string;
}