#include "aux.h"

/** @file aux.cpp
 *  @brief Auxiliar enums definitions and functions related
 * 	@author [Alejandro Manzanares Lemus](https://github.com/Alexmnzlms)
 * 
 */

/**
 * @brief Convert enum Axis to std::string c++ type.
 * 
 * @param axis enum value to convert
 * @return std::string value of enum
 * @see [std::string](https://en.cppreference.com/w/cpp/string/basic_string)
 */
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
/**
 * @brief Convert enum Map to std::string c++ type.
 * 
 * @param map enum value to convert
 * @return std::string value of enum
 * @see [std::string](https://en.cppreference.com/w/cpp/string/basic_string)
 */
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
	
	case GNDM:
		map_string = "GNDM";
		break;
	}
	return map_string;
}
/**
 * @brief 
 * @todo comment
 * 
 * @param s 
 * @param delim 
 * @return vector<string> 
 */
std::vector<std::string> split(const std::string &s, char delim){
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}